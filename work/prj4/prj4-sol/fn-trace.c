#include "fn-trace.h"
#include "x86-64_lde.h"

#include "memalloc.h"
#include <errno.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

struct FnsData {
  
  size_t index;        /** index of next free element */
  size_t size;         /** max number of elements for current elements[] */
  FnInfo **fnInfo;      /** storage for elements */
};


const FnsData* fntrace(void *addr, FnsData *fnsData){
	 unsigned char * address = (unsigned char*)addr;
	 int fn_index = fnsData->index;
  FnsData * data = (FnsData*)add_instr(addr, fnsData);
  
  unsigned int f_length = 0;
  unsigned int nOut = 0;
  while(!is_ret(*address)){
    int instrLength = get_op_length(address);
    unsigned char opCode = *address;
    f_length += instrLength;
    if(is_call(opCode)){
      nOut++;
      int* offset = (void*)address + 1;
      void* rootfn = *offset + address + instrLength;
      
  if(isPresent(address,data)==-1){  
	     fntrace(rootfn, data);
      }else{
	data->fnInfo[isPresent(address,data)]->nInCalls+= 1;
      }
    }
    address += instrLength;
  }
  data->fnInfo[fn_index]->nOutCalls = nOut;
  data->fnInfo[fn_index]->length = f_length + 1;
  return data;

}

FnsData * add_instr(void *rootFn, FnsData * data){
	if(data->index >= data->size){
    const size_t size = (data->size > 0) ? data->size*2 : 1;
    data->fnInfo = reallocChk(data->fnInfo, size * sizeof(FnInfo));
    data->size = size;
  }
  data->fnInfo[data->index] = (FnInfo*)malloc(sizeof(FnInfo));
  data->fnInfo[data->index]->address = rootFn;
  data->fnInfo[data->index]->length = 0;
  data->fnInfo[data->index]->nInCalls = 1;
  data->fnInfo[data->index]->nOutCalls = 0;
  data->index+= 1;
  return data;
}

int isPresent(void *addr, FnsData *fnsData){
  for(int i=0; i<fnsData->size;i++){
    
    if(fnsData->fnInfo[i]->address==addr){
      return i;
    }
  }
  return -1;
}

int cmpAdd(const void* addr1, const void * addr2){
  FnInfo fn1 = *(FnInfo *)addr1;
  FnInfo fn2 = *(FnInfo *)addr2;
  void * l = fn1.address;
  void * r = fn2.address;
    return (l - r);

}
/** Return pointer to opaque data structure containing collection of
 *  FnInfo's for functions which are callable directly or indirectly
 *  from the function whose address is rootFn.
 */
const FnsData *
new_fns_data(void *rootFn)
{
  //verify assumption used when decoding call address
  assert(sizeof(int) == 4);
  //@TODO
  
  FnsData *Fns = mallocChk( sizeof(FnsData));
  if (is_ret(get_op_length(rootFn))) {
    printf( "cannot alloc FnsData: %d\n",get_op_length(rootFn) );
    exit(1);
  }
  Fns->fnInfo=NULL;
  Fns->size=0;
  Fns->index=0;
  Fns = (FnsData*)fntrace(rootFn,Fns);
  qsort(Fns->fnInfo, Fns->index, sizeof(FnInfo*), cmpAdd);

  return Fns;
}

/** Free all resources occupied by fnsData. fnsData must have been
 *  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
  for(int i=0;i<fnsData->index;i++){
     free(fnsData->fnInfo[i]);
   }
    free(fnsData->fnInfo);
    free(fnsData);
    fnsData=NULL;
   fnsData->size=0;
  fnsData->index=0;
  
  
}

/** Iterate over all FnInfo's in fnsData.  Make initial call with NULL
 *  lastFnInfo.  Keep calling with return value as lastFnInfo, until
 *  next_fn_info() returns NULL.  Values must be returned sorted in
 *  increasing order by fnInfoP->address.
 *
 *  Sample iteration:
 *
 *  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 *       fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 *    //body of iteration
 *  }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
  //@TODO
  if(fnsData->size==0){
    return NULL;
  }

  if(lastFnInfo==NULL){
    return fnsData->fnInfo[0];
  }
  for (int i=0;i<fnsData.size;i++) {
    if(lastFnInfo->address==fnsData->fnInfo[i]->address){
      return fnsData->fnInfo[i];
    }
    i++;
  }
  return lastFnInfo;
}
