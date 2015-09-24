/*
** This file contains all sources (including headers) to the LEMON
** LALR(1) parser generator.  The sources have been combined into a
** single file to make it easy to include LEMON in the source tree
** and Makefile of another program.
**
** The author of this program disclaims copyright.
*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#ifndef __WIN32__
#   if defined(_WIN32) || defined(WIN32)
#	define __WIN32__
#   endif
#endif

#ifdef __WIN32__
#ifdef __cplusplus
extern "C" {
#endif
extern int access(const char *path, int mode);
#ifdef __cplusplus
}
#endif
#else
#include <unistd.h>
#endif

#define PRIVATE

#ifdef TEST
#define MAXRHS 5       
#else
#define MAXRHS 1000
#endif

static int showPrecedenceConflict = 0;
static const char **made_files = NULL;
static int made_files_count = 0;
static int successful_exit = 0;
static void LemonAtExit(void)
{
    
    int i;
    for (i = 0; i < made_files_count; i++) {
        if (!successful_exit) {
            remove(made_files[i]);
        }
    }
    free(made_files);
    made_files_count = 0;
    made_files = NULL;
}

static char *msort(char*,char**,int(*)(const char*,const char*));

#define lemonStrlen(X)   ((int)strlen(X))

struct rule;
struct lemon;
struct action;

static struct action *Action_new(void);
static struct action *Action_sort(struct action *);

void FindRulePrecedences();
void FindFirstSets();
void FindStates();
void FindLinks();
void FindFollowSets();
void FindActions();

void Configlist_init(void);
struct config *Configlist_add(struct rule *, int);
struct config *Configlist_addbasis(struct rule *, int);
void Configlist_closure(struct lemon *);
void Configlist_sort(void);
void Configlist_sortbasis(void);
struct config *Configlist_return(void);
struct config *Configlist_basis(void);
void Configlist_eat(struct config *);
void Configlist_reset(void);

void ErrorMsg(const char *, int,const char *, ...);

enum option_type { OPT_FLAG=1,  OPT_INT,  OPT_DBL,  OPT_STR,
         OPT_FFLAG, OPT_FINT, OPT_FDBL, OPT_FSTR};
struct s_options {
  enum option_type type;
  const char *label;
  char *arg;
  const char *message;
};
int    OptInit(char**,struct s_options*,FILE*);
int    OptNArgs(void);
char  *OptArg(int);
void   OptErr(int);
void   OptPrint(void);

void Parse(struct lemon *lemp);

struct plink *Plink_new(void);
void Plink_add(struct plink **, struct config *);
void Plink_copy(struct plink **, struct plink *);
void Plink_delete(struct plink *);

void Reprint(struct lemon *);
void ReportOutput(struct lemon *);
void ReportTable(struct lemon *, int);
void ReportHeader(struct lemon *);
void CompressTables(struct lemon *);
void ResortStates(struct lemon *);

void  SetSize(int);             
char *SetNew(void);               
void  SetFree(char*);             

char *SetNew(void);               
int SetAdd(char*,int);            
int SetUnion(char *,char *);    
#define SetFind(X,Y) (X[Y])       


typedef enum {LEMON_FALSE=0, LEMON_TRUE} Boolean;

enum symbol_type {
  TERMINAL,
  NONTERMINAL,
  MULTITERMINAL
};
enum e_assoc {
    LEFT,
    RIGHT,
    NONE,
    UNK
};
struct symbol {
  const char *name;        
  int index;               
  enum symbol_type type;   
  struct rule *rule;       
  struct symbol *fallback; 
  int prec;                
  enum e_assoc assoc;      
  char *firstset;          
  Boolean lambda;          
  int useCnt;              
  char *destructor;        
  int destLineno;          
  char *datatype;          
  int dtnum;               
  
  int nsubsym;             
  struct symbol **subsym;  
};

struct rule {
  struct symbol *lhs;      
  const char *lhsalias;    
  int lhsStart;            
  int ruleline;            
  int nrhs;                
  struct symbol **rhs;     
  const char **rhsalias;   
  int line;                
  const char *code;        
  struct symbol *precsym;  
  int index;               
  Boolean canReduce;       
  struct rule *nextlhs;    
  struct rule *next;       
};

enum cfgstatus {
  COMPLETE,
  INCOMPLETE
};
struct config {
  struct rule *rp;         
  int dot;                 
  char *fws;               
  struct plink *fplp;      
  struct plink *bplp;      
  struct state *stp;       
  enum cfgstatus status;   
  struct config *next;     
  struct config *bp;       
};

enum e_action {
  SHIFT,
  ACCEPT,
  REDUCE,
  ERROR,
  SSCONFLICT,              
  SRCONFLICT,              
  RRCONFLICT,              
  SH_RESOLVED,             
  RD_RESOLVED,             
  NOT_USED                 
};

struct action {
  struct symbol *sp;       
  enum e_action type;
  union {
    struct state *stp;     
    struct rule *rp;       
  } x;
  struct action *next;     
  struct action *collide;  
};

struct state {
  struct config *bp;       
  struct config *cfp;      
  int statenum;            
  struct action *ap;       
  int nTknAct, nNtAct;     
  int iTknOfst, iNtOfst;   
  int iDflt;               
};
#define NO_OFFSET (-2147483647)

struct plink {
  struct config *cfp;      
  struct plink *next;      
};

struct lemon {
  struct state **sorted;   
  struct rule *rule;       
  int nstate;              
  int nrule;               
  int nsymbol;             
  int nterminal;           
  struct symbol **symbols; 
  int errorcnt;            
  struct symbol *errsym;   
  struct symbol *wildcard; 
  char *name;              
  char *arg;               
  char *tokentype;         
  char *vartype;           
  char *start;             
  char *stacksize;         
  char *include;           
  char *error;             
  char *overflow;          
  char *failure;           
  char *accept;            
  char *extracode;         
  char *tokendest;         
  char *vardest;           
  char *filename;          
  char *outname;           
  char *tokenprefix;       
  int nconflict;           
  int tablesize;           
  int basisflag;           
  int has_fallback;        
  int nolinenosflag;       
  char *argv0;             
};

#define MemoryCheck(X) if((X)==0){ \
  extern void memory_error(); \
  memory_error(); \
}


const char *Strsafe(const char *);

void Strsafe_init(void);
int Strsafe_insert(const char *);
const char *Strsafe_find(const char *);


struct symbol *Symbol_new(const char *);
int Symbolcmpp(const void *, const void *);
void Symbol_init(void);
int Symbol_insert(struct symbol *, const char *);
struct symbol *Symbol_find(const char *);
struct symbol *Symbol_Nth(int);
int Symbol_count(void);
struct symbol **Symbol_arrayof(void);


int Configcmp(const char *, const char *);
struct state *State_new(void);
void State_init(void);
int State_insert(struct state *, struct config *);
struct state *State_find(struct config *);
struct state **State_arrayof();


void Configtable_init(void);
int Configtable_insert(struct config *);
struct config *Configtable_find(struct config *);
void Configtable_clear(int(*)(struct config *));


static struct action *Action_new(void){
  static struct action *freelist = 0;
  struct action *newaction;

  if( freelist==0 ){
    int i;
    int amt = 100;
    freelist = (struct action *)calloc(amt, sizeof(struct action));
    if( freelist==0 ){
      fprintf(stderr,"Unable to allocate memory for a new parser action.");
      exit(1);
    }
    for(i=0; i<amt-1; i++) freelist[i].next = &freelist[i+1];
    freelist[amt-1].next = 0;
  }
  newaction = freelist;
  freelist = freelist->next;
  return newaction;
}

static int actioncmp(
  struct action *ap1,
  struct action *ap2
){
  int rc;
  rc = ap1->sp->index - ap2->sp->index;
  if( rc==0 ){
    rc = (int)ap1->type - (int)ap2->type;
  }
  if( rc==0 && ap1->type==REDUCE ){
    rc = ap1->x.rp->index - ap2->x.rp->index;
  }
  if( rc==0 ){
    rc = (int) (ap2 - ap1);
  }
  return rc;
}

static struct action *Action_sort(
  struct action *ap
){
  ap = (struct action *)msort((char *)ap,(char **)&ap->next,
                              (int(*)(const char*,const char*))actioncmp);
  return ap;
}

void Action_add(
  struct action **app,
  enum e_action type,
  struct symbol *sp,
  char *arg
){
  struct action *newaction;
  newaction = Action_new();
  newaction->next = *app;
  *app = newaction;
  newaction->type = type;
  newaction->sp = sp;
  if( type==SHIFT ){
    newaction->x.stp = (struct state *)arg;
  }else{
    newaction->x.rp = (struct rule *)arg;
  }
}

struct lookahead_action {
  int lookahead;             
  int action;                
};
typedef struct acttab acttab;
struct acttab {
  int nAction;                 
  int nActionAlloc;            
  struct lookahead_action
    *aAction,                  
    *aLookahead;               
  int mnLookahead;             
  int mnAction;                
  int mxLookahead;             
  int nLookahead;              
  int nLookaheadAlloc;         
};

#define acttab_size(X) ((X)->nAction)

#define acttab_yyaction(X,N)  ((X)->aAction[N].action)

#define acttab_yylookahead(X,N)  ((X)->aAction[N].lookahead)

void acttab_free(acttab *p){
  free( p->aAction );
  free( p->aLookahead );
  free( p );
}

acttab *acttab_alloc(void){
  acttab *p = (acttab *) calloc( 1, sizeof(*p) );
  if( p==0 ){
    fprintf(stderr,"Unable to allocate memory for a new acttab.");
    exit(1);
  }
  memset(p, 0, sizeof(*p));
  return p;
}

void acttab_action(acttab *p, int lookahead, int action){
  if( p->nLookahead>=p->nLookaheadAlloc ){
    p->nLookaheadAlloc += 25;
    p->aLookahead = (struct lookahead_action *) realloc( p->aLookahead,
                             sizeof(p->aLookahead[0])*p->nLookaheadAlloc );
    if( p->aLookahead==0 ){
      fprintf(stderr,"malloc failed\n");
      exit(1);
    }
  }
  if( p->nLookahead==0 ){
    p->mxLookahead = lookahead;
    p->mnLookahead = lookahead;
    p->mnAction = action;
  }else{
    if( p->mxLookahead<lookahead ) p->mxLookahead = lookahead;
    if( p->mnLookahead>lookahead ){
      p->mnLookahead = lookahead;
      p->mnAction = action;
    }
  }
  p->aLookahead[p->nLookahead].lookahead = lookahead;
  p->aLookahead[p->nLookahead].action = action;
  p->nLookahead++;
}

int acttab_insert(acttab *p){
  int i, j, k, n;
  assert( p->nLookahead>0 );

  n = p->mxLookahead + 1;
  if( p->nAction + n >= p->nActionAlloc ){
    int oldAlloc = p->nActionAlloc;
    p->nActionAlloc = p->nAction + n + p->nActionAlloc + 20;
    p->aAction = (struct lookahead_action *) realloc( p->aAction,
                          sizeof(p->aAction[0])*p->nActionAlloc);
    if( p->aAction==0 ){
      fprintf(stderr,"malloc failed\n");
      exit(1);
    }
    for(i=oldAlloc; i<p->nActionAlloc; i++){
      p->aAction[i].lookahead = -1;
      p->aAction[i].action = -1;
    }
  }

  for(i=p->nAction-1; i>=0; i--){
    if( p->aAction[i].lookahead==p->mnLookahead ){
      if( p->aAction[i].action!=p->mnAction ) continue;
      for(j=0; j<p->nLookahead; j++){
        k = p->aLookahead[j].lookahead - p->mnLookahead + i;
        if( k<0 || k>=p->nAction ) break;
        if( p->aLookahead[j].lookahead!=p->aAction[k].lookahead ) break;
        if( p->aLookahead[j].action!=p->aAction[k].action ) break;
      }
      if( j<p->nLookahead ) continue;

      n = 0;
      for(j=0; j<p->nAction; j++){
        if( p->aAction[j].lookahead<0 ) continue;
        if( p->aAction[j].lookahead==j+p->mnLookahead-i ) n++;
      }
      if( n==p->nLookahead ){
        break;  
      }
    }
  }

  if( i<0 ){
    for(i=0; i<p->nActionAlloc - p->mxLookahead; i++){
      if( p->aAction[i].lookahead<0 ){
        for(j=0; j<p->nLookahead; j++){
          k = p->aLookahead[j].lookahead - p->mnLookahead + i;
          if( k<0 ) break;
          if( p->aAction[k].lookahead>=0 ) break;
        }
        if( j<p->nLookahead ) continue;
        for(j=0; j<p->nAction; j++){
          if( p->aAction[j].lookahead==j+p->mnLookahead-i ) break;
        }
        if( j==p->nAction ){
          break;  
        }
      }
    }
  }
  
  for(j=0; j<p->nLookahead; j++){
    k = p->aLookahead[j].lookahead - p->mnLookahead + i;
    p->aAction[k] = p->aLookahead[j];
    if( k>=p->nAction ) p->nAction = k+1;
  }
  p->nLookahead = 0;

  return i - p->mnLookahead;
}


void FindRulePrecedences(struct lemon *xp)
{
  struct rule *rp;
  for(rp=xp->rule; rp; rp=rp->next){
    if( rp->precsym==0 ){
      int i, j;
      for(i=0; i<rp->nrhs && rp->precsym==0; i++){
        struct symbol *sp = rp->rhs[i];
        if( sp->type==MULTITERMINAL ){
          for(j=0; j<sp->nsubsym; j++){
            if( sp->subsym[j]->prec>=0 ){
              rp->precsym = sp->subsym[j];
              break;
            }
          }
        }else if( sp->prec>=0 ){
          rp->precsym = rp->rhs[i];
	}
      }
    }
  }
  return;
}

void FindFirstSets(struct lemon *lemp)
{
  int i, j;
  struct rule *rp;
  int progress;

  for(i=0; i<lemp->nsymbol; i++){
    lemp->symbols[i]->lambda = LEMON_FALSE;
  }
  for(i=lemp->nterminal; i<lemp->nsymbol; i++){
    lemp->symbols[i]->firstset = SetNew();
  }

  
  do{
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      if( rp->lhs->lambda ) continue;
      for(i=0; i<rp->nrhs; i++){
         struct symbol *sp = rp->rhs[i];
         if( sp->type!=TERMINAL || sp->lambda==LEMON_FALSE ) break;
      }
      if( i==rp->nrhs ){
        rp->lhs->lambda = LEMON_TRUE;
        progress = 1;
      }
    }
  }while( progress );

  
  do{
    struct symbol *s1, *s2;
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      s1 = rp->lhs;
      for(i=0; i<rp->nrhs; i++){
        s2 = rp->rhs[i];
        if( s2->type==TERMINAL ){
          progress += SetAdd(s1->firstset,s2->index);
          break;
        }else if( s2->type==MULTITERMINAL ){
          for(j=0; j<s2->nsubsym; j++){
            progress += SetAdd(s1->firstset,s2->subsym[j]->index);
          }
          break;
	}else if( s1==s2 ){
          if( s1->lambda==LEMON_FALSE ) break;
	}else{
          progress += SetUnion(s1->firstset,s2->firstset);
          if( s2->lambda==LEMON_FALSE ) break;
	}
      }
    }
  }while( progress );
  return;
}

PRIVATE struct state *getstate(struct lemon *);  
void FindStates(struct lemon *lemp)
{
  struct symbol *sp;
  struct rule *rp;

  Configlist_init();

  
  if( lemp->start ){
    sp = Symbol_find(lemp->start);
    if( sp==0 ){
      ErrorMsg(lemp->filename,0,
"The specified start symbol \"%s\" is not \
in a nonterminal of the grammar.  \"%s\" will be used as the start \
symbol instead.",lemp->start,lemp->rule->lhs->name);
      lemp->errorcnt++;
      sp = lemp->rule->lhs;
    }
  }else{
    sp = lemp->rule->lhs;
  }

  for(rp=lemp->rule; rp; rp=rp->next){
    int i;
    for(i=0; i<rp->nrhs; i++){
      if( rp->rhs[i]==sp ){   
        ErrorMsg(lemp->filename,0,
"The start symbol \"%s\" occurs on the \
right-hand side of a rule. This will result in a parser which \
does not work properly.",sp->name);
        lemp->errorcnt++;
      }
    }
  }

  for(rp=sp->rule; rp; rp=rp->nextlhs){
    struct config *newcfp;
    rp->lhsStart = 1;
    newcfp = Configlist_addbasis(rp,0);
    SetAdd(newcfp->fws,0);
  }

  (void)getstate(lemp);
  return;
}

PRIVATE void buildshifts(struct lemon *, struct state *); 
PRIVATE struct state *getstate(struct lemon *lemp)
{
  struct config *cfp, *bp;
  struct state *stp;

  Configlist_sortbasis();
  bp = Configlist_basis();

  
  stp = State_find(bp);
  if( stp ){
    struct config *x, *y;
    for(x=bp, y=stp->bp; x && y; x=x->bp, y=y->bp){
      Plink_copy(&y->bplp,x->bplp);
      Plink_delete(x->fplp);
      x->fplp = x->bplp = 0;
    }
    cfp = Configlist_return();
    Configlist_eat(cfp);
  }else{
    
    Configlist_closure(lemp);    
    Configlist_sort();           
    cfp = Configlist_return();   
    stp = State_new();           
    MemoryCheck(stp);
    stp->bp = bp;                
    stp->cfp = cfp;              
    stp->statenum = lemp->nstate++; 
    stp->ap = 0;                 
    State_insert(stp,stp->bp);   
    buildshifts(lemp,stp);       
  }
  return stp;
}

int same_symbol(struct symbol *a, struct symbol *b)
{
  int i;
  if( a==b ) return 1;
  if( a->type!=MULTITERMINAL ) return 0;
  if( b->type!=MULTITERMINAL ) return 0;
  if( a->nsubsym!=b->nsubsym ) return 0;
  for(i=0; i<a->nsubsym; i++){
    if( a->subsym[i]!=b->subsym[i] ) return 0;
  }
  return 1;
}

PRIVATE void buildshifts(struct lemon *lemp, struct state *stp)
{
  struct config *cfp;  
  struct config *bcfp; 
  struct config *newcfg;  
  struct symbol *sp;   
  struct symbol *bsp;  
  struct state *newstp; 

  for(cfp=stp->cfp; cfp; cfp=cfp->next) cfp->status = INCOMPLETE;

  
  for(cfp=stp->cfp; cfp; cfp=cfp->next){
    if( cfp->status==COMPLETE ) continue;    
    if( cfp->dot>=cfp->rp->nrhs ) continue;  
    Configlist_reset();                      
    sp = cfp->rp->rhs[cfp->dot];             

    for(bcfp=cfp; bcfp; bcfp=bcfp->next){
      if( bcfp->status==COMPLETE ) continue;    
      if( bcfp->dot>=bcfp->rp->nrhs ) continue; 
      bsp = bcfp->rp->rhs[bcfp->dot];           
      if( !same_symbol(bsp,sp) ) continue;      
      bcfp->status = COMPLETE;                  
      newcfg = Configlist_addbasis(bcfp->rp,bcfp->dot+1);
      Plink_add(&newcfg->bplp,bcfp);
    }

    newstp = getstate(lemp);

    if( sp->type==MULTITERMINAL ){
      int i;
      for(i=0; i<sp->nsubsym; i++){
        Action_add(&stp->ap,SHIFT,sp->subsym[i],(char*)newstp);
      }
    }else{
      Action_add(&stp->ap,SHIFT,sp,(char *)newstp);
    }
  }
}

void FindLinks(struct lemon *lemp)
{
  int i;
  struct config *cfp, *other;
  struct state *stp;
  struct plink *plp;

  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    for(cfp=stp->cfp; cfp; cfp=cfp->next){
      cfp->stp = stp;
    }
  }

  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    for(cfp=stp->cfp; cfp; cfp=cfp->next){
      for(plp=cfp->bplp; plp; plp=plp->next){
        other = plp->cfp;
        Plink_add(&other->fplp,cfp);
      }
    }
  }
}

void FindFollowSets(struct lemon *lemp)
{
  int i;
  struct config *cfp;
  struct plink *plp;
  int progress;
  int change;

  for(i=0; i<lemp->nstate; i++){
    for(cfp=lemp->sorted[i]->cfp; cfp; cfp=cfp->next){
      cfp->status = INCOMPLETE;
    }
  }
  
  do{
    progress = 0;
    for(i=0; i<lemp->nstate; i++){
      for(cfp=lemp->sorted[i]->cfp; cfp; cfp=cfp->next){
        if( cfp->status==COMPLETE ) continue;
        for(plp=cfp->fplp; plp; plp=plp->next){
          change = SetUnion(plp->cfp->fws,cfp->fws);
          if( change ){
            plp->cfp->status = INCOMPLETE;
            progress = 1;
	  }
	}
        cfp->status = COMPLETE;
      }
    }
  }while( progress );
}

static int resolve_conflict(struct action *,struct action *, struct symbol *);

void FindActions(struct lemon *lemp)
{
  int i,j;
  struct config *cfp;
  struct state *stp;
  struct symbol *sp;
  struct rule *rp;

  for(i=0; i<lemp->nstate; i++){   
    stp = lemp->sorted[i];
    for(cfp=stp->cfp; cfp; cfp=cfp->next){  
      if( cfp->rp->nrhs==cfp->dot ){        
        for(j=0; j<lemp->nterminal; j++){
          if( SetFind(cfp->fws,j) ){
            Action_add(&stp->ap,REDUCE,lemp->symbols[j],(char *)cfp->rp);
          }
	}
      }
    }
  }

  
  if( lemp->start ){
    sp = Symbol_find(lemp->start);
    if( sp==0 ) sp = lemp->rule->lhs;
  }else{
    sp = lemp->rule->lhs;
  }
  Action_add(&lemp->sorted[0]->ap,ACCEPT,sp,0);

  
  for(i=0; i<lemp->nstate; i++){
    struct action *ap, *nap;
    struct state *stp;
    stp = lemp->sorted[i];
    
    stp->ap = Action_sort(stp->ap);
    for(ap=stp->ap; ap && ap->next; ap=ap->next){
      for(nap=ap->next; nap && nap->sp==ap->sp; nap=nap->next){
         lemp->nconflict += resolve_conflict(ap,nap,lemp->errsym);
      }
    }
  }

  
  for(rp=lemp->rule; rp; rp=rp->next) rp->canReduce = LEMON_FALSE;
  for(i=0; i<lemp->nstate; i++){
    struct action *ap;
    for(ap=lemp->sorted[i]->ap; ap; ap=ap->next){
      if( ap->type==REDUCE ) ap->x.rp->canReduce = LEMON_TRUE;
    }
  }
  for(rp=lemp->rule; rp; rp=rp->next){
    if( rp->canReduce ) continue;
    ErrorMsg(lemp->filename,rp->ruleline,"This rule can not be reduced.\n");
    lemp->errorcnt++;
  }
}

static int resolve_conflict(
  struct action *apx,
  struct action *apy,
  struct symbol *errsym   
){
  struct symbol *spx, *spy;
  int errcnt = 0;
  assert( apx->sp==apy->sp );  
  if( apx->type==SHIFT && apy->type==SHIFT ){
    apy->type = SSCONFLICT;
    errcnt++;
  }
  if( apx->type==SHIFT && apy->type==REDUCE ){
    spx = apx->sp;
    spy = apy->x.rp->precsym;
    if( spy==0 || spx->prec<0 || spy->prec<0 ){
      
      apy->type = SRCONFLICT;
      errcnt++;
    }else if( spx->prec>spy->prec ){    
      apy->type = RD_RESOLVED;
    }else if( spx->prec<spy->prec ){
      apx->type = SH_RESOLVED;
    }else if( spx->prec==spy->prec && spx->assoc==RIGHT ){ 
      apy->type = RD_RESOLVED;                             
    }else if( spx->prec==spy->prec && spx->assoc==LEFT ){  
      apx->type = SH_RESOLVED;
    }else{
      assert( spx->prec==spy->prec && spx->assoc==NONE );
      apy->type = SRCONFLICT;
      errcnt++;
    }
  }else if( apx->type==REDUCE && apy->type==REDUCE ){
    spx = apx->x.rp->precsym;
    spy = apy->x.rp->precsym;
    if( spx==0 || spy==0 || spx->prec<0 ||
    spy->prec<0 || spx->prec==spy->prec ){
      apy->type = RRCONFLICT;
      errcnt++;
    }else if( spx->prec>spy->prec ){
      apy->type = RD_RESOLVED;
    }else if( spx->prec<spy->prec ){
      apx->type = RD_RESOLVED;
    }
  }else{
    assert( 
      apx->type==SH_RESOLVED ||
      apx->type==RD_RESOLVED ||
      apx->type==SSCONFLICT ||
      apx->type==SRCONFLICT ||
      apx->type==RRCONFLICT ||
      apy->type==SH_RESOLVED ||
      apy->type==RD_RESOLVED ||
      apy->type==SSCONFLICT ||
      apy->type==SRCONFLICT ||
      apy->type==RRCONFLICT
    );
  }
  return errcnt;
}

static struct config *freelist = 0;      
static struct config *current = 0;       
static struct config **currentend = 0;   
static struct config *basis = 0;         
static struct config **basisend = 0;     

PRIVATE struct config *newconfig(){
  struct config *newcfg;
  if( freelist==0 ){
    int i;
    int amt = 3;
    freelist = (struct config *)calloc( amt, sizeof(struct config) );
    if( freelist==0 ){
      fprintf(stderr,"Unable to allocate memory for a new configuration.");
      exit(1);
    }
    for(i=0; i<amt-1; i++) freelist[i].next = &freelist[i+1];
    freelist[amt-1].next = 0;
  }
  newcfg = freelist;
  freelist = freelist->next;
  return newcfg;
}

PRIVATE void deleteconfig(struct config *old)
{
  old->next = freelist;
  freelist = old;
}

void Configlist_init(){
  current = 0;
  currentend = &current;
  basis = 0;
  basisend = &basis;
  Configtable_init();
  return;
}

void Configlist_reset(){
  current = 0;
  currentend = &current;
  basis = 0;
  basisend = &basis;
  Configtable_clear(0);
  return;
}

struct config *Configlist_add(
  struct rule *rp,    
  int dot             
){
  struct config *cfp, model;

  assert( currentend!=0 );
  model.rp = rp;
  model.dot = dot;
  cfp = Configtable_find(&model);
  if( cfp==0 ){
    cfp = newconfig();
    cfp->rp = rp;
    cfp->dot = dot;
    cfp->fws = SetNew();
    cfp->stp = 0;
    cfp->fplp = cfp->bplp = 0;
    cfp->next = 0;
    cfp->bp = 0;
    *currentend = cfp;
    currentend = &cfp->next;
    Configtable_insert(cfp);
  }
  return cfp;
}

struct config *Configlist_addbasis(struct rule *rp, int dot)
{
  struct config *cfp, model;

  assert( basisend!=0 );
  assert( currentend!=0 );
  model.rp = rp;
  model.dot = dot;
  cfp = Configtable_find(&model);
  if( cfp==0 ){
    cfp = newconfig();
    cfp->rp = rp;
    cfp->dot = dot;
    cfp->fws = SetNew();
    cfp->stp = 0;
    cfp->fplp = cfp->bplp = 0;
    cfp->next = 0;
    cfp->bp = 0;
    *currentend = cfp;
    currentend = &cfp->next;
    *basisend = cfp;
    basisend = &cfp->bp;
    Configtable_insert(cfp);
  }
  return cfp;
}

void Configlist_closure(struct lemon *lemp)
{
  struct config *cfp, *newcfp;
  struct rule *rp, *newrp;
  struct symbol *sp, *xsp;
  int i, dot;

  assert( currentend!=0 );
  for(cfp=current; cfp; cfp=cfp->next){
    rp = cfp->rp;
    dot = cfp->dot;
    if( dot>=rp->nrhs ) continue;
    sp = rp->rhs[dot];
    if( sp->type==NONTERMINAL ){
      if( sp->rule==0 && sp!=lemp->errsym ){
        ErrorMsg(lemp->filename,rp->line,"Nonterminal \"%s\" has no rules.",
          sp->name);
        lemp->errorcnt++;
      }
      for(newrp=sp->rule; newrp; newrp=newrp->nextlhs){
        newcfp = Configlist_add(newrp,0);
        for(i=dot+1; i<rp->nrhs; i++){
          xsp = rp->rhs[i];
          if( xsp->type==TERMINAL ){
            SetAdd(newcfp->fws,xsp->index);
            break;
          }else if( xsp->type==MULTITERMINAL ){
            int k;
            for(k=0; k<xsp->nsubsym; k++){
              SetAdd(newcfp->fws, xsp->subsym[k]->index);
            }
            break;
	  }else{
            SetUnion(newcfp->fws,xsp->firstset);
            if( xsp->lambda==LEMON_FALSE ) break;
	  }
	}
        if( i==rp->nrhs ) Plink_add(&cfp->fplp,newcfp);
      }
    }
  }
  return;
}

void Configlist_sort(){
  current = (struct config *)msort((char *)current,(char **)&(current->next),Configcmp);
  currentend = 0;
  return;
}

void Configlist_sortbasis(){
  basis = (struct config *)msort((char *)current,(char **)&(current->bp),Configcmp);
  basisend = 0;
  return;
}

struct config *Configlist_return(){
  struct config *old;
  old = current;
  current = 0;
  currentend = 0;
  return old;
}

struct config *Configlist_basis(){
  struct config *old;
  old = basis;
  basis = 0;
  basisend = 0;
  return old;
}

void Configlist_eat(struct config *cfp)
{
  struct config *nextcfp;
  for(; cfp; cfp=nextcfp){
    nextcfp = cfp->next;
    assert( cfp->fplp==0 );
    assert( cfp->bplp==0 );
    if( cfp->fws ) SetFree(cfp->fws);
    deleteconfig(cfp);
  }
  return;
}

void ErrorMsg(const char *filename, int lineno, const char *format, ...){
  va_list ap;
  fprintf(stderr, "%s:%d: ", filename, lineno);
  va_start(ap, format);
  vfprintf(stderr,format,ap);
  va_end(ap);
  fprintf(stderr, "\n");
}

void memory_error(){
  fprintf(stderr,"Out of memory.  Aborting...\n");
  exit(1);
}

static int nDefine = 0;      
static char **azDefine = 0;  

static void handle_D_option(char *z){
  char **paz;
  nDefine++;
  azDefine = (char **) realloc(azDefine, sizeof(azDefine[0])*nDefine);
  if( azDefine==0 ){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  paz = &azDefine[nDefine-1];
  *paz = (char *) malloc( lemonStrlen(z)+1 );
  if( *paz==0 ){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  strcpy(*paz, z);
  for(z=*paz; *z && *z!='='; z++){}
  *z = 0;
}

static char *user_templatename = NULL;
static void handle_T_option(char *z){
  user_templatename = (char *) malloc( lemonStrlen(z)+1 );
  if( user_templatename==0 ){
    memory_error();
  }
  strcpy(user_templatename, z);
}

int main(int argc, char **argv)
{
  static int version = 0;
  static int rpflag = 0;
  static int basisflag = 0;
  static int compress = 0;
  static int quiet = 0;
  static int statistics = 0;
  static int mhflag = 0;
  static int nolinenosflag = 0;
  static int noResort = 0;
  static struct s_options options[] = {
    {OPT_FLAG, "b", (char*)&basisflag, "Print only the basis in report."},
    {OPT_FLAG, "c", (char*)&compress, "Don't compress the action table."},
    {OPT_FSTR, "D", (char*)handle_D_option, "Define an %ifdef macro."},
    {OPT_FSTR, "T", (char*)handle_T_option, "Specify a template file."},
    {OPT_FLAG, "g", (char*)&rpflag, "Print grammar without actions."},
    {OPT_FLAG, "m", (char*)&mhflag, "Output a makeheaders compatible file."},
    {OPT_FLAG, "l", (char*)&nolinenosflag, "Do not print #line statements."},
    {OPT_FLAG, "p", (char*)&showPrecedenceConflict,
                    "Show conflicts resolved by precedence rules"},
    {OPT_FLAG, "q", (char*)&quiet, "(Quiet) Don't print the report file."},
    {OPT_FLAG, "r", (char*)&noResort, "Do not sort or renumber states"},
    {OPT_FLAG, "s", (char*)&statistics,
                                   "Print parser stats to standard output."},
    {OPT_FLAG, "x", (char*)&version, "Print the version number."},
    {OPT_FLAG,0,0,0}
  };
  int i;
  int exitcode;
  struct lemon lem;

  atexit(LemonAtExit);

  OptInit(argv,options,stderr);
  if( version ){
     printf("Lemon version 1.0\n");
     exit(0); 
  }
  if( OptNArgs()!=1 ){
    fprintf(stderr,"Exactly one filename argument is required.\n");
    exit(1);
  }
  memset(&lem, 0, sizeof(lem));
  lem.errorcnt = 0;

  
  Strsafe_init();
  Symbol_init();
  State_init();
  lem.argv0 = argv[0];
  lem.filename = OptArg(0);
  lem.basisflag = basisflag;
  lem.nolinenosflag = nolinenosflag;
  Symbol_new("$");
  lem.errsym = Symbol_new("error");
  lem.errsym->useCnt = 0;

  
  Parse(&lem);
  if( lem.errorcnt ) exit(lem.errorcnt);
  if( lem.nrule==0 ){
    fprintf(stderr,"Empty grammar.\n");
    exit(1);
  }

  
  lem.nsymbol = Symbol_count();
  Symbol_new("{default}");
  lem.symbols = Symbol_arrayof();
  for(i=0; i<=lem.nsymbol; i++) lem.symbols[i]->index = i;
  qsort(lem.symbols,lem.nsymbol+1,sizeof(struct symbol*), Symbolcmpp);
  for(i=0; i<=lem.nsymbol; i++) lem.symbols[i]->index = i;
  for(i=1; isupper(lem.symbols[i]->name[0]); i++);
  lem.nterminal = i;

  
  if( rpflag ){
    Reprint(&lem);
  }else{
    
    SetSize(lem.nterminal+1);

    
    FindRulePrecedences(&lem);

    FindFirstSets(&lem);

    lem.nstate = 0;
    FindStates(&lem);
    lem.sorted = State_arrayof();

    
    FindLinks(&lem);

    
    FindFollowSets(&lem);

    
    FindActions(&lem);

    
    if( compress==0 ) CompressTables(&lem);

    if( noResort==0 ) ResortStates(&lem);

    
    if( !quiet ) ReportOutput(&lem);

    
    ReportTable(&lem, mhflag);

    if( !mhflag ) ReportHeader(&lem);
  }
  if( statistics ){
    printf("Parser statistics: %d terminals, %d nonterminals, %d rules\n",
      lem.nterminal, lem.nsymbol - lem.nterminal, lem.nrule);
    printf("                   %d states, %d parser table entries, %d conflicts\n",
      lem.nstate, lem.tablesize, lem.nconflict);
  }
  if( lem.nconflict > 0 ){
    fprintf(stderr,"%d parsing conflicts.\n",lem.nconflict);
  }

  
  exitcode = ((lem.errorcnt > 0) || (lem.nconflict > 0)) ? 1 : 0;
  successful_exit = (exitcode == 0);
  exit(exitcode);
  return (exitcode);
}

#define NEXT(A) (*(char**)(((unsigned long)A)+offset))

static char *merge(
  char *a,
  char *b,
  int (*cmp)(const char*,const char*),
  int offset
){
  char *ptr, *head;

  if( a==0 ){
    head = b;
  }else if( b==0 ){
    head = a;
  }else{
    if( (*cmp)(a,b)<=0 ){
      ptr = a;
      a = NEXT(a);
    }else{
      ptr = b;
      b = NEXT(b);
    }
    head = ptr;
    while( a && b ){
      if( (*cmp)(a,b)<=0 ){
        NEXT(ptr) = a;
        ptr = a;
        a = NEXT(a);
      }else{
        NEXT(ptr) = b;
        ptr = b;
        b = NEXT(b);
      }
    }
    if( a ) NEXT(ptr) = a;
    else    NEXT(ptr) = b;
  }
  return head;
}

#define LISTSIZE 30
static char *msort(
  char *list,
  char **next,
  int (*cmp)(const char*,const char*)
){
  unsigned long offset;
  char *ep;
  char *set[LISTSIZE];
  int i;
  offset = (unsigned long)next - (unsigned long)list;
  for(i=0; i<LISTSIZE; i++) set[i] = 0;
  while( list ){
    ep = list;
    list = NEXT(list);
    NEXT(ep) = 0;
    for(i=0; i<LISTSIZE-1 && set[i]!=0; i++){
      ep = merge(ep,set[i],cmp,offset);
      set[i] = 0;
    }
    set[i] = ep;
  }
  ep = 0;
  for(i=0; i<LISTSIZE; i++) if( set[i] ) ep = merge(set[i],ep,cmp,offset);
  return ep;
}
static char **argv;
static struct s_options *op;
static FILE *errstream;

#define ISOPT(X) ((X)[0]=='-'||(X)[0]=='+'||strchr((X),'=')!=0)

static void errline(int n, int k, FILE *err)
{
  int spcnt, i;
  if( argv[0] ) fprintf(err,"%s",argv[0]);
  spcnt = lemonStrlen(argv[0]) + 1;
  for(i=1; i<n && argv[i]; i++){
    fprintf(err," %s",argv[i]);
    spcnt += lemonStrlen(argv[i])+1;
  }
  spcnt += k;
  for(; argv[i]; i++) fprintf(err," %s",argv[i]);
  if( spcnt<20 ){
    fprintf(err,"\n%*s^-- here\n",spcnt,"");
  }else{
    fprintf(err,"\n%*shere --^\n",spcnt-7,"");
  }
}

static int argindex(int n)
{
  int i;
  int dashdash = 0;
  if( argv!=0 && *argv!=0 ){
    for(i=1; argv[i]; i++){
      if( dashdash || !ISOPT(argv[i]) ){
        if( n==0 ) return i;
        n--;
      }
      if( strcmp(argv[i],"--")==0 ) dashdash = 1;
    }
  }
  return -1;
}

static char emsg[] = "Command line syntax error: ";

static int handleflags(int i, FILE *err)
{
  int v;
  int errcnt = 0;
  int j;
  for(j=0; op[j].label; j++){
    if( strncmp(&argv[i][1],op[j].label,lemonStrlen(op[j].label))==0 ) break;
  }
  v = argv[i][0]=='-' ? 1 : 0;
  if( op[j].label==0 ){
    if( err ){
      fprintf(err,"%sundefined option.\n",emsg);
      errline(i,1,err);
    }
    errcnt++;
  }else if( op[j].type==OPT_FLAG ){
    *((int*)op[j].arg) = v;
  }else if( op[j].type==OPT_FFLAG ){
    (*(void(*)(int))(op[j].arg))(v);
  }else if( op[j].type==OPT_FSTR ){
    (*(void(*)(char *))(op[j].arg))(&argv[i][2]);
  }else{
    if( err ){
      fprintf(err,"%smissing argument on switch.\n",emsg);
      errline(i,1,err);
    }
    errcnt++;
  }
  return errcnt;
}

static int handleswitch(int i, FILE *err)
{
  int lv = 0;
  double dv = 0.0;
  char *sv = 0, *end;
  char *cp;
  int j;
  int errcnt = 0;
  cp = strchr(argv[i],'=');
  assert( cp!=0 );
  *cp = 0;
  for(j=0; op[j].label; j++){
    if( strcmp(argv[i],op[j].label)==0 ) break;
  }
  *cp = '=';
  if( op[j].label==0 ){
    if( err ){
      fprintf(err,"%sundefined option.\n",emsg);
      errline(i,0,err);
    }
    errcnt++;
  }else{
    cp++;
    switch( op[j].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        if( err ){
          fprintf(err,"%soption requires an argument.\n",emsg);
          errline(i,0,err);
        }
        errcnt++;
        break;
      case OPT_DBL:
      case OPT_FDBL:
        dv = strtod(cp,&end);
        if( *end ){
          if( err ){
            fprintf(err,"%sillegal character in floating-point argument.\n",emsg);
            errline(i,((unsigned long)end)-(unsigned long)argv[i],err);
          }
          errcnt++;
        }
        break;
      case OPT_INT:
      case OPT_FINT:
        lv = strtol(cp,&end,0);
        if( *end ){
          if( err ){
            fprintf(err,"%sillegal character in integer argument.\n",emsg);
            errline(i,((unsigned long)end)-(unsigned long)argv[i],err);
          }
          errcnt++;
        }
        break;
      case OPT_STR:
      case OPT_FSTR:
        sv = cp;
        break;
    }
    switch( op[j].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        break;
      case OPT_DBL:
        *(double*)(op[j].arg) = dv;
        break;
      case OPT_FDBL:
        (*(void(*)(double))(op[j].arg))(dv);
        break;
      case OPT_INT:
        *(int*)(op[j].arg) = lv;
        break;
      case OPT_FINT:
        (*(void(*)(int))(op[j].arg))((int)lv);
        break;
      case OPT_STR:
        *(char**)(op[j].arg) = sv;
        break;
      case OPT_FSTR:
        (*(void(*)(char *))(op[j].arg))(sv);
        break;
    }
  }
  return errcnt;
}

int OptInit(char **a, struct s_options *o, FILE *err)
{
  int errcnt = 0;
  argv = a;
  op = o;
  errstream = err;
  if( argv && *argv && op ){
    int i;
    for(i=1; argv[i]; i++){
      if( argv[i][0]=='+' || argv[i][0]=='-' ){
        errcnt += handleflags(i,err);
      }else if( strchr(argv[i],'=') ){
        errcnt += handleswitch(i,err);
      }
    }
  }
  if( errcnt>0 ){
    fprintf(err,"Valid command line options for \"%s\" are:\n",*a);
    OptPrint();
    exit(1);
  }
  return 0;
}

int OptNArgs(){
  int cnt = 0;
  int dashdash = 0;
  int i;
  if( argv!=0 && argv[0]!=0 ){
    for(i=1; argv[i]; i++){
      if( dashdash || !ISOPT(argv[i]) ) cnt++;
      if( strcmp(argv[i],"--")==0 ) dashdash = 1;
    }
  }
  return cnt;
}

char *OptArg(int n)
{
  int i;
  i = argindex(n);
  return i>=0 ? argv[i] : 0;
}

void OptErr(int n)
{
  int i;
  i = argindex(n);
  if( i>=0 ) errline(i,0,errstream);
}

void OptPrint(){
  int i;
  int max, len;
  max = 0;
  for(i=0; op[i].label; i++){
    len = lemonStrlen(op[i].label) + 1;
    switch( op[i].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        break;
      case OPT_INT:
      case OPT_FINT:
        len += 9;       
        break;
      case OPT_DBL:
      case OPT_FDBL:
        len += 6;       
        break;
      case OPT_STR:
      case OPT_FSTR:
        len += 8;       
        break;
    }
    if( len>max ) max = len;
  }
  for(i=0; op[i].label; i++){
    switch( op[i].type ){
      case OPT_FLAG:
      case OPT_FFLAG:
        fprintf(errstream,"  -%-*s  %s\n",max,op[i].label,op[i].message);
        break;
      case OPT_INT:
      case OPT_FINT:
        fprintf(errstream,"  %s=<integer>%*s  %s\n",op[i].label,
          (int)(max-lemonStrlen(op[i].label)-9),"",op[i].message);
        break;
      case OPT_DBL:
      case OPT_FDBL:
        fprintf(errstream,"  %s=<real>%*s  %s\n",op[i].label,
          (int)(max-lemonStrlen(op[i].label)-6),"",op[i].message);
        break;
      case OPT_STR:
      case OPT_FSTR:
        fprintf(errstream,"  %s=<string>%*s  %s\n",op[i].label,
          (int)(max-lemonStrlen(op[i].label)-8),"",op[i].message);
        break;
    }
  }
}

enum e_state {
  INITIALIZE,
  WAITING_FOR_DECL_OR_RULE,
  WAITING_FOR_DECL_KEYWORD,
  WAITING_FOR_DECL_ARG,
  WAITING_FOR_PRECEDENCE_SYMBOL,
  WAITING_FOR_ARROW,
  IN_RHS,
  LHS_ALIAS_1,
  LHS_ALIAS_2,
  LHS_ALIAS_3,
  RHS_ALIAS_1,
  RHS_ALIAS_2,
  PRECEDENCE_MARK_1,
  PRECEDENCE_MARK_2,
  RESYNC_AFTER_RULE_ERROR,
  RESYNC_AFTER_DECL_ERROR,
  WAITING_FOR_DESTRUCTOR_SYMBOL,
  WAITING_FOR_DATATYPE_SYMBOL,
  WAITING_FOR_FALLBACK_ID,
  WAITING_FOR_WILDCARD_ID
};
struct pstate {
  char *filename;       
  int tokenlineno;      
  int errorcnt;         
  char *tokenstart;     
  struct lemon *gp;     
  enum e_state state;        
  struct symbol *fallback;   
  struct symbol *lhs;        
  const char *lhsalias;      
  int nrhs;                  
  struct symbol *rhs[MAXRHS];  
  const char *alias[MAXRHS]; 
  struct rule *prevrule;     
  const char *declkeyword;   
  char **declargslot;        
  int insertLineMacro;       
  int *decllinenoslot;       
  enum e_assoc declassoc;    
  int preccounter;           
  struct rule *firstrule;    
  struct rule *lastrule;     
};

static void parseonetoken(struct pstate *psp)
{
  const char *x;
  x = Strsafe(psp->tokenstart);     
#if 0
  printf("%s:%d: Token=[%s] state=%d\n",psp->filename,psp->tokenlineno,
    x,psp->state);
#endif
  switch( psp->state ){
    case INITIALIZE:
      psp->prevrule = 0;
      psp->preccounter = 0;
      psp->firstrule = psp->lastrule = 0;
      psp->gp->nrule = 0;
      
    case WAITING_FOR_DECL_OR_RULE:
      if( x[0]=='%' ){
        psp->state = WAITING_FOR_DECL_KEYWORD;
      }else if( islower(x[0]) ){
        psp->lhs = Symbol_new(x);
        psp->nrhs = 0;
        psp->lhsalias = 0;
        psp->state = WAITING_FOR_ARROW;
      }else if( x[0]=='{' ){
        if( psp->prevrule==0 ){
          ErrorMsg(psp->filename,psp->tokenlineno,
"There is no prior rule opon which to attach the code \
fragment which begins on this line.");
          psp->errorcnt++;
	}else if( psp->prevrule->code!=0 ){
          ErrorMsg(psp->filename,psp->tokenlineno,
"Code fragment beginning on this line is not the first \
to follow the previous rule.");
          psp->errorcnt++;
        }else{
          psp->prevrule->line = psp->tokenlineno;
          psp->prevrule->code = &x[1];
	}
      }else if( x[0]=='[' ){
        psp->state = PRECEDENCE_MARK_1;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Token \"%s\" should be either \"%%\" or a nonterminal name.",
          x);
        psp->errorcnt++;
      }
      break;
    case PRECEDENCE_MARK_1:
      if( !isupper(x[0]) ){
        ErrorMsg(psp->filename,psp->tokenlineno,
          "The precedence symbol must be a terminal.");
        psp->errorcnt++;
      }else if( psp->prevrule==0 ){
        ErrorMsg(psp->filename,psp->tokenlineno,
          "There is no prior rule to assign precedence \"[%s]\".",x);
        psp->errorcnt++;
      }else if( psp->prevrule->precsym!=0 ){
        ErrorMsg(psp->filename,psp->tokenlineno,
"Precedence mark on this line is not the first \
to follow the previous rule.");
        psp->errorcnt++;
      }else{
        psp->prevrule->precsym = Symbol_new(x);
      }
      psp->state = PRECEDENCE_MARK_2;
      break;
    case PRECEDENCE_MARK_2:
      if( x[0]!=']' ){
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Missing \"]\" on precedence mark.");
        psp->errorcnt++;
      }
      psp->state = WAITING_FOR_DECL_OR_RULE;
      break;
    case WAITING_FOR_ARROW:
      if( x[0]==':' && x[1]==':' && x[2]=='=' ){
        psp->state = IN_RHS;
      }else if( x[0]=='(' ){
        psp->state = LHS_ALIAS_1;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Expected to see a \":\" following the LHS symbol \"%s\".",
          psp->lhs->name);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case LHS_ALIAS_1:
      if( isalpha(x[0]) ){
        psp->lhsalias = x;
        psp->state = LHS_ALIAS_2;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "\"%s\" is not a valid alias for the LHS \"%s\"\n",
          x,psp->lhs->name);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case LHS_ALIAS_2:
      if( x[0]==')' ){
        psp->state = LHS_ALIAS_3;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Missing \")\" following LHS alias name \"%s\".",psp->lhsalias);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case LHS_ALIAS_3:
      if( x[0]==':' && x[1]==':' && x[2]=='=' ){
        psp->state = IN_RHS;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Missing \"->\" following: \"%s(%s)\".",
           psp->lhs->name,psp->lhsalias);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case IN_RHS:
      if( x[0]=='.' ){
        struct rule *rp;
        rp = (struct rule *)calloc( sizeof(struct rule) + 
             sizeof(struct symbol*)*psp->nrhs + sizeof(char*)*psp->nrhs, 1);
        if( rp==0 ){
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Can't allocate enough memory for this rule.");
          psp->errorcnt++;
          psp->prevrule = 0;
	}else{
          int i;
          rp->ruleline = psp->tokenlineno;
          rp->rhs = (struct symbol**)&rp[1];
          rp->rhsalias = (const char**)&(rp->rhs[psp->nrhs]);
          for(i=0; i<psp->nrhs; i++){
            rp->rhs[i] = psp->rhs[i];
            rp->rhsalias[i] = psp->alias[i];
	  }
          rp->lhs = psp->lhs;
          rp->lhsalias = psp->lhsalias;
          rp->nrhs = psp->nrhs;
          rp->code = 0;
          rp->precsym = 0;
          rp->index = psp->gp->nrule++;
          rp->nextlhs = rp->lhs->rule;
          rp->lhs->rule = rp;
          rp->next = 0;
          if( psp->firstrule==0 ){
            psp->firstrule = psp->lastrule = rp;
	  }else{
            psp->lastrule->next = rp;
            psp->lastrule = rp;
	  }
          psp->prevrule = rp;
	}
        psp->state = WAITING_FOR_DECL_OR_RULE;
      }else if( isalpha(x[0]) ){
        if( psp->nrhs>=MAXRHS ){
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Too many symbols on RHS of rule beginning at \"%s\".",
            x);
          psp->errorcnt++;
          psp->state = RESYNC_AFTER_RULE_ERROR;
	}else{
          psp->rhs[psp->nrhs] = Symbol_new(x);
          psp->alias[psp->nrhs] = 0;
          psp->nrhs++;
	}
      }else if( (x[0]=='|' || x[0]=='/') && psp->nrhs>0 ){
        struct symbol *msp = psp->rhs[psp->nrhs-1];
        if( msp->type!=MULTITERMINAL ){
          struct symbol *origsp = msp;
          msp = (struct symbol *) calloc(1,sizeof(*msp));
          memset(msp, 0, sizeof(*msp));
          msp->type = MULTITERMINAL;
          msp->nsubsym = 1;
          msp->subsym = (struct symbol **) calloc(1,sizeof(struct symbol*));
          msp->subsym[0] = origsp;
          msp->name = origsp->name;
          psp->rhs[psp->nrhs-1] = msp;
        }
        msp->nsubsym++;
        msp->subsym = (struct symbol **) realloc(msp->subsym,
          sizeof(struct symbol*)*msp->nsubsym);
        msp->subsym[msp->nsubsym-1] = Symbol_new(&x[1]);
        if( islower(x[1]) || islower(msp->subsym[0]->name[0]) ){
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Cannot form a compound containing a non-terminal");
          psp->errorcnt++;
        }
      }else if( x[0]=='(' && psp->nrhs>0 ){
        psp->state = RHS_ALIAS_1;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Illegal character on RHS of rule: \"%s\".",x);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case RHS_ALIAS_1:
      if( isalpha(x[0]) ){
        psp->alias[psp->nrhs-1] = x;
        psp->state = RHS_ALIAS_2;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "\"%s\" is not a valid alias for the RHS symbol \"%s\"\n",
          x,psp->rhs[psp->nrhs-1]->name);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case RHS_ALIAS_2:
      if( x[0]==')' ){
        psp->state = IN_RHS;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Missing \")\" following LHS alias name \"%s\".",psp->lhsalias);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_RULE_ERROR;
      }
      break;
    case WAITING_FOR_DECL_KEYWORD:
      if( isalpha(x[0]) ){
        psp->declkeyword = x;
        psp->declargslot = 0;
        psp->decllinenoslot = 0;
        psp->insertLineMacro = 1;
        psp->state = WAITING_FOR_DECL_ARG;
        if( strcmp(x,"name")==0 ){
          psp->declargslot = &(psp->gp->name);
          psp->insertLineMacro = 0;
	}else if( strcmp(x,"include")==0 ){
          psp->declargslot = &(psp->gp->include);
	}else if( strcmp(x,"code")==0 ){
          psp->declargslot = &(psp->gp->extracode);
	}else if( strcmp(x,"token_destructor")==0 ){
          psp->declargslot = &psp->gp->tokendest;
	}else if( strcmp(x,"default_destructor")==0 ){
          psp->declargslot = &psp->gp->vardest;
	}else if( strcmp(x,"token_prefix")==0 ){
          psp->declargslot = &psp->gp->tokenprefix;
          psp->insertLineMacro = 0;
	}else if( strcmp(x,"syntax_error")==0 ){
          psp->declargslot = &(psp->gp->error);
	}else if( strcmp(x,"parse_accept")==0 ){
          psp->declargslot = &(psp->gp->accept);
	}else if( strcmp(x,"parse_failure")==0 ){
          psp->declargslot = &(psp->gp->failure);
	}else if( strcmp(x,"stack_overflow")==0 ){
          psp->declargslot = &(psp->gp->overflow);
        }else if( strcmp(x,"extra_argument")==0 ){
          psp->declargslot = &(psp->gp->arg);
          psp->insertLineMacro = 0;
        }else if( strcmp(x,"token_type")==0 ){
          psp->declargslot = &(psp->gp->tokentype);
          psp->insertLineMacro = 0;
        }else if( strcmp(x,"default_type")==0 ){
          psp->declargslot = &(psp->gp->vartype);
          psp->insertLineMacro = 0;
        }else if( strcmp(x,"stack_size")==0 ){
          psp->declargslot = &(psp->gp->stacksize);
          psp->insertLineMacro = 0;
        }else if( strcmp(x,"start_symbol")==0 ){
          psp->declargslot = &(psp->gp->start);
          psp->insertLineMacro = 0;
        }else if( strcmp(x,"left")==0 ){
          psp->preccounter++;
          psp->declassoc = LEFT;
          psp->state = WAITING_FOR_PRECEDENCE_SYMBOL;
        }else if( strcmp(x,"right")==0 ){
          psp->preccounter++;
          psp->declassoc = RIGHT;
          psp->state = WAITING_FOR_PRECEDENCE_SYMBOL;
        }else if( strcmp(x,"nonassoc")==0 ){
          psp->preccounter++;
          psp->declassoc = NONE;
          psp->state = WAITING_FOR_PRECEDENCE_SYMBOL;
	}else if( strcmp(x,"destructor")==0 ){
          psp->state = WAITING_FOR_DESTRUCTOR_SYMBOL;
	}else if( strcmp(x,"type")==0 ){
          psp->state = WAITING_FOR_DATATYPE_SYMBOL;
        }else if( strcmp(x,"fallback")==0 ){
          psp->fallback = 0;
          psp->state = WAITING_FOR_FALLBACK_ID;
        }else if( strcmp(x,"wildcard")==0 ){
          psp->state = WAITING_FOR_WILDCARD_ID;
        }else{
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Unknown declaration keyword: \"%%%s\".",x);
          psp->errorcnt++;
          psp->state = RESYNC_AFTER_DECL_ERROR;
	}
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Illegal declaration keyword: \"%s\".",x);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_DECL_ERROR;
      }
      break;
    case WAITING_FOR_DESTRUCTOR_SYMBOL:
      if( !isalpha(x[0]) ){
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Symbol name missing after %%destructor keyword");
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_DECL_ERROR;
      }else{
        struct symbol *sp = Symbol_new(x);
        psp->declargslot = &sp->destructor;
        psp->decllinenoslot = &sp->destLineno;
        psp->insertLineMacro = 1;
        psp->state = WAITING_FOR_DECL_ARG;
      }
      break;
    case WAITING_FOR_DATATYPE_SYMBOL:
      if( !isalpha(x[0]) ){
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Symbol name missing after %%type keyword");
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_DECL_ERROR;
      }else{
        struct symbol *sp = Symbol_find(x);
        if((sp) && (sp->datatype)){
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Symbol %%type \"%s\" already defined", x);
          psp->errorcnt++;
          psp->state = RESYNC_AFTER_DECL_ERROR;
        }else{
          if (!sp){
            sp = Symbol_new(x);
          }
          psp->declargslot = &sp->datatype;
          psp->insertLineMacro = 0;
          psp->state = WAITING_FOR_DECL_ARG;
        }
      }
      break;
    case WAITING_FOR_PRECEDENCE_SYMBOL:
      if( x[0]=='.' ){
        psp->state = WAITING_FOR_DECL_OR_RULE;
      }else if( isupper(x[0]) ){
        struct symbol *sp;
        sp = Symbol_new(x);
        if( sp->prec>=0 ){
          ErrorMsg(psp->filename,psp->tokenlineno,
            "Symbol \"%s\" has already be given a precedence.",x);
          psp->errorcnt++;
	}else{
          sp->prec = psp->preccounter;
          sp->assoc = psp->declassoc;
	}
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Can't assign a precedence to \"%s\".",x);
        psp->errorcnt++;
      }
      break;
    case WAITING_FOR_DECL_ARG:
      if( x[0]=='{' || x[0]=='\"' || isalnum(x[0]) ){
        const char *zOld, *zNew;
        char *zBuf, *z;
        int nOld, n, nLine, nNew, nBack;
        int addLineMacro;
        char zLine[50];
        zNew = x;
        if( zNew[0]=='"' || zNew[0]=='{' ) zNew++;
        nNew = lemonStrlen(zNew);
        if( *psp->declargslot ){
          zOld = *psp->declargslot;
        }else{
          zOld = "";
        }
        nOld = lemonStrlen(zOld);
        n = nOld + nNew + 20;
        addLineMacro = !psp->gp->nolinenosflag && psp->insertLineMacro &&
                        (psp->decllinenoslot==0 || psp->decllinenoslot[0]!=0);
        if( addLineMacro ){
          for(z=psp->filename, nBack=0; *z; z++){
            if( *z=='\\' ) nBack++;
          }
          sprintf(zLine, "#line %d ", psp->tokenlineno);
          nLine = lemonStrlen(zLine);
          n += nLine + lemonStrlen(psp->filename) + nBack;
        }
        *psp->declargslot = (char *) realloc(*psp->declargslot, n);
        zBuf = *psp->declargslot + nOld;
        if( addLineMacro ){
          if( nOld && zBuf[-1]!='\n' ){
            *(zBuf++) = '\n';
          }
          memcpy(zBuf, zLine, nLine);
          zBuf += nLine;
          *(zBuf++) = '"';
          for(z=psp->filename; *z; z++){
            if( *z=='\\' ){
              *(zBuf++) = '\\';
            }
            *(zBuf++) = *z;
          }
          *(zBuf++) = '"';
          *(zBuf++) = '\n';
        }
        if( psp->decllinenoslot && psp->decllinenoslot[0]==0 ){
          psp->decllinenoslot[0] = psp->tokenlineno;
        }
        memcpy(zBuf, zNew, nNew);
        zBuf += nNew;
        *zBuf = 0;
        psp->state = WAITING_FOR_DECL_OR_RULE;
      }else{
        ErrorMsg(psp->filename,psp->tokenlineno,
          "Illegal argument to %%%s: %s",psp->declkeyword,x);
        psp->errorcnt++;
        psp->state = RESYNC_AFTER_DECL_ERROR;
      }
      break;
    case WAITING_FOR_FALLBACK_ID:
      if( x[0]=='.' ){
        psp->state = WAITING_FOR_DECL_OR_RULE;
      }else if( !isupper(x[0]) ){
        ErrorMsg(psp->filename, psp->tokenlineno,
          "%%fallback argument \"%s\" should be a token", x);
        psp->errorcnt++;
      }else{
        struct symbol *sp = Symbol_new(x);
        if( psp->fallback==0 ){
          psp->fallback = sp;
        }else if( sp->fallback ){
          ErrorMsg(psp->filename, psp->tokenlineno,
            "More than one fallback assigned to token %s", x);
          psp->errorcnt++;
        }else{
          sp->fallback = psp->fallback;
          psp->gp->has_fallback = 1;
        }
      }
      break;
    case WAITING_FOR_WILDCARD_ID:
      if( x[0]=='.' ){
        psp->state = WAITING_FOR_DECL_OR_RULE;
      }else if( !isupper(x[0]) ){
        ErrorMsg(psp->filename, psp->tokenlineno,
          "%%wildcard argument \"%s\" should be a token", x);
        psp->errorcnt++;
      }else{
        struct symbol *sp = Symbol_new(x);
        if( psp->gp->wildcard==0 ){
          psp->gp->wildcard = sp;
        }else{
          ErrorMsg(psp->filename, psp->tokenlineno,
            "Extra wildcard to token: %s", x);
          psp->errorcnt++;
        }
      }
      break;
    case RESYNC_AFTER_RULE_ERROR:
    case RESYNC_AFTER_DECL_ERROR:
      if( x[0]=='.' ) psp->state = WAITING_FOR_DECL_OR_RULE;
      if( x[0]=='%' ) psp->state = WAITING_FOR_DECL_KEYWORD;
      break;
  }
}

static void preprocess_input(char *z){
  int i, j, k, n;
  int exclude = 0;
  int start = 0;
  int lineno = 1;
  int start_lineno = 1;
  for(i=0; z[i]; i++){
    if( z[i]=='\n' ) lineno++;
    if( z[i]!='%' || (i>0 && z[i-1]!='\n') ) continue;
    if( strncmp(&z[i],"%endif",6)==0 && isspace(z[i+6]) ){
      if( exclude ){
        exclude--;
        if( exclude==0 ){
          for(j=start; j<i; j++) if( z[j]!='\n' ) z[j] = ' ';
        }
      }
      for(j=i; z[j] && z[j]!='\n'; j++) z[j] = ' ';
    }else if( (strncmp(&z[i],"%ifdef",6)==0 && isspace(z[i+6]))
          || (strncmp(&z[i],"%ifndef",7)==0 && isspace(z[i+7])) ){
      if( exclude ){
        exclude++;
      }else{
        for(j=i+7; isspace(z[j]); j++){}
        for(n=0; z[j+n] && !isspace(z[j+n]); n++){}
        exclude = 1;
        for(k=0; k<nDefine; k++){
          if( strncmp(azDefine[k],&z[j],n)==0 && lemonStrlen(azDefine[k])==n ){
            exclude = 0;
            break;
          }
        }
        if( z[i+3]=='n' ) exclude = !exclude;
        if( exclude ){
          start = i;
          start_lineno = lineno;
        }
      }
      for(j=i; z[j] && z[j]!='\n'; j++) z[j] = ' ';
    }
  }
  if( exclude ){
    fprintf(stderr,"unterminated %%ifdef starting on line %d\n", start_lineno);
    exit(1);
  }
}

void Parse(struct lemon *gp)
{
  struct pstate ps;
  FILE *fp;
  char *filebuf;
  int filesize;
  int lineno;
  int c;
  char *cp, *nextcp;
  int startline = 0;

  memset(&ps, '\0', sizeof(ps));
  ps.gp = gp;
  ps.filename = gp->filename;
  ps.errorcnt = 0;
  ps.state = INITIALIZE;

  
  fp = fopen(ps.filename,"rb");
  if( fp==0 ){
    ErrorMsg(ps.filename,0,"Can't open this file for reading.");
    gp->errorcnt++;
    return;
  }
  fseek(fp,0,2);
  filesize = ftell(fp);
  rewind(fp);
  filebuf = (char *)malloc( filesize+1 );
  if( filebuf==0 ){
    ErrorMsg(ps.filename,0,"Can't allocate %d of memory to hold this file.",
      filesize+1);
    gp->errorcnt++;
    return;
  }
  if( fread(filebuf,1,filesize,fp)!=filesize ){
    ErrorMsg(ps.filename,0,"Can't read in all %d bytes of this file.",
      filesize);
    free(filebuf);
    gp->errorcnt++;
    return;
  }
  fclose(fp);
  filebuf[filesize] = 0;

  
  preprocess_input(filebuf);

  
  lineno = 1;
  for(cp=filebuf; (c= *cp)!=0; ){
    if( c=='\n' ) lineno++;              
    if( isspace(c) ){ cp++; continue; }  
    if( c=='/' && cp[1]=='/' ){          
      cp+=2;
      while( (c= *cp)!=0 && c!='\n' ) cp++;
      continue;
    }
    if( c=='/' && cp[1]=='*' ){          
      cp+=2;
      while( (c= *cp)!=0 && (c!='/' || cp[-1]!='*') ){
        if( c=='\n' ) lineno++;
        cp++;
      }
      if( c ) cp++;
      continue;
    }
    ps.tokenstart = cp;                
    ps.tokenlineno = lineno;           
    if( c=='\"' ){                     
      cp++;
      while( (c= *cp)!=0 && c!='\"' ){
        if( c=='\n' ) lineno++;
        cp++;
      }
      if( c==0 ){
        ErrorMsg(ps.filename,startline,
"String starting on this line is not terminated before the end of the file.");
        ps.errorcnt++;
        nextcp = cp;
      }else{
        nextcp = cp+1;
      }
    }else if( c=='{' ){               
      int level;
      cp++;
      for(level=1; (c= *cp)!=0 && (level>1 || c!='}'); cp++){
        if( c=='\n' ) lineno++;
        else if( c=='{' ) level++;
        else if( c=='}' ) level--;
        else if( c=='/' && cp[1]=='*' ){  
          int prevc;
          cp = &cp[2];
          prevc = 0;
          while( (c= *cp)!=0 && (c!='/' || prevc!='*') ){
            if( c=='\n' ) lineno++;
            prevc = c;
            cp++;
	  }
	}else if( c=='/' && cp[1]=='/' ){  
          cp = &cp[2];
          while( (c= *cp)!=0 && c!='\n' ) cp++;
          if( c ) lineno++;
	}else if( c=='\'' || c=='\"' ){    
          int startchar, prevc;
          startchar = c;
          prevc = 0;
          for(cp++; (c= *cp)!=0 && (c!=startchar || prevc=='\\'); cp++){
            if( c=='\n' ) lineno++;
            if( prevc=='\\' ) prevc = 0;
            else              prevc = c;
	  }
	}
      }
      if( c==0 ){
        ErrorMsg(ps.filename,ps.tokenlineno,
"C code starting on this line is not terminated before the end of the file.");
        ps.errorcnt++;
        nextcp = cp;
      }else{
        nextcp = cp+1;
      }
    }else if( isalnum(c) ){          
      while( (c= *cp)!=0 && (isalnum(c) || c=='_') ) cp++;
      nextcp = cp;
    }else if( c==':' && cp[1]==':' && cp[2]=='=' ){ 
      cp += 3;
      nextcp = cp;
    }else if( (c=='/' || c=='|') && isalpha(cp[1]) ){
      cp += 2;
      while( (c = *cp)!=0 && (isalnum(c) || c=='_') ) cp++;
      nextcp = cp;
    }else{                          
      cp++;
      nextcp = cp;
    }
    c = *cp;
    *cp = 0;                        
    parseonetoken(&ps);             
    *cp = c;                        
    cp = nextcp;
  }
  free(filebuf);                    
  gp->rule = ps.firstrule;
  gp->errorcnt = ps.errorcnt;
}
static struct plink *plink_freelist = 0;

struct plink *Plink_new(){
  struct plink *newlink;

  if( plink_freelist==0 ){
    int i;
    int amt = 100;
    plink_freelist = (struct plink *)calloc( amt, sizeof(struct plink) );
    if( plink_freelist==0 ){
      fprintf(stderr,
      "Unable to allocate memory for a new follow-set propagation link.\n");
      exit(1);
    }
    for(i=0; i<amt-1; i++) plink_freelist[i].next = &plink_freelist[i+1];
    plink_freelist[amt-1].next = 0;
  }
  newlink = plink_freelist;
  plink_freelist = plink_freelist->next;
  return newlink;
}

void Plink_add(struct plink **plpp, struct config *cfp)
{
  struct plink *newlink;
  newlink = Plink_new();
  newlink->next = *plpp;
  *plpp = newlink;
  newlink->cfp = cfp;
}

void Plink_copy(struct plink **to, struct plink *from)
{
  struct plink *nextpl;
  while( from ){
    nextpl = from->next;
    from->next = *to;
    *to = from;
    from = nextpl;
  }
}

void Plink_delete(struct plink *plp)
{
  struct plink *nextpl;

  while( plp ){
    nextpl = plp->next;
    plp->next = plink_freelist;
    plink_freelist = plp;
    plp = nextpl;
  }
}

PRIVATE char *file_makename(struct lemon *lemp, const char *suffix)
{
  char *name;
  char *cp;

  name = (char*)malloc( lemonStrlen(lemp->filename) + lemonStrlen(suffix) + 5 );
  if( name==0 ){
    fprintf(stderr,"Can't allocate space for a filename.\n");
    exit(1);
  }
  strcpy(name,lemp->filename);
  cp = strrchr(name,'.');
  if( cp ) *cp = 0;
  strcat(name,suffix);
  return name;
}

PRIVATE FILE *file_open(
  struct lemon *lemp,
  const char *suffix,
  const char *mode
){
  FILE *fp;

  if( lemp->outname ) free(lemp->outname);
  lemp->outname = file_makename(lemp, suffix);
  fp = fopen(lemp->outname,mode);
  if( fp==0 && *mode=='w' ){
    fprintf(stderr,"Can't open file \"%s\".\n",lemp->outname);
    lemp->errorcnt++;
    return 0;
  }

  if(( *mode=='w' ) && (strcmp(suffix, ".out") != 0)){
    const char **ptr = (const char **)
        realloc(made_files, sizeof (const char **) * (made_files_count + 1));
    const char *fname = Strsafe(lemp->outname);
    if ((ptr == NULL) || (fname == NULL)) {
        free(ptr);
        memory_error();
    }
    made_files = ptr;
    made_files[made_files_count++] = fname;
  }
  return fp;
}

void Reprint(struct lemon *lemp)
{
  struct rule *rp;
  struct symbol *sp;
  int i, j, maxlen, len, ncolumns, skip;
  printf("// Reprint of input file \"%s\".\n// Symbols:\n",lemp->filename);
  maxlen = 10;
  for(i=0; i<lemp->nsymbol; i++){
    sp = lemp->symbols[i];
    len = lemonStrlen(sp->name);
    if( len>maxlen ) maxlen = len;
  }
  ncolumns = 76/(maxlen+5);
  if( ncolumns<1 ) ncolumns = 1;
  skip = (lemp->nsymbol + ncolumns - 1)/ncolumns;
  for(i=0; i<skip; i++){
    printf("//");
    for(j=i; j<lemp->nsymbol; j+=skip){
      sp = lemp->symbols[j];
      assert( sp->index==j );
      printf(" %3d %-*.*s",j,maxlen,maxlen,sp->name);
    }
    printf("\n");
  }
  for(rp=lemp->rule; rp; rp=rp->next){
    printf("%s",rp->lhs->name);
    
    printf(" ::=");
    for(i=0; i<rp->nrhs; i++){
      sp = rp->rhs[i];
      printf(" %s", sp->name);
      if( sp->type==MULTITERMINAL ){
        for(j=1; j<sp->nsubsym; j++){
          printf("|%s", sp->subsym[j]->name);
        }
      }
      
    }
    printf(".");
    if( rp->precsym ) printf(" [%s]",rp->precsym->name);
    
    printf("\n");
  }
}

void ConfigPrint(FILE *fp, struct config *cfp)
{
  struct rule *rp;
  struct symbol *sp;
  int i, j;
  rp = cfp->rp;
  fprintf(fp,"%s ::=",rp->lhs->name);
  for(i=0; i<=rp->nrhs; i++){
    if( i==cfp->dot ) fprintf(fp," *");
    if( i==rp->nrhs ) break;
    sp = rp->rhs[i];
    fprintf(fp," %s", sp->name);
    if( sp->type==MULTITERMINAL ){
      for(j=1; j<sp->nsubsym; j++){
        fprintf(fp,"|%s",sp->subsym[j]->name);
      }
    }
  }
}

#if 0
PRIVATE void SetPrint(out,set,lemp)
FILE *out;
char *set;
struct lemon *lemp;
{
  int i;
  char *spacer;
  spacer = "";
  fprintf(out,"%12s[","");
  for(i=0; i<lemp->nterminal; i++){
    if( SetFind(set,i) ){
      fprintf(out,"%s%s",spacer,lemp->symbols[i]->name);
      spacer = " ";
    }
  }
  fprintf(out,"]\n");
}

PRIVATE void PlinkPrint(out,plp,tag)
FILE *out;
struct plink *plp;
char *tag;
{
  while( plp ){
    fprintf(out,"%12s%s (state %2d) ","",tag,plp->cfp->stp->statenum);
    ConfigPrint(out,plp->cfp);
    fprintf(out,"\n");
    plp = plp->next;
  }
}
#endif

int PrintAction(struct action *ap, FILE *fp, int indent){
  int result = 1;
  switch( ap->type ){
    case SHIFT:
      fprintf(fp,"%*s shift  %d",indent,ap->sp->name,ap->x.stp->statenum);
      break;
    case REDUCE:
      fprintf(fp,"%*s reduce %d",indent,ap->sp->name,ap->x.rp->index);
      break;
    case ACCEPT:
      fprintf(fp,"%*s accept",indent,ap->sp->name);
      break;
    case ERROR:
      fprintf(fp,"%*s error",indent,ap->sp->name);
      break;
    case SRCONFLICT:
    case RRCONFLICT:
      fprintf(fp,"%*s reduce %-3d ** Parsing conflict **",
        indent,ap->sp->name,ap->x.rp->index);
      break;
    case SSCONFLICT:
      fprintf(fp,"%*s shift  %-3d ** Parsing conflict **", 
        indent,ap->sp->name,ap->x.stp->statenum);
      break;
    case SH_RESOLVED:
      if( showPrecedenceConflict ){
        fprintf(fp,"%*s shift  %-3d -- dropped by precedence",
                indent,ap->sp->name,ap->x.stp->statenum);
      }else{
        result = 0;
      }
      break;
    case RD_RESOLVED:
      if( showPrecedenceConflict ){
        fprintf(fp,"%*s reduce %-3d -- dropped by precedence",
                indent,ap->sp->name,ap->x.rp->index);
      }else{
        result = 0;
      }
      break;
    case NOT_USED:
      result = 0;
      break;
  }
  return result;
}

void ReportOutput(struct lemon *lemp)
{
  int i;
  struct state *stp;
  struct config *cfp;
  struct action *ap;
  FILE *fp;

  fp = file_open(lemp,".out","wb");
  if( fp==0 ) return;
  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    fprintf(fp,"State %d:\n",stp->statenum);
    if( lemp->basisflag ) cfp=stp->bp;
    else                  cfp=stp->cfp;
    while( cfp ){
      char buf[20];
      if( cfp->dot==cfp->rp->nrhs ){
        sprintf(buf,"(%d)",cfp->rp->index);
        fprintf(fp,"    %5s ",buf);
      }else{
        fprintf(fp,"          ");
      }
      ConfigPrint(fp,cfp);
      fprintf(fp,"\n");
#if 0
      SetPrint(fp,cfp->fws,lemp);
      PlinkPrint(fp,cfp->fplp,"To  ");
      PlinkPrint(fp,cfp->bplp,"From");
#endif
      if( lemp->basisflag ) cfp=cfp->bp;
      else                  cfp=cfp->next;
    }
    fprintf(fp,"\n");
    for(ap=stp->ap; ap; ap=ap->next){
      if( PrintAction(ap,fp,30) ) fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
  }
  fprintf(fp, "----------------------------------------------------\n");
  fprintf(fp, "Symbols:\n");
  for(i=0; i<lemp->nsymbol; i++){
    int j;
    struct symbol *sp;

    sp = lemp->symbols[i];
    fprintf(fp, "  %3d: %s", i, sp->name);
    if( sp->type==NONTERMINAL ){
      fprintf(fp, ":");
      if( sp->lambda ){
        fprintf(fp, " <lambda>");
      }
      for(j=0; j<lemp->nterminal; j++){
        if( sp->firstset && SetFind(sp->firstset, j) ){
          fprintf(fp, " %s", lemp->symbols[j]->name);
        }
      }
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return;
}

PRIVATE char *pathsearch(char *argv0, char *name, int modemask)
{
  const char *pathlist;
  char *pathbufptr;
  char *pathbuf;
  char *path,*cp;
  char c;

#ifdef __WIN32__
  cp = strrchr(argv0,'\\');
#else
  cp = strrchr(argv0,'/');
#endif
  if( cp ){
    c = *cp;
    *cp = 0;
    path = (char *)malloc( lemonStrlen(argv0) + lemonStrlen(name) + 2 );
    if( path ) sprintf(path,"%s/%s",argv0,name);
    *cp = c;
  }else{
    pathlist = getenv("PATH");
    if( pathlist==0 ) pathlist = ".:/bin:/usr/bin";
    pathbuf = (char *) malloc( lemonStrlen(pathlist) + 1 );
    path = (char *)malloc( lemonStrlen(pathlist)+lemonStrlen(name)+2 );
    if( (pathbuf != 0) && (path!=0) ){
      pathbufptr = pathbuf;
      strcpy(pathbuf, pathlist);
      while( *pathbuf ){
        cp = strchr(pathbuf,':');
        if( cp==0 ) cp = &pathbuf[lemonStrlen(pathbuf)];
        c = *cp;
        *cp = 0;
        sprintf(path,"%s/%s",pathbuf,name);
        *cp = c;
        if( c==0 ) pathbuf[0] = 0;
        else pathbuf = &cp[1];
        if( access(path,modemask)==0 ) break;
      }
      free(pathbufptr);
    }
  }
  return path;
}

PRIVATE int compute_action(struct lemon *lemp, struct action *ap)
{
  int act;
  switch( ap->type ){
    case SHIFT:  act = ap->x.stp->statenum;            break;
    case REDUCE: act = ap->x.rp->index + lemp->nstate; break;
    case ERROR:  act = lemp->nstate + lemp->nrule;     break;
    case ACCEPT: act = lemp->nstate + lemp->nrule + 1; break;
    default:     act = -1; break;
  }
  return act;
}

#define LINESIZE 1000
PRIVATE void tplt_xfer(char *name, FILE *in, FILE *out, int *lineno)
{
  int i, iStart;
  char line[LINESIZE];
  while( fgets(line,LINESIZE,in) && (line[0]!='%' || line[1]!='%') ){
    (*lineno)++;
    iStart = 0;
    if( name ){
      for(i=0; line[i]; i++){
        if( line[i]=='P' && strncmp(&line[i],"Parse",5)==0
          && (i==0 || !isalpha(line[i-1]))
        ){
          if( i>iStart ) fprintf(out,"%.*s",i-iStart,&line[iStart]);
          fprintf(out,"%s",name);
          i += 4;
          iStart = i+1;
        }
      }
    }
    fprintf(out,"%s",&line[iStart]);
  }
}

PRIVATE FILE *tplt_open(struct lemon *lemp)
{
  static char templatename[] = "lempar.c";
  char buf[1000];
  FILE *in;
  char *tpltname;
  char *cp;

  
  if (user_templatename != 0) {
    if( access(user_templatename,004)==-1 ){
      fprintf(stderr,"Can't find the parser driver template file \"%s\".\n",
        user_templatename);
      lemp->errorcnt++;
      return 0;
    }
    in = fopen(user_templatename,"rb");
    if( in==0 ){
      fprintf(stderr,"Can't open the template file \"%s\".\n",user_templatename);
      lemp->errorcnt++;
      return 0;
    }
    return in;
  }

  cp = strrchr(lemp->filename,'.');
  if( cp ){
    sprintf(buf,"%.*s.lt",(int)(cp-lemp->filename),lemp->filename);
  }else{
    sprintf(buf,"%s.lt",lemp->filename);
  }
  if( access(buf,004)==0 ){
    tpltname = buf;
  }else if( access(templatename,004)==0 ){
    tpltname = templatename;
  }else{
    tpltname = pathsearch(lemp->argv0,templatename,0);
  }
  if( tpltname==0 ){
    fprintf(stderr,"Can't find the parser driver template file \"%s\".\n",
    templatename);
    lemp->errorcnt++;
    return 0;
  }
  in = fopen(tpltname,"rb");
  if( in==0 ){
    fprintf(stderr,"Can't open the template file \"%s\".\n",templatename);
    lemp->errorcnt++;
    return 0;
  }
  return in;
}

PRIVATE void tplt_linedir(FILE *out, int lineno, char *filename)
{
  fprintf(out,"#line %d \"",lineno);
  while( *filename ){
    if( *filename == '\\' ) putc('\\',out);
    putc(*filename,out);
    filename++;
  }
  fprintf(out,"\"\n");
}

PRIVATE void tplt_print(FILE *out, struct lemon *lemp, char *str, int *lineno)
{
  if( str==0 ) return;
  while( *str ){
    putc(*str,out);
    if( *str=='\n' ) (*lineno)++;
    str++;
  }
  if( str[-1]!='\n' ){
    putc('\n',out);
    (*lineno)++;
  }
  if (!lemp->nolinenosflag) {
    (*lineno)++; tplt_linedir(out,*lineno,lemp->outname); 
  }
  return;
}

void emit_destructor_code(
  FILE *out,
  struct symbol *sp,
  struct lemon *lemp,
  int *lineno
){
 char *cp = 0;

 if( sp->type==TERMINAL ){
   cp = lemp->tokendest;
   if( cp==0 ) return;
   fprintf(out,"{\n"); (*lineno)++;
 }else if( sp->destructor ){
   cp = sp->destructor;
   fprintf(out,"{\n"); (*lineno)++;
   if (!lemp->nolinenosflag) { (*lineno)++; tplt_linedir(out,sp->destLineno,lemp->filename); }
 }else if( lemp->vardest ){
   cp = lemp->vardest;
   if( cp==0 ) return;
   fprintf(out,"{\n"); (*lineno)++;
 }else{
   assert( 0 );  
 }
 for(; *cp; cp++){
   if( *cp=='$' && cp[1]=='$' ){
     fprintf(out,"(yypminor->yy%d)",sp->dtnum);
     cp++;
     continue;
   }
   if( *cp=='\n' ) (*lineno)++;
   fputc(*cp,out);
 }
 fprintf(out,"\n"); (*lineno)++;
 if (!lemp->nolinenosflag) { 
   (*lineno)++; tplt_linedir(out,*lineno,lemp->outname); 
 }
 fprintf(out,"}\n"); (*lineno)++;
 return;
}

int has_destructor(struct symbol *sp, struct lemon *lemp)
{
  int ret;
  if( sp->type==TERMINAL ){
    ret = lemp->tokendest!=0;
  }else{
    ret = lemp->vardest!=0 || sp->destructor!=0;
  }
  return ret;
}

/*
** Append text to a dynamically allocated string.  If zText is 0 then
** reset the string to be empty again.  Always return the complete text
** of the string (which is overwritten with each call).
**
** n bytes of zText are stored.  If n==0 then all of zText up to the first
** \000 terminator is stored.  zText can contain up to two instances of
** %d.  The values of p1 and p2 are written into the first and second
** %d.
**
** If n==-1, then the previous character is overwritten.
*/
PRIVATE char *append_str(const char *zText, int n, int p1, int p2){
  static char empty[1] = { 0 };
  static char *z = 0;
  static int alloced = 0;
  static int used = 0;
  int c;
  char zInt[40];
  if( zText==0 ){
    used = 0;
    return z;
  }
  if( n<=0 ){
    if( n<0 ){
      used += n;
      assert( used>=0 );
    }
    n = lemonStrlen(zText);
  }
  if( (int) (n+sizeof(zInt)*2+used) >= alloced ){
    alloced = n + sizeof(zInt)*2 + used + 200;
    z = (char *) realloc(z,  alloced);
  }
  if( z==0 ) return empty;
  while( n-- > 0 ){
    c = *(zText++);
    if( c=='%' && n>0 && zText[0]=='d' ){
      sprintf(zInt, "%d", p1);
      p1 = p2;
      strcpy(&z[used], zInt);
      used += lemonStrlen(&z[used]);
      zText++;
      n--;
    }else{
      z[used++] = c;
    }
  }
  z[used] = 0;
  return z;
}

PRIVATE void translate_code(struct lemon *lemp, struct rule *rp){
  char *cp, *xp;
  int i;
  char lhsused = 0;    
  char used[MAXRHS];   

  for(i=0; i<rp->nrhs; i++) used[i] = 0;
  lhsused = 0;

  if( rp->code==0 ){
    static char newlinestr[2] = { '\n', '\0' };
    rp->code = newlinestr;
    rp->line = rp->ruleline;
  }

  append_str(0,0,0,0);

  
  for(cp=(char *)rp->code; *cp; cp++){
    if( isalpha(*cp) && (cp==rp->code || (!isalnum(cp[-1]) && cp[-1]!='_')) ){
      char saved;
      for(xp= &cp[1]; isalnum(*xp) || *xp=='_'; xp++);
      saved = *xp;
      *xp = 0;
      if( rp->lhsalias && strcmp(cp,rp->lhsalias)==0 ){
        append_str("yygotominor.yy%d",0,rp->lhs->dtnum,0);
        cp = xp;
        lhsused = 1;
      }else{
        for(i=0; i<rp->nrhs; i++){
          if( rp->rhsalias[i] && strcmp(cp,rp->rhsalias[i])==0 ){
            if( cp!=rp->code && cp[-1]=='@' ){
              append_str("yymsp[%d].major",-1,i-rp->nrhs+1,0);
            }else{
              struct symbol *sp = rp->rhs[i];
              int dtnum;
              if( sp->type==MULTITERMINAL ){
                dtnum = sp->subsym[0]->dtnum;
              }else{
                dtnum = sp->dtnum;
              }
              append_str("yymsp[%d].minor.yy%d",0,i-rp->nrhs+1, dtnum);
            }
            cp = xp;
            used[i] = 1;
            break;
          }
        }
      }
      *xp = saved;
    }
    append_str(cp, 1, 0, 0);
  } 

  
  if( rp->lhsalias && !lhsused ){
    ErrorMsg(lemp->filename,rp->ruleline,
      "Label \"%s\" for \"%s(%s)\" is never used.",
        rp->lhsalias,rp->lhs->name,rp->lhsalias);
    lemp->errorcnt++;
  }

  for(i=0; i<rp->nrhs; i++){
    if( rp->rhsalias[i] && !used[i] ){
      ErrorMsg(lemp->filename,rp->ruleline,
        "Label %s for \"%s(%s)\" is never used.",
        rp->rhsalias[i],rp->rhs[i]->name,rp->rhsalias[i]);
      lemp->errorcnt++;
    }else if( rp->rhsalias[i]==0 ){
      if( has_destructor(rp->rhs[i],lemp) ){
        append_str("  yy_destructor(yypParser,%d,&yymsp[%d].minor);\n", 0,
           rp->rhs[i]->index,i-rp->nrhs+1);
      }else{
        
      }
    }
  }
  if( rp->code ){
    cp = append_str(0,0,0,0);
    rp->code = Strsafe(cp?cp:"");
  }
}

PRIVATE void emit_code(
  FILE *out,
  struct rule *rp,
  struct lemon *lemp,
  int *lineno
){
 const char *cp;

 
 if( rp->code ){
   if (!lemp->nolinenosflag) { (*lineno)++; tplt_linedir(out,rp->line,lemp->filename); }
   fprintf(out,"{%s",rp->code);
   for(cp=rp->code; *cp; cp++){
     if( *cp=='\n' ) (*lineno)++;
   } 
   fprintf(out,"}\n"); (*lineno)++;
   if (!lemp->nolinenosflag) { (*lineno)++; tplt_linedir(out,*lineno,lemp->outname); }
 } 

 return;
}

void print_stack_union(
  FILE *out,                  
  struct lemon *lemp,         
  int *plineno,               
  int mhflag                  
){
  int lineno = *plineno;    
  char **types;             
  int arraysize;            
  int maxdtlength;          
  char *stddt;              
  int i,j;                  
  int hash;                 
  const char *name;         

  
  arraysize = lemp->nsymbol * 2;
  types = (char**)calloc( arraysize, sizeof(char*) );
  for(i=0; i<arraysize; i++) types[i] = 0;
  maxdtlength = 0;
  if( lemp->vartype ){
    maxdtlength = lemonStrlen(lemp->vartype);
  }
  for(i=0; i<lemp->nsymbol; i++){
    int len;
    struct symbol *sp = lemp->symbols[i];
    if( sp->datatype==0 ) continue;
    len = lemonStrlen(sp->datatype);
    if( len>maxdtlength ) maxdtlength = len;
  }
  stddt = (char*)malloc( maxdtlength*2 + 1 );
  if( types==0 || stddt==0 ){
    fprintf(stderr,"Out of memory.\n");
    exit(1);
  }

  for(i=0; i<lemp->nsymbol; i++){
    struct symbol *sp = lemp->symbols[i];
    char *cp;
    if( sp==lemp->errsym ){
      sp->dtnum = arraysize+1;
      continue;
    }
    if( sp->type!=NONTERMINAL || (sp->datatype==0 && lemp->vartype==0) ){
      sp->dtnum = 0;
      continue;
    }
    cp = sp->datatype;
    if( cp==0 ) cp = lemp->vartype;
    j = 0;
    while( isspace(*cp) ) cp++;
    while( *cp ) stddt[j++] = *cp++;
    while( j>0 && isspace(stddt[j-1]) ) j--;
    stddt[j] = 0;
    if( lemp->tokentype && strcmp(stddt, lemp->tokentype)==0 ){
      sp->dtnum = 0;
      continue;
    }
    hash = 0;
    for(j=0; stddt[j]; j++){
      hash = hash*53 + stddt[j];
    }
    hash = (hash & 0x7fffffff)%arraysize;
    while( types[hash] ){
      if( strcmp(types[hash],stddt)==0 ){
        sp->dtnum = hash + 1;
        break;
      }
      hash++;
      if( hash>=arraysize ) hash = 0;
    }
    if( types[hash]==0 ){
      sp->dtnum = hash + 1;
      types[hash] = (char*)malloc( lemonStrlen(stddt)+1 );
      if( types[hash]==0 ){
        fprintf(stderr,"Out of memory.\n");
        exit(1);
      }
      strcpy(types[hash],stddt);
    }
  }

  
  name = lemp->name ? lemp->name : "Parse";
  lineno = *plineno;
  if( mhflag ){ fprintf(out,"#if INTERFACE\n"); lineno++; }
  fprintf(out,"#define %sTOKENTYPE %s\n",name,
    lemp->tokentype?lemp->tokentype:"void*");  lineno++;
  if( mhflag ){ fprintf(out,"#endif\n"); lineno++; }
  fprintf(out,"typedef union {\n"); lineno++;
  fprintf(out,"  int yyinit;\n"); lineno++;
  fprintf(out,"  %sTOKENTYPE yy0;\n",name); lineno++;
  for(i=0; i<arraysize; i++){
    if( types[i]==0 ) continue;
    fprintf(out,"  %s yy%d;\n",types[i],i+1); lineno++;
    free(types[i]);
  }
  if( lemp->errsym->useCnt ){
    fprintf(out,"  int yy%d;\n",lemp->errsym->dtnum); lineno++;
  }
  free(stddt);
  free(types);
  fprintf(out,"} YYMINORTYPE;\n"); lineno++;
  *plineno = lineno;
}

static const char *minimum_size_type(int lwr, int upr){
  if( lwr>=0 ){
    if( upr<=255 ){
      return "unsigned char";
    }else if( upr<65535 ){
      return "unsigned short int";
    }else{
      return "unsigned int";
    }
  }else if( lwr>=-127 && upr<=127 ){
    return "signed char";
  }else if( lwr>=-32767 && upr<32767 ){
    return "short";
  }else{
    return "int";
  }
}

struct axset {
  struct state *stp;   
  int isTkn;           
  int nAction;         
  int iOrder;          
};

static int axset_compare(const void *a, const void *b){
  struct axset *p1 = (struct axset*)a;
  struct axset *p2 = (struct axset*)b;
  int c;
  c = p2->nAction - p1->nAction;
  if( c==0 ){
    c = p2->iOrder - p1->iOrder;
  }
  assert( c!=0 || p1==p2 );
  return c;
}

static void writeRuleText(FILE *out, struct rule *rp){
  int j;
  fprintf(out,"%s ::=", rp->lhs->name);
  for(j=0; j<rp->nrhs; j++){
    struct symbol *sp = rp->rhs[j];
    fprintf(out," %s", sp->name);
    if( sp->type==MULTITERMINAL ){
      int k;
      for(k=1; k<sp->nsubsym; k++){
        fprintf(out,"|%s",sp->subsym[k]->name);
      }
    }
  }
}


void ReportTable(
  struct lemon *lemp,
  int mhflag     
){
  FILE *out, *in;
  char line[LINESIZE];
  int  lineno;
  struct state *stp;
  struct action *ap;
  struct rule *rp;
  struct acttab *pActtab;
  int i, j, n;
  const char *name;
  int mnTknOfst, mxTknOfst;
  int mnNtOfst, mxNtOfst;
  struct axset *ax;

  in = tplt_open(lemp);
  if( in==0 ) return;
  out = file_open(lemp,".c","wb");
  if( out==0 ){
    fclose(in);
    return;
  }
  lineno = 1;
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->include,&lineno);
  if( mhflag ){
    char *name = file_makename(lemp, ".h");
    fprintf(out,"#include \"%s\"\n", name); lineno++;
    free(name);
  }
  tplt_xfer(lemp->name,in,out,&lineno);

  
  if( mhflag ){
    const char *prefix;
    fprintf(out,"#if INTERFACE\n"); lineno++;
    if( lemp->tokenprefix ) prefix = lemp->tokenprefix;
    else                    prefix = "";
    for(i=1; i<lemp->nterminal; i++){
      fprintf(out,"#define %s%-30s %2d\n",prefix,lemp->symbols[i]->name,i);
      lineno++;
    }
    fprintf(out,"#endif\n"); lineno++;
  }
  tplt_xfer(lemp->name,in,out,&lineno);

  
  fprintf(out,"#define YYCODETYPE %s\n",
    minimum_size_type(0, lemp->nsymbol+1)); lineno++;
  fprintf(out,"#define YYNOCODE %d\n",lemp->nsymbol+1);  lineno++;
  fprintf(out,"#define YYACTIONTYPE %s\n",
    minimum_size_type(0, lemp->nstate+lemp->nrule+5));  lineno++;
  if( lemp->wildcard ){
    fprintf(out,"#define YYWILDCARD %d\n",
       lemp->wildcard->index); lineno++;
  }
  print_stack_union(out,lemp,&lineno,mhflag);
  fprintf(out, "#ifndef YYSTACKDEPTH\n"); lineno++;
  if( lemp->stacksize ){
    fprintf(out,"#define YYSTACKDEPTH %s\n",lemp->stacksize);  lineno++;
  }else{
    fprintf(out,"#define YYSTACKDEPTH 100\n");  lineno++;
  }
  fprintf(out, "#endif\n"); lineno++;
  if( mhflag ){
    fprintf(out,"#if INTERFACE\n"); lineno++;
  }
  name = lemp->name ? lemp->name : "Parse";
  if( lemp->arg && lemp->arg[0] ){
    int i;
    i = lemonStrlen(lemp->arg);
    while( i>=1 && isspace(lemp->arg[i-1]) ) i--;
    while( i>=1 && (isalnum(lemp->arg[i-1]) || lemp->arg[i-1]=='_') ) i--;
    fprintf(out,"#define %sARG_SDECL %s;\n",name,lemp->arg);  lineno++;
    fprintf(out,"#define %sARG_PDECL ,%s\n",name,lemp->arg);  lineno++;
    fprintf(out,"#define %sARG_FETCH %s = yypParser->%s\n",
                 name,lemp->arg,&lemp->arg[i]);  lineno++;
    fprintf(out,"#define %sARG_STORE yypParser->%s = %s\n",
                 name,&lemp->arg[i],&lemp->arg[i]);  lineno++;
  }else{
    fprintf(out,"#define %sARG_SDECL\n",name);  lineno++;
    fprintf(out,"#define %sARG_PDECL\n",name);  lineno++;
    fprintf(out,"#define %sARG_FETCH\n",name); lineno++;
    fprintf(out,"#define %sARG_STORE\n",name); lineno++;
  }
  if( mhflag ){
    fprintf(out,"#endif\n"); lineno++;
  }
  fprintf(out,"#define YYNSTATE %d\n",lemp->nstate);  lineno++;
  fprintf(out,"#define YYNRULE %d\n",lemp->nrule);  lineno++;
  if( lemp->errsym->useCnt ){
    fprintf(out,"#define YYERRORSYMBOL %d\n",lemp->errsym->index);  lineno++;
    fprintf(out,"#define YYERRSYMDT yy%d\n",lemp->errsym->dtnum);  lineno++;
  }
  if( lemp->has_fallback ){
    fprintf(out,"#define YYFALLBACK 1\n");  lineno++;
  }
  tplt_xfer(lemp->name,in,out,&lineno);


  
  ax = (struct axset *) calloc(lemp->nstate*2, sizeof(ax[0]));
  if( ax==0 ){
    fprintf(stderr,"malloc failed\n");
    exit(1);
  }
  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    ax[i*2].stp = stp;
    ax[i*2].isTkn = 1;
    ax[i*2].nAction = stp->nTknAct;
    ax[i*2+1].stp = stp;
    ax[i*2+1].isTkn = 0;
    ax[i*2+1].nAction = stp->nNtAct;
  }
  mxTknOfst = mnTknOfst = 0;
  mxNtOfst = mnNtOfst = 0;

  for(i=0; i<lemp->nstate*2; i++) ax[i].iOrder = i;
  qsort(ax, lemp->nstate*2, sizeof(ax[0]), axset_compare);
  pActtab = acttab_alloc();
  for(i=0; i<lemp->nstate*2 && ax[i].nAction>0; i++){
    stp = ax[i].stp;
    if( ax[i].isTkn ){
      for(ap=stp->ap; ap; ap=ap->next){
        int action;
        if( ap->sp->index>=lemp->nterminal ) continue;
        action = compute_action(lemp, ap);
        if( action<0 ) continue;
        acttab_action(pActtab, ap->sp->index, action);
      }
      stp->iTknOfst = acttab_insert(pActtab);
      if( stp->iTknOfst<mnTknOfst ) mnTknOfst = stp->iTknOfst;
      if( stp->iTknOfst>mxTknOfst ) mxTknOfst = stp->iTknOfst;
    }else{
      for(ap=stp->ap; ap; ap=ap->next){
        int action;
        if( ap->sp->index<lemp->nterminal ) continue;
        if( ap->sp->index==lemp->nsymbol ) continue;
        action = compute_action(lemp, ap);
        if( action<0 ) continue;
        acttab_action(pActtab, ap->sp->index, action);
      }
      stp->iNtOfst = acttab_insert(pActtab);
      if( stp->iNtOfst<mnNtOfst ) mnNtOfst = stp->iNtOfst;
      if( stp->iNtOfst>mxNtOfst ) mxNtOfst = stp->iNtOfst;
    }
  }
  free(ax);

  
  n = acttab_size(pActtab);
  fprintf(out,"#define YY_ACTTAB_COUNT (%d)\n", n); lineno++;
  fprintf(out,"static const YYACTIONTYPE yy_action[] = {\n"); lineno++;
  for(i=j=0; i<n; i++){
    int action = acttab_yyaction(pActtab, i);
    if( action<0 ) action = lemp->nstate + lemp->nrule + 2;
    if( j==0 ) fprintf(out," /* %5d */ ", i);
    fprintf(out, " %4d,", action);
    if( j==9 || i==n-1 ){
      fprintf(out, "\n"); lineno++;
      j = 0;
    }else{
      j++;
    }
  }
  fprintf(out, "};\n"); lineno++;

  
  fprintf(out,"static const YYCODETYPE yy_lookahead[] = {\n"); lineno++;
  for(i=j=0; i<n; i++){
    int la = acttab_yylookahead(pActtab, i);
    if( la<0 ) la = lemp->nsymbol;
    if( j==0 ) fprintf(out," /* %5d */ ", i);
    fprintf(out, " %4d,", la);
    if( j==9 || i==n-1 ){
      fprintf(out, "\n"); lineno++;
      j = 0;
    }else{
      j++;
    }
  }
  fprintf(out, "};\n"); lineno++;

  
  fprintf(out, "#define YY_SHIFT_USE_DFLT (%d)\n", mnTknOfst-1); lineno++;
  n = lemp->nstate;
  while( n>0 && lemp->sorted[n-1]->iTknOfst==NO_OFFSET ) n--;
  fprintf(out, "#define YY_SHIFT_COUNT (%d)\n", n-1); lineno++;
  fprintf(out, "#define YY_SHIFT_MIN   (%d)\n", mnTknOfst); lineno++;
  fprintf(out, "#define YY_SHIFT_MAX   (%d)\n", mxTknOfst); lineno++;
  fprintf(out, "static const %s yy_shift_ofst[] = {\n", 
          minimum_size_type(mnTknOfst-1, mxTknOfst)); lineno++;
  for(i=j=0; i<n; i++){
    int ofst;
    stp = lemp->sorted[i];
    ofst = stp->iTknOfst;
    if( ofst==NO_OFFSET ) ofst = mnTknOfst - 1;
    if( j==0 ) fprintf(out," /* %5d */ ", i);
    fprintf(out, " %4d,", ofst);
    if( j==9 || i==n-1 ){
      fprintf(out, "\n"); lineno++;
      j = 0;
    }else{
      j++;
    }
  }
  fprintf(out, "};\n"); lineno++;

  
  fprintf(out, "#define YY_REDUCE_USE_DFLT (%d)\n", mnNtOfst-1); lineno++;
  n = lemp->nstate;
  while( n>0 && lemp->sorted[n-1]->iNtOfst==NO_OFFSET ) n--;
  fprintf(out, "#define YY_REDUCE_COUNT (%d)\n", n-1); lineno++;
  fprintf(out, "#define YY_REDUCE_MIN   (%d)\n", mnNtOfst); lineno++;
  fprintf(out, "#define YY_REDUCE_MAX   (%d)\n", mxNtOfst); lineno++;
  fprintf(out, "static const %s yy_reduce_ofst[] = {\n", 
          minimum_size_type(mnNtOfst-1, mxNtOfst)); lineno++;
  for(i=j=0; i<n; i++){
    int ofst;
    stp = lemp->sorted[i];
    ofst = stp->iNtOfst;
    if( ofst==NO_OFFSET ) ofst = mnNtOfst - 1;
    if( j==0 ) fprintf(out," /* %5d */ ", i);
    fprintf(out, " %4d,", ofst);
    if( j==9 || i==n-1 ){
      fprintf(out, "\n"); lineno++;
      j = 0;
    }else{
      j++;
    }
  }
  fprintf(out, "};\n"); lineno++;

  
  fprintf(out, "static const YYACTIONTYPE yy_default[] = {\n"); lineno++;
  n = lemp->nstate;
  for(i=j=0; i<n; i++){
    stp = lemp->sorted[i];
    if( j==0 ) fprintf(out," /* %5d */ ", i);
    fprintf(out, " %4d,", stp->iDflt);
    if( j==9 || i==n-1 ){
      fprintf(out, "\n"); lineno++;
      j = 0;
    }else{
      j++;
    }
  }
  fprintf(out, "};\n"); lineno++;
  tplt_xfer(lemp->name,in,out,&lineno);

  if( lemp->has_fallback ){
    int mx = lemp->nterminal - 1;
    while( mx>0 && lemp->symbols[mx]->fallback==0 ){ mx--; }
    for(i=0; i<=mx; i++){
      struct symbol *p = lemp->symbols[i];
      if( p->fallback==0 ){
        fprintf(out, "    0,  /* %10s => nothing */\n", p->name);
      }else{
        fprintf(out, "  %3d,  /* %10s => %s */\n", p->fallback->index,
          p->name, p->fallback->name);
      }
      lineno++;
    }
  }
  tplt_xfer(lemp->name, in, out, &lineno);

  for(i=0; i<lemp->nsymbol; i++){
    sprintf(line,"\"%s\",",lemp->symbols[i]->name);
    fprintf(out,"  %-15s",line);
    if( (i&3)==3 ){ fprintf(out,"\n"); lineno++; }
  }
  if( (i&3)!=0 ){ fprintf(out,"\n"); lineno++; }
  tplt_xfer(lemp->name,in,out,&lineno);

  for(i=0, rp=lemp->rule; rp; rp=rp->next, i++){
    assert( rp->index==i );
    fprintf(out," /* %3d */ \"", i);
    writeRuleText(out, rp);
    fprintf(out,"\",\n"); lineno++;
  }
  tplt_xfer(lemp->name,in,out,&lineno);

  if( lemp->tokendest ){
    int once = 1;
    for(i=0; i<lemp->nsymbol; i++){
      struct symbol *sp = lemp->symbols[i];
      if( sp==0 || sp->type!=TERMINAL ) continue;
      if( once ){
        fprintf(out, "      /* TERMINAL Destructor */\n"); lineno++;
        once = 0;
      }
      fprintf(out,"    case %d: /* %s */\n", sp->index, sp->name); lineno++;
    }
    for(i=0; i<lemp->nsymbol && lemp->symbols[i]->type!=TERMINAL; i++);
    if( i<lemp->nsymbol ){
      emit_destructor_code(out,lemp->symbols[i],lemp,&lineno);
      fprintf(out,"      break;\n"); lineno++;
    }
  }
  if( lemp->vardest ){
    struct symbol *dflt_sp = 0;
    int once = 1;
    for(i=0; i<lemp->nsymbol; i++){
      struct symbol *sp = lemp->symbols[i];
      if( sp==0 || sp->type==TERMINAL ||
          sp->index<=0 || sp->destructor!=0 ) continue;
      if( once ){
        fprintf(out, "      /* Default NON-TERMINAL Destructor */\n"); lineno++;
        once = 0;
      }
      fprintf(out,"    case %d: /* %s */\n", sp->index, sp->name); lineno++;
      dflt_sp = sp;
    }
    if( dflt_sp!=0 ){
      emit_destructor_code(out,dflt_sp,lemp,&lineno);
    }
    fprintf(out,"      break;\n"); lineno++;
  }
  for(i=0; i<lemp->nsymbol; i++){
    struct symbol *sp = lemp->symbols[i];
    if( sp==0 || sp->type==TERMINAL || sp->destructor==0 ) continue;
    fprintf(out,"    case %d: /* %s */\n", sp->index, sp->name); lineno++;

    
    for(j=i+1; j<lemp->nsymbol; j++){
      struct symbol *sp2 = lemp->symbols[j];
      if( sp2 && sp2->type!=TERMINAL && sp2->destructor
          && sp2->dtnum==sp->dtnum
          && strcmp(sp->destructor,sp2->destructor)==0 ){
         fprintf(out,"    case %d: /* %s */\n",
                 sp2->index, sp2->name); lineno++;
         sp2->destructor = 0;
      }
    }

    emit_destructor_code(out,lemp->symbols[i],lemp,&lineno);
    fprintf(out,"      break;\n"); lineno++;
  }
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->overflow,&lineno);
  tplt_xfer(lemp->name,in,out,&lineno);

  for(rp=lemp->rule; rp; rp=rp->next){
    fprintf(out,"  { %d, %d },\n",rp->lhs->index,rp->nrhs); lineno++;
  }
  tplt_xfer(lemp->name,in,out,&lineno);

  
  for(rp=lemp->rule; rp; rp=rp->next){
    translate_code(lemp, rp);
  }
  
  for(rp=lemp->rule; rp; rp=rp->next){
    struct rule *rp2;               
    if( rp->code==0 ) continue;
    if( rp->code[0]=='\n' && rp->code[1]==0 ) continue; 
    fprintf(out,"      case %d: /* ", rp->index);
    writeRuleText(out, rp);
    fprintf(out, " */\n"); lineno++;
    for(rp2=rp->next; rp2; rp2=rp2->next){
      if( rp2->code==rp->code ){
        fprintf(out,"      case %d: /* ", rp2->index);
        writeRuleText(out, rp2);
        fprintf(out," */ yytestcase(yyruleno==%d);\n", rp2->index); lineno++;
        rp2->code = 0;
      }
    }
    emit_code(out,rp,lemp,&lineno);
    fprintf(out,"        break;\n"); lineno++;
    rp->code = 0;
  }
  fprintf(out,"      default:\n"); lineno++;
  for(rp=lemp->rule; rp; rp=rp->next){
    if( rp->code==0 ) continue;
    assert( rp->code[0]=='\n' && rp->code[1]==0 );
    fprintf(out,"      /* (%d) ", rp->index);
    writeRuleText(out, rp);
    fprintf(out, " */ yytestcase(yyruleno==%d);\n", rp->index); lineno++;
  }
  fprintf(out,"        break;\n"); lineno++;
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->failure,&lineno);
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->error,&lineno);
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->accept,&lineno);
  tplt_xfer(lemp->name,in,out,&lineno);

  
  tplt_print(out,lemp,lemp->extracode,&lineno);

  fclose(in);
  fclose(out);
  return;
}

void ReportHeader(struct lemon *lemp)
{
  FILE *out, *in;
  const char *prefix;
  char line[LINESIZE];
  char pattern[LINESIZE];
  int i;

  if( lemp->tokenprefix ) prefix = lemp->tokenprefix;
  else                    prefix = "";
  in = file_open(lemp,".h","rb");
  if( in ){
    for(i=1; i<lemp->nterminal && fgets(line,LINESIZE,in); i++){
      sprintf(pattern,"#define %s%-30s %2d\n",prefix,lemp->symbols[i]->name,i);
      if( strcmp(line,pattern) ) break;
    }
    fclose(in);
    if( i==lemp->nterminal ){
      
      return;
    }
  }
  out = file_open(lemp,".h","wb");
  if( out ){
    for(i=1; i<lemp->nterminal; i++){
      fprintf(out,"#define %s%-30s %2d\n",prefix,lemp->symbols[i]->name,i);
    }
    fclose(out);  
  }
  return;
}

void CompressTables(struct lemon *lemp)
{
  struct state *stp;
  struct action *ap, *ap2;
  struct rule *rp, *rp2, *rbest;
  int nbest, n;
  int i;
  int usesWildcard;

  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    nbest = 0;
    rbest = 0;
    usesWildcard = 0;

    for(ap=stp->ap; ap; ap=ap->next){
      if( ap->type==SHIFT && ap->sp==lemp->wildcard ){
        usesWildcard = 1;
      }
      if( ap->type!=REDUCE ) continue;
      rp = ap->x.rp;
      if( rp->lhsStart ) continue;
      if( rp==rbest ) continue;
      n = 1;
      for(ap2=ap->next; ap2; ap2=ap2->next){
        if( ap2->type!=REDUCE ) continue;
        rp2 = ap2->x.rp;
        if( rp2==rbest ) continue;
        if( rp2==rp ) n++;
      }
      if( n>nbest ){
        nbest = n;
        rbest = rp;
      }
    }
 
    if( nbest<1 || usesWildcard ) continue;


    
    for(ap=stp->ap; ap; ap=ap->next){
      if( ap->type==REDUCE && ap->x.rp==rbest ) break;
    }
    assert( ap );
    ap->sp = Symbol_new("{default}");
    for(ap=ap->next; ap; ap=ap->next){
      if( ap->type==REDUCE && ap->x.rp==rbest ) ap->type = NOT_USED;
    }
    stp->ap = Action_sort(stp->ap);
  }
}


static int stateResortCompare(const void *a, const void *b){
  const struct state *pA = *(const struct state**)a;
  const struct state *pB = *(const struct state**)b;
  int n;

  n = pB->nNtAct - pA->nNtAct;
  if( n==0 ){
    n = pB->nTknAct - pA->nTknAct;
    if( n==0 ){
      n = pB->statenum - pA->statenum;
    }
  }
  assert( n!=0 );
  return n;
}


void ResortStates(struct lemon *lemp)
{
  int i;
  struct state *stp;
  struct action *ap;

  for(i=0; i<lemp->nstate; i++){
    stp = lemp->sorted[i];
    stp->nTknAct = stp->nNtAct = 0;
    stp->iDflt = lemp->nstate + lemp->nrule;
    stp->iTknOfst = NO_OFFSET;
    stp->iNtOfst = NO_OFFSET;
    for(ap=stp->ap; ap; ap=ap->next){
      if( compute_action(lemp,ap)>=0 ){
        if( ap->sp->index<lemp->nterminal ){
          stp->nTknAct++;
        }else if( ap->sp->index<lemp->nsymbol ){
          stp->nNtAct++;
        }else{
          stp->iDflt = compute_action(lemp, ap);
        }
      }
    }
  }
  qsort(&lemp->sorted[1], lemp->nstate-1, sizeof(lemp->sorted[0]),
        stateResortCompare);
  for(i=0; i<lemp->nstate; i++){
    lemp->sorted[i]->statenum = i;
  }
}



static int size = 0;

void SetSize(int n)
{
  size = n+1;
}

char *SetNew(){
  char *s;
  s = (char*)calloc( size, 1);
  if( s==0 ){
    extern void memory_error();
    memory_error();
  }
  return s;
}

void SetFree(char *s)
{
  free(s);
}

int SetAdd(char *s, int e)
{
  int rv;
  assert( e>=0 && e<size );
  rv = s[e];
  s[e] = 1;
  return !rv;
}

int SetUnion(char *s1, char *s2)
{
  int i, progress;
  progress = 0;
  for(i=0; i<size; i++){
    if( s2[i]==0 ) continue;
    if( s1[i]==0 ){
      progress = 1;
      s1[i] = 1;
    }
  }
  return progress;
}

PRIVATE int strhash(const char *x)
{
  int h = 0;
  while( *x) h = h*13 + *(x++);
  return h;
}

const char *Strsafe(const char *y)
{
  const char *z;
  char *cpy;

  if( y==0 ) return 0;
  z = Strsafe_find(y);
  if( z==0 && (cpy=(char *)malloc( lemonStrlen(y)+1 ))!=0 ){
    strcpy(cpy,y);
    z = cpy;
    Strsafe_insert(z);
  }
  MemoryCheck(z);
  return z;
}

struct s_x1 {
  int size;               
                          
                          
  int count;              
  struct s_x1node *tbl;  
  struct s_x1node **ht;  
};

typedef struct s_x1node {
  const char *data;        
  struct s_x1node *next;   
  struct s_x1node **from;  
} x1node;

static struct s_x1 *x1a;

void Strsafe_init(){
  if( x1a ) return;
  x1a = (struct s_x1*)malloc( sizeof(struct s_x1) );
  if( x1a ){
    x1a->size = 1024;
    x1a->count = 0;
    x1a->tbl = (x1node*)malloc( 
      (sizeof(x1node) + sizeof(x1node*))*1024 );
    if( x1a->tbl==0 ){
      free(x1a);
      x1a = 0;
    }else{
      int i;
      x1a->ht = (x1node**)&(x1a->tbl[1024]);
      for(i=0; i<1024; i++) x1a->ht[i] = 0;
    }
  }
}
/* Insert a new record into the array.  Return TRUE if successful.
** Prior data with the same key is NOT overwritten */
int Strsafe_insert(const char *data)
{
  x1node *np;
  int h;
  int ph;

  if( x1a==0 ) return 0;
  ph = strhash(data);
  h = ph & (x1a->size-1);
  np = x1a->ht[h];
  while( np ){
    if( strcmp(np->data,data)==0 ){
      
      
      return 0;
    }
    np = np->next;
  }
  if( x1a->count>=x1a->size ){
    
    int i,size;
    struct s_x1 array;
    array.size = size = x1a->size*2;
    array.count = x1a->count;
    array.tbl = (x1node*)malloc(
      (sizeof(x1node) + sizeof(x1node*))*size );
    if( array.tbl==0 ) return 0;  
    array.ht = (x1node**)&(array.tbl[size]);
    for(i=0; i<size; i++) array.ht[i] = 0;
    for(i=0; i<x1a->count; i++){
      x1node *oldnp, *newnp;
      oldnp = &(x1a->tbl[i]);
      h = strhash(oldnp->data) & (size-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x1a->tbl);
    *x1a = array;
  }
  
  h = ph & (x1a->size-1);
  np = &(x1a->tbl[x1a->count++]);
  np->data = data;
  if( x1a->ht[h] ) x1a->ht[h]->from = &(np->next);
  np->next = x1a->ht[h];
  x1a->ht[h] = np;
  np->from = &(x1a->ht[h]);
  return 1;
}

const char *Strsafe_find(const char *key)
{
  int h;
  x1node *np;

  if( x1a==0 ) return 0;
  h = strhash(key) & (x1a->size-1);
  np = x1a->ht[h];
  while( np ){
    if( strcmp(np->data,key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}

struct symbol *Symbol_new(const char *x)
{
  struct symbol *sp;

  sp = Symbol_find(x);
  if( sp==0 ){
    sp = (struct symbol *)calloc(1, sizeof(struct symbol) );
    MemoryCheck(sp);
    sp->name = Strsafe(x);
    sp->type = isupper(*x) ? TERMINAL : NONTERMINAL;
    sp->rule = 0;
    sp->fallback = 0;
    sp->prec = -1;
    sp->assoc = UNK;
    sp->firstset = 0;
    sp->lambda = LEMON_FALSE;
    sp->destructor = 0;
    sp->destLineno = 0;
    sp->datatype = 0;
    sp->useCnt = 0;
    Symbol_insert(sp,sp->name);
  }
  sp->useCnt++;
  return sp;
}

int Symbolcmpp(const void *_a, const void *_b)
{
  const struct symbol **a = (const struct symbol **) _a;
  const struct symbol **b = (const struct symbol **) _b;
  int i1 = (**a).index + 10000000*((**a).name[0]>'Z');
  int i2 = (**b).index + 10000000*((**b).name[0]>'Z');
  assert( i1!=i2 || strcmp((**a).name,(**b).name)==0 );
  return i1-i2;
}

struct s_x2 {
  int size;               
                          
                          
  int count;              
  struct s_x2node *tbl;  
  struct s_x2node **ht;  
};

typedef struct s_x2node {
  struct symbol *data;     
  const char *key;         
  struct s_x2node *next;   
  struct s_x2node **from;  
} x2node;

static struct s_x2 *x2a;

void Symbol_init(){
  if( x2a ) return;
  x2a = (struct s_x2*)malloc( sizeof(struct s_x2) );
  if( x2a ){
    x2a->size = 128;
    x2a->count = 0;
    x2a->tbl = (x2node*)malloc( 
      (sizeof(x2node) + sizeof(x2node*))*128 );
    if( x2a->tbl==0 ){
      free(x2a);
      x2a = 0;
    }else{
      int i;
      x2a->ht = (x2node**)&(x2a->tbl[128]);
      for(i=0; i<128; i++) x2a->ht[i] = 0;
    }
  }
}
/* Insert a new record into the array.  Return TRUE if successful.
** Prior data with the same key is NOT overwritten */
int Symbol_insert(struct symbol *data, const char *key)
{
  x2node *np;
  int h;
  int ph;

  if( x2a==0 ) return 0;
  ph = strhash(key);
  h = ph & (x2a->size-1);
  np = x2a->ht[h];
  while( np ){
    if( strcmp(np->key,key)==0 ){
      
      
      return 0;
    }
    np = np->next;
  }
  if( x2a->count>=x2a->size ){
    
    int i,size;
    struct s_x2 array;
    array.size = size = x2a->size*2;
    array.count = x2a->count;
    array.tbl = (x2node*)malloc(
      (sizeof(x2node) + sizeof(x2node*))*size );
    if( array.tbl==0 ) return 0;  
    array.ht = (x2node**)&(array.tbl[size]);
    for(i=0; i<size; i++) array.ht[i] = 0;
    for(i=0; i<x2a->count; i++){
      x2node *oldnp, *newnp;
      oldnp = &(x2a->tbl[i]);
      h = strhash(oldnp->key) & (size-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->key = oldnp->key;
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x2a->tbl);
    *x2a = array;
  }
  
  h = ph & (x2a->size-1);
  np = &(x2a->tbl[x2a->count++]);
  np->key = key;
  np->data = data;
  if( x2a->ht[h] ) x2a->ht[h]->from = &(np->next);
  np->next = x2a->ht[h];
  x2a->ht[h] = np;
  np->from = &(x2a->ht[h]);
  return 1;
}

struct symbol *Symbol_find(const char *key)
{
  int h;
  x2node *np;

  if( x2a==0 ) return 0;
  h = strhash(key) & (x2a->size-1);
  np = x2a->ht[h];
  while( np ){
    if( strcmp(np->key,key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}

struct symbol *Symbol_Nth(int n)
{
  struct symbol *data;
  if( x2a && n>0 && n<=x2a->count ){
    data = x2a->tbl[n-1].data;
  }else{
    data = 0;
  }
  return data;
}

int Symbol_count()
{
  return x2a ? x2a->count : 0;
}

struct symbol **Symbol_arrayof()
{
  struct symbol **array;
  int i,size;
  if( x2a==0 ) return 0;
  size = x2a->count;
  array = (struct symbol **)calloc(size, sizeof(struct symbol *));
  if( array ){
    for(i=0; i<size; i++) array[i] = x2a->tbl[i].data;
  }
  return array;
}

int Configcmp(const char *_a,const char *_b)
{
  const struct config *a = (struct config *) _a;
  const struct config *b = (struct config *) _b;
  int x;
  x = a->rp->index - b->rp->index;
  if( x==0 ) x = a->dot - b->dot;
  return x;
}

PRIVATE int statecmp(struct config *a, struct config *b)
{
  int rc;
  for(rc=0; rc==0 && a && b;  a=a->bp, b=b->bp){
    rc = a->rp->index - b->rp->index;
    if( rc==0 ) rc = a->dot - b->dot;
  }
  if( rc==0 ){
    if( a ) rc = 1;
    if( b ) rc = -1;
  }
  return rc;
}

PRIVATE int statehash(struct config *a)
{
  int h=0;
  while( a ){
    h = h*571 + a->rp->index*37 + a->dot;
    a = a->bp;
  }
  return h;
}

struct state *State_new()
{
  struct state *newstate;
  newstate = (struct state *)calloc(1, sizeof(struct state) );
  MemoryCheck(newstate);
  return newstate;
}

struct s_x3 {
  int size;               
                          
                          
  int count;              
  struct s_x3node *tbl;  
  struct s_x3node **ht;  
};

typedef struct s_x3node {
  struct state *data;                  
  struct config *key;                   
  struct s_x3node *next;   
  struct s_x3node **from;  
} x3node;

static struct s_x3 *x3a;

void State_init(){
  if( x3a ) return;
  x3a = (struct s_x3*)malloc( sizeof(struct s_x3) );
  if( x3a ){
    x3a->size = 128;
    x3a->count = 0;
    x3a->tbl = (x3node*)malloc( 
      (sizeof(x3node) + sizeof(x3node*))*128 );
    if( x3a->tbl==0 ){
      free(x3a);
      x3a = 0;
    }else{
      int i;
      x3a->ht = (x3node**)&(x3a->tbl[128]);
      for(i=0; i<128; i++) x3a->ht[i] = 0;
    }
  }
}
/* Insert a new record into the array.  Return TRUE if successful.
** Prior data with the same key is NOT overwritten */
int State_insert(struct state *data, struct config *key)
{
  x3node *np;
  int h;
  int ph;

  if( x3a==0 ) return 0;
  ph = statehash(key);
  h = ph & (x3a->size-1);
  np = x3a->ht[h];
  while( np ){
    if( statecmp(np->key,key)==0 ){
      
      
      return 0;
    }
    np = np->next;
  }
  if( x3a->count>=x3a->size ){
    
    int i,size;
    struct s_x3 array;
    array.size = size = x3a->size*2;
    array.count = x3a->count;
    array.tbl = (x3node*)malloc(
      (sizeof(x3node) + sizeof(x3node*))*size );
    if( array.tbl==0 ) return 0;  
    array.ht = (x3node**)&(array.tbl[size]);
    for(i=0; i<size; i++) array.ht[i] = 0;
    for(i=0; i<x3a->count; i++){
      x3node *oldnp, *newnp;
      oldnp = &(x3a->tbl[i]);
      h = statehash(oldnp->key) & (size-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->key = oldnp->key;
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x3a->tbl);
    *x3a = array;
  }
  
  h = ph & (x3a->size-1);
  np = &(x3a->tbl[x3a->count++]);
  np->key = key;
  np->data = data;
  if( x3a->ht[h] ) x3a->ht[h]->from = &(np->next);
  np->next = x3a->ht[h];
  x3a->ht[h] = np;
  np->from = &(x3a->ht[h]);
  return 1;
}

struct state *State_find(struct config *key)
{
  int h;
  x3node *np;

  if( x3a==0 ) return 0;
  h = statehash(key) & (x3a->size-1);
  np = x3a->ht[h];
  while( np ){
    if( statecmp(np->key,key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}

struct state **State_arrayof()
{
  struct state **array;
  int i,size;
  if( x3a==0 ) return 0;
  size = x3a->count;
  array = (struct state **)malloc( sizeof(struct state *)*size );
  if( array ){
    for(i=0; i<size; i++) array[i] = x3a->tbl[i].data;
  }
  return array;
}

PRIVATE int confighash(struct config *a)
{
  int h=0;
  h = h*571 + a->rp->index*37 + a->dot;
  return h;
}

struct s_x4 {
  int size;               
                          
                          
  int count;              
  struct s_x4node *tbl;  
  struct s_x4node **ht;  
};

typedef struct s_x4node {
  struct config *data;                  
  struct s_x4node *next;   
  struct s_x4node **from;  
} x4node;

static struct s_x4 *x4a;

void Configtable_init(){
  if( x4a ) return;
  x4a = (struct s_x4*)malloc( sizeof(struct s_x4) );
  if( x4a ){
    x4a->size = 64;
    x4a->count = 0;
    x4a->tbl = (x4node*)malloc( 
      (sizeof(x4node) + sizeof(x4node*))*64 );
    if( x4a->tbl==0 ){
      free(x4a);
      x4a = 0;
    }else{
      int i;
      x4a->ht = (x4node**)&(x4a->tbl[64]);
      for(i=0; i<64; i++) x4a->ht[i] = 0;
    }
  }
}
/* Insert a new record into the array.  Return TRUE if successful.
** Prior data with the same key is NOT overwritten */
int Configtable_insert(struct config *data)
{
  x4node *np;
  int h;
  int ph;

  if( x4a==0 ) return 0;
  ph = confighash(data);
  h = ph & (x4a->size-1);
  np = x4a->ht[h];
  while( np ){
    if( Configcmp((const char *) np->data,(const char *) data)==0 ){
      
      
      return 0;
    }
    np = np->next;
  }
  if( x4a->count>=x4a->size ){
    
    int i,size;
    struct s_x4 array;
    array.size = size = x4a->size*2;
    array.count = x4a->count;
    array.tbl = (x4node*)malloc(
      (sizeof(x4node) + sizeof(x4node*))*size );
    if( array.tbl==0 ) return 0;  
    array.ht = (x4node**)&(array.tbl[size]);
    for(i=0; i<size; i++) array.ht[i] = 0;
    for(i=0; i<x4a->count; i++){
      x4node *oldnp, *newnp;
      oldnp = &(x4a->tbl[i]);
      h = confighash(oldnp->data) & (size-1);
      newnp = &(array.tbl[i]);
      if( array.ht[h] ) array.ht[h]->from = &(newnp->next);
      newnp->next = array.ht[h];
      newnp->data = oldnp->data;
      newnp->from = &(array.ht[h]);
      array.ht[h] = newnp;
    }
    free(x4a->tbl);
    *x4a = array;
  }
  
  h = ph & (x4a->size-1);
  np = &(x4a->tbl[x4a->count++]);
  np->data = data;
  if( x4a->ht[h] ) x4a->ht[h]->from = &(np->next);
  np->next = x4a->ht[h];
  x4a->ht[h] = np;
  np->from = &(x4a->ht[h]);
  return 1;
}

struct config *Configtable_find(struct config *key)
{
  int h;
  x4node *np;

  if( x4a==0 ) return 0;
  h = confighash(key) & (x4a->size-1);
  np = x4a->ht[h];
  while( np ){
    if( Configcmp((const char *) np->data,(const char *) key)==0 ) break;
    np = np->next;
  }
  return np ? np->data : 0;
}

void Configtable_clear(int(*f)(struct config *))
{
  int i;
  if( x4a==0 || x4a->count==0 ) return;
  if( f ) for(i=0; i<x4a->count; i++) (*f)(x4a->tbl[i].data);
  for(i=0; i<x4a->size; i++) x4a->ht[i] = 0;
  x4a->count = 0;
  return;
}
