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
  
  int index;        
  int size;         
  FnInfo **fnInfo;     
};


FnsData* fntrace(void *addr, FnsData *fnsData){

	int f_index = fnsData->index;
  fnsData = add_instr(addr,fnsData);
  fnsData->fnInfo[f_index]->nInCalls = 1;
  unsigned char* address = addr;
  unsigned int funcLength = 0;
  unsigned int nOut = 0;
  while(!is_ret(*address)){
    int next_len = get_op_length(address);
    funcLength += next_len;
    if(is_call(*address)){
      nOut++;
      int* offset = (int*)(address + 1);
      void* next = *offset + address + next_len;
      int present = isPresent(next,fnsData);
      if(present == -1){
        fnsData = fntrace(next, fnsData);
      }else{
        fnsData->fnInfo[present]->nInCalls+= 1;
      }
    }
    address += next_len;
    addr+=next_len;
  }
  fnsData->fnInfo[f_index]->nOutCalls = nOut;
  fnsData->fnInfo[f_index]->length = funcLength + 1;
  return fnsData;
}


FnsData * add_instr(void *rootFn, FnsData * data){
	if(data->index >= data->size){
    int size = (data->size > 0) ? data->size*2 : 1;
    data->fnInfo = reallocChk(data->fnInfo, size * sizeof(FnInfo));
    data->size = size;
  }
  data->fnInfo[data->index] = (FnInfo*)malloc(sizeof(FnInfo));
  data->fnInfo[data->index]->address = rootFn;
  data->fnInfo[data->index]->length = 0;
  data->fnInfo[data->index]->nInCalls = 0;
  data->fnInfo[data->index]->nOutCalls = 0;
  data->index++;
  return data;
}

int isPresent(void *address, FnsData *fnsData){
          for (int i = 0; i < fnsData->index; i++) {
            if (fnsData->fnInfo[i]->address == address) {
                return i;
            }
        }
        return -1;
}

int cmpAdd(const void* addr1, const void * addr2){
  FnInfo **infoA = (FnInfo **) addr1;
  int * a = (*infoA)->address;
  FnInfo **infoB = (FnInfo **) addr2;
  int* b = (*infoB)->address;
  return a-b;

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
  Fns = fntrace(rootFn,Fns);
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
  for(int i=0;i<fnsData->size;i++){
   free(fnsData->fnInfo[i]);
   }
    free(fnsData->fnInfo);
    free(fnsData);

  
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
  if (lastFnInfo == NULL) return fnsData->fnInfo[0];
  int i;
  for (i = 0; fnsData->fnInfo[i] != lastFnInfo; i++);
  return fnsData->fnInfo[i+1];
}
