/*
** 2004 April 6
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file implements a external (disk-based) database using BTrees.
** For a detailed discussion of BTrees, refer to
**
**     Donald E. Knuth, THE ART OF COMPUTER PROGRAMMING, Volume 3:
**     "Sorting And Searching", pages 473-480. Addison-Wesley
**     Publishing Company, Reading, Massachusetts.
**
** The basic idea is that each page of the file contains N database
** entries and N+1 pointers to subpages.
**
**   ----------------------------------------------------------------
**   |  Ptr(0) | Key(0) | Ptr(1) | Key(1) | ... | Key(N-1) | Ptr(N) |
**   ----------------------------------------------------------------
**
** All of the keys on the page that Ptr(0) points to have values less
** than Key(0).  All of the keys on page Ptr(1) and its subpages have
** values greater than Key(0) and less than Key(1).  All of the keys
** on Ptr(N) and its subpages have values greater than Key(N-1).  And
** so forth.
**
** Finding a particular key requires reading O(log(M)) pages from the 
** disk where M is the number of entries in the tree.
**
** In this implementation, a single file can hold one or more separate 
** BTrees.  Each BTree is identified by the index of its root page.  The
** key and data for any entry are combined to form the "payload".  A
** fixed amount of payload can be carried directly on the database
** page.  If the payload is larger than the preset amount then surplus
** bytes are stored on overflow pages.  The payload for an entry
** and the preceding pointer are combined to form a "Cell".  Each 
** page has a small header which contains the Ptr(N) pointer and other
** information such as the size of key and data.
**
** FORMAT DETAILS
**
** The file is divided into pages.  The first page is called page 1,
** the second is page 2, and so forth.  A page number of zero indicates
** "no such page".  The page size can be any power of 2 between 512 and 65536.
** Each page can be either a btree page, a freelist page, an overflow
** page, or a pointer-map page.
**
** The first page is always a btree page.  The first 100 bytes of the first
** page contain a special header (the "file header") that describes the file.
** The format of the file header is as follows:
**
**   OFFSET   SIZE    DESCRIPTION
**      0      16     Header string: "SQLite format 3\000"
**     16       2     Page size in bytes.  
**     18       1     File format write version
**     19       1     File format read version
**     20       1     Bytes of unused space at the end of each page
**     21       1     Max embedded payload fraction
**     22       1     Min embedded payload fraction
**     23       1     Min leaf payload fraction
**     24       4     File change counter
**     28       4     Reserved for future use
**     32       4     First freelist page
**     36       4     Number of freelist pages in the file
**     40      60     15 4-byte meta values passed to higher layers
**
**     40       4     Schema cookie
**     44       4     File format of schema layer
**     48       4     Size of page cache
**     52       4     Largest root-page (auto/incr_vacuum)
**     56       4     1=UTF-8 2=UTF16le 3=UTF16be
**     60       4     User version
**     64       4     Incremental vacuum mode
**     68       4     unused
**     72       4     unused
**     76       4     unused
**
** All of the integer values are big-endian (most significant byte first).
**
** The file change counter is incremented when the database is changed
** This counter allows other processes to know when the file has changed
** and thus when they need to flush their cache.
**
** The max embedded payload fraction is the amount of the total usable
** space in a page that can be consumed by a single cell for standard
** B-tree (non-LEAFDATA) tables.  A value of 255 means 100%.  The default
** is to limit the maximum cell size so that at least 4 cells will fit
** on one page.  Thus the default max embedded payload fraction is 64.
**
** If the payload for a cell is larger than the max payload, then extra
** payload is spilled to overflow pages.  Once an overflow page is allocated,
** as many bytes as possible are moved into the overflow pages without letting
** the cell size drop below the min embedded payload fraction.
**
** The min leaf payload fraction is like the min embedded payload fraction
** except that it applies to leaf nodes in a LEAFDATA tree.  The maximum
** payload fraction for a LEAFDATA tree is always 100% (or 255) and it
** not specified in the header.
**
** Each btree pages is divided into three sections:  The header, the
** cell pointer array, and the cell content area.  Page 1 also has a 100-byte
** file header that occurs before the page header.
**
**      |----------------|
**      | file header    |   100 bytes.  Page 1 only.
**      |----------------|
**      | page header    |   8 bytes for leaves.  12 bytes for interior nodes
**      |----------------|
**      | cell pointer   |   |  2 bytes per cell.  Sorted order.
**      | array          |   |  Grows downward
**      |                |   v
**      |----------------|
**      | unallocated    |
**      | space          |
**      |----------------|   ^  Grows upwards
**      | cell content   |   |  Arbitrary order interspersed with freeblocks.
**      | area           |   |  and free space fragments.
**      |----------------|
**
** The page headers looks like this:
**
**   OFFSET   SIZE     DESCRIPTION
**      0       1      Flags. 1: intkey, 2: zerodata, 4: leafdata, 8: leaf
**      1       2      byte offset to the first freeblock
**      3       2      number of cells on this page
**      5       2      first byte of the cell content area
**      7       1      number of fragmented free bytes
**      8       4      Right child (the Ptr(N) value).  Omitted on leaves.
**
** The flags define the format of this btree page.  The leaf flag means that
** this page has no children.  The zerodata flag means that this page carries
** only keys and no data.  The intkey flag means that the key is a integer
** which is stored in the key size entry of the cell header rather than in
** the payload area.
**
** The cell pointer array begins on the first byte after the page header.
** The cell pointer array contains zero or more 2-byte numbers which are
** offsets from the beginning of the page to the cell content in the cell
** content area.  The cell pointers occur in sorted order.  The system strives
** to keep free space after the last cell pointer so that new cells can
** be easily added without having to defragment the page.
**
** Cell content is stored at the very end of the page and grows toward the
** beginning of the page.
**
** Unused space within the cell content area is collected into a linked list of
** freeblocks.  Each freeblock is at least 4 bytes in size.  The byte offset
** to the first freeblock is given in the header.  Freeblocks occur in
** increasing order.  Because a freeblock must be at least 4 bytes in size,
** any group of 3 or fewer unused bytes in the cell content area cannot
** exist on the freeblock chain.  A group of 3 or fewer free bytes is called
** a fragment.  The total number of bytes in all fragments is recorded.
** in the page header at offset 7.
**
**    SIZE    DESCRIPTION
**      2     Byte offset of the next freeblock
**      2     Bytes in this freeblock
**
** Cells are of variable length.  Cells are stored in the cell content area at
** the end of the page.  Pointers to the cells are in the cell pointer array
** that immediately follows the page header.  Cells is not necessarily
** contiguous or in order, but cell pointers are contiguous and in order.
**
** Cell content makes use of variable length integers.  A variable
** length integer is 1 to 9 bytes where the lower 7 bits of each 
** byte are used.  The integer consists of all bytes that have bit 8 set and
** the first byte with bit 8 clear.  The most significant byte of the integer
** appears first.  A variable-length integer may not be more than 9 bytes long.
** As a special case, all 8 bytes of the 9th byte are used as data.  This
** allows a 64-bit integer to be encoded in 9 bytes.
**
**    0x00                      becomes  0x00000000
**    0x7f                      becomes  0x0000007f
**    0x81 0x00                 becomes  0x00000080
**    0x82 0x00                 becomes  0x00000100
**    0x80 0x7f                 becomes  0x0000007f
**    0x8a 0x91 0xd1 0xac 0x78  becomes  0x12345678
**    0x81 0x81 0x81 0x81 0x01  becomes  0x10204081
**
** Variable length integers are used for rowids and to hold the number of
** bytes of key and data in a btree cell.
**
** The content of a cell looks like this:
**
**    SIZE    DESCRIPTION
**      4     Page number of the left child. Omitted if leaf flag is set.
**     var    Number of bytes of data. Omitted if the zerodata flag is set.
**     var    Number of bytes of key. Or the key itself if intkey flag is set.
**      *     Payload
**      4     First page of the overflow chain.  Omitted if no overflow
**
** Overflow pages form a linked list.  Each page except the last is completely
** filled with data (pagesize - 4 bytes).  The last page can have as little
** as 1 byte of data.
**
**    SIZE    DESCRIPTION
**      4     Page number of next overflow page
**      *     Data
**
** Freelist pages come in two subtypes: trunk pages and leaf pages.  The
** file header points to the first in a linked list of trunk page.  Each trunk
** page points to multiple leaf pages.  The content of a leaf page is
** unspecified.  A trunk page looks like this:
**
**    SIZE    DESCRIPTION
**      4     Page number of next trunk page
**      4     Number of leaf pointers on this page
**      *     zero or more pages numbers of leaves
*/
#include "sqliteInt.h"


#define MX_CELL_SIZE(pBt)  ((int)(pBt->pageSize-8))

#define MX_CELL(pBt) ((pBt->pageSize-8)/6)

typedef struct MemPage MemPage;
typedef struct BtLock BtLock;

#ifndef SQLITE_FILE_HEADER 
#  define SQLITE_FILE_HEADER "SQLite format 3"
#endif

#define PTF_INTKEY    0x01
#define PTF_ZERODATA  0x02
#define PTF_LEAFDATA  0x04
#define PTF_LEAF      0x08

struct MemPage {
  u8 isInit;           
  u8 nOverflow;        
  u8 intKey;           
  u8 leaf;             
  u8 hasData;          
  u8 hdrOffset;        
  u8 childPtrSize;     
  u16 maxLocal;        
  u16 minLocal;        
  u16 cellOffset;      
  u16 nFree;           
  u16 nCell;           
  u16 maskPage;        
  struct _OvflCell {   
    u8 *pCell;          
    u16 idx;            
  } aOvfl[5];
  BtShared *pBt;       
  u8 *aData;           
  DbPage *pDbPage;     
  Pgno pgno;           
};

#define EXTRA_SIZE sizeof(MemPage)

struct BtLock {
  Btree *pBtree;        
  Pgno iTable;          
  u8 eLock;             
  BtLock *pNext;        
};

#define READ_LOCK     1
#define WRITE_LOCK    2

struct Btree {
  sqlite3 *db;       
  BtShared *pBt;     
  u8 inTrans;        
  u8 sharable;       
  u8 locked;         
  int wantToLock;    
  int nBackup;       
  Btree *pNext;      
  Btree *pPrev;      
#ifndef SQLITE_OMIT_SHARED_CACHE
  BtLock lock;       
#endif
};

#define TRANS_NONE  0
#define TRANS_READ  1
#define TRANS_WRITE 2

struct BtShared {
  Pager *pPager;        
  sqlite3 *db;          
  BtCursor *pCursor;    
  MemPage *pPage1;      
  u8 readOnly;          
  u8 pageSizeFixed;     
  u8 secureDelete;      
  u8 initiallyEmpty;    
  u8 openFlags;         
#ifndef SQLITE_OMIT_AUTOVACUUM
  u8 autoVacuum;        
  u8 incrVacuum;        
#endif
  u8 inTransaction;     
  u8 doNotUseWAL;       
  u16 maxLocal;         
  u16 minLocal;         
  u16 maxLeaf;          
  u16 minLeaf;          
  u32 pageSize;         
  u32 usableSize;       
  int nTransaction;     
  u32 nPage;            
  void *pSchema;        
  void (*xFreeSchema)(void*);  
  sqlite3_mutex *mutex; 
  Bitvec *pHasContent;  
#ifndef SQLITE_OMIT_SHARED_CACHE
  int nRef;             
  BtShared *pNext;      
  BtLock *pLock;        
  Btree *pWriter;       
  u8 isExclusive;       
  u8 isPending;         
#endif
  u8 *pTmpSpace;        
};

typedef struct CellInfo CellInfo;
struct CellInfo {
  i64 nKey;      
  u8 *pCell;     
  u32 nData;     
  u32 nPayload;  
  u16 nHeader;   
  u16 nLocal;    
  u16 iOverflow; 
  u16 nSize;     
};

#define BTCURSOR_MAX_DEPTH 20

struct BtCursor {
  Btree *pBtree;            
  BtShared *pBt;            
  BtCursor *pNext, *pPrev;  
  struct KeyInfo *pKeyInfo; 
  Pgno pgnoRoot;            
  sqlite3_int64 cachedRowid; 
  CellInfo info;            
  i64 nKey;        
  void *pKey;      
  int skipNext;    
  u8 wrFlag;                
  u8 atLast;                
  u8 validNKey;             
  u8 eState;                
#ifndef SQLITE_OMIT_INCRBLOB
  Pgno *aOverflow;          
  u8 isIncrblobHandle;      
#endif
  i16 iPage;                            
  u16 aiIdx[BTCURSOR_MAX_DEPTH];        
  MemPage *apPage[BTCURSOR_MAX_DEPTH];  
};

#define CURSOR_INVALID           0
#define CURSOR_VALID             1
#define CURSOR_REQUIRESEEK       2
#define CURSOR_FAULT             3

# define PENDING_BYTE_PAGE(pBt) PAGER_MJ_PGNO(pBt)

#define PTRMAP_PAGENO(pBt, pgno) ptrmapPageno(pBt, pgno)
#define PTRMAP_PTROFFSET(pgptrmap, pgno) (5*(pgno-pgptrmap-1))
#define PTRMAP_ISPAGE(pBt, pgno) (PTRMAP_PAGENO((pBt),(pgno))==(pgno))

#define PTRMAP_ROOTPAGE 1
#define PTRMAP_FREEPAGE 2
#define PTRMAP_OVERFLOW1 3
#define PTRMAP_OVERFLOW2 4
#define PTRMAP_BTREE 5

#define btreeIntegrity(p) \
  assert( p->pBt->inTransaction!=TRANS_NONE || p->pBt->nTransaction==0 ); \
  assert( p->pBt->inTransaction>=p->inTrans ); 


#ifndef SQLITE_OMIT_AUTOVACUUM
#define ISAUTOVACUUM (pBt->autoVacuum)
#else
#define ISAUTOVACUUM 0
#endif


typedef struct IntegrityCk IntegrityCk;
struct IntegrityCk {
  BtShared *pBt;    
  Pager *pPager;    
  Pgno nPage;       
  int *anRef;       
  int mxErr;        
  int nErr;         /* Number of messages written to zErrMsg so far */
  int mallocFailed; 
  StrAccum errMsg;  
};

#define get2byte(x)   ((x)[0]<<8 | (x)[1])
#define put2byte(p,v) ((p)[0] = (u8)((v)>>8), (p)[1] = (u8)(v))
#define get4byte sqlite3Get4byte
#define put4byte sqlite3Put4byte
