
#ifndef __XML_CHVALID_H__
#define __XML_CHVALID_H__

#include <libxml/xmlversion.h>
#include <libxml/xmlstring.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _xmlChSRange xmlChSRange;
typedef xmlChSRange *xmlChSRangePtr;
struct _xmlChSRange {
    unsigned short	low;
    unsigned short	high;
};

typedef struct _xmlChLRange xmlChLRange;
typedef xmlChLRange *xmlChLRangePtr;
struct _xmlChLRange {
    unsigned int	low;
    unsigned int	high;
};

typedef struct _xmlChRangeGroup xmlChRangeGroup;
typedef xmlChRangeGroup *xmlChRangeGroupPtr;
struct _xmlChRangeGroup {
    int			nbShortRange;
    int			nbLongRange;
    const xmlChSRange	*shortRange;	
    const xmlChLRange	*longRange;
};

XMLPUBFUN int XMLCALL
		xmlCharInRange(unsigned int val, const xmlChRangeGroup *group);


#define xmlIsBaseChar_ch(c)	(((0x41 <= (c)) && ((c) <= 0x5a)) || \
				 ((0x61 <= (c)) && ((c) <= 0x7a)) || \
				 ((0xc0 <= (c)) && ((c) <= 0xd6)) || \
				 ((0xd8 <= (c)) && ((c) <= 0xf6)) || \
				  (0xf8 <= (c)))

#define xmlIsBaseCharQ(c)	(((c) < 0x100) ? \
				 xmlIsBaseChar_ch((c)) : \
				 xmlCharInRange((c), &xmlIsBaseCharGroup))

XMLPUBVAR const xmlChRangeGroup xmlIsBaseCharGroup;

#define xmlIsBlank_ch(c)	(((c) == 0x20) || \
				 ((0x9 <= (c)) && ((c) <= 0xa)) || \
				 ((c) == 0xd))

#define xmlIsBlankQ(c)		(((c) < 0x100) ? \
				 xmlIsBlank_ch((c)) : 0)


#define xmlIsChar_ch(c)		(((0x9 <= (c)) && ((c) <= 0xa)) || \
				 ((c) == 0xd) || \
				  (0x20 <= (c)))

#define xmlIsCharQ(c)		(((c) < 0x100) ? \
				 xmlIsChar_ch((c)) :\
				(((0x100 <= (c)) && ((c) <= 0xd7ff)) || \
				 ((0xe000 <= (c)) && ((c) <= 0xfffd)) || \
				 ((0x10000 <= (c)) && ((c) <= 0x10ffff))))

XMLPUBVAR const xmlChRangeGroup xmlIsCharGroup;

#define xmlIsCombiningQ(c)	(((c) < 0x100) ? \
				 0 : \
				 xmlCharInRange((c), &xmlIsCombiningGroup))

XMLPUBVAR const xmlChRangeGroup xmlIsCombiningGroup;

#define xmlIsDigit_ch(c)	(((0x30 <= (c)) && ((c) <= 0x39)))

#define xmlIsDigitQ(c)		(((c) < 0x100) ? \
				 xmlIsDigit_ch((c)) : \
				 xmlCharInRange((c), &xmlIsDigitGroup))

XMLPUBVAR const xmlChRangeGroup xmlIsDigitGroup;

#define xmlIsExtender_ch(c)	(((c) == 0xb7))

#define xmlIsExtenderQ(c)	(((c) < 0x100) ? \
				 xmlIsExtender_ch((c)) : \
				 xmlCharInRange((c), &xmlIsExtenderGroup))

XMLPUBVAR const xmlChRangeGroup xmlIsExtenderGroup;

#define xmlIsIdeographicQ(c)	(((c) < 0x100) ? \
				 0 :\
				(((0x4e00 <= (c)) && ((c) <= 0x9fa5)) || \
				 ((c) == 0x3007) || \
				 ((0x3021 <= (c)) && ((c) <= 0x3029))))

XMLPUBVAR const xmlChRangeGroup xmlIsIdeographicGroup;
XMLPUBVAR const unsigned char xmlIsPubidChar_tab[256];

#define xmlIsPubidChar_ch(c)	(xmlIsPubidChar_tab[(c)])

#define xmlIsPubidCharQ(c)	(((c) < 0x100) ? \
				 xmlIsPubidChar_ch((c)) : 0)

XMLPUBFUN int XMLCALL
		xmlIsBaseChar(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsBlank(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsChar(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsCombining(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsDigit(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsExtender(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsIdeographic(unsigned int ch);
XMLPUBFUN int XMLCALL
		xmlIsPubidChar(unsigned int ch);

#ifdef __cplusplus
}
#endif
#endif 
