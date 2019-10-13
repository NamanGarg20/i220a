#include "big-bits.h"
#include "hex-util.h"
#include "errors.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  char * bits;


  
};

/** Return a pointer to a representation of a big integer with value
 *  corresponding to the non-empty hexadecimal string hex.  Note that
 *  hex will only contain hexadecimal characters '0' - '9', 'a' - 'f'
 *  and 'A' - 'F' terminated by a NUL '\0' char.
 *
 *  The string hex may not remain valid after this function returns.
 *
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
newBigBits(const char *hex)
{
  assert(CHAR_BIT == 8);
  //@TODO
  int count=0;
  BigBits * newBit = malloc(sizeof(struct BigBits));
  char * s = (char *)malloc(strlen(hex)+1);
  if(newBit==NULL || s==NULL){
  	error(strerror(errno));
  }
  	strcpy(s,(char *)hex);
	newBit->bits= s;

  return newBit;
}

/** Frees all resources used by currently valid bigBits.  bigBits
 *  is not valid after this function returns.
 */
void
freeBigBits(BigBits *bigBits)
{
  //@TODO
    free(bigBits->bits);
    free(bigBits); 
  }



/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  there is no call to free the corresponding string).
 */
const char *
stringBigBits(const BigBits *bigBits)
{
  //@TODO
  if(bigBits!=NULL){
  int outBits = 0;// prececiding zero bits
  char *newBit;
  
  if(strlen(bigBits->bits)>1){
  for(int i = 0;i< strlen(bigBits->bits); i++){
        if(bigBits->bits[i]=='0'){
        outBits++;
    }
  }
  	newBit = (char*)malloc(strlen(bigBits->bits)+1-outBits);
  for(int i = 0; i<strlen(bigBits->bits)-outBits; i++){
  newBit[i] = tolower(bigBits->bits[i+outBits]);
  }
  newBit[strlen(bigBits->bits)-outBits]='\0';

}else {
	newBit =(char*) malloc(strlen(bigBits->bits));
	for(int i = 0; i<strlen(bigBits->bits); i++){
  newBit[i] = tolower(bigBits->bits[i]);
  }
	
}
for(int i=0;i<strlen(newBit);i++){
  	if(charToHexet(newBit[i])>16 || charToHexet(newBit[i])<0){
  		newBit[i]='\0';
  	}
  }
  	
  return newBit;
}
else{
	return NULL;
}
}
  	


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
	if(bigBits1!=NULL && bigBits2 !=NULL){
 	char * newBits;
  int size1 = strlen(bigBits1->bits);
  int size2 = strlen(bigBits2->bits); 		
  	int i=0;
  	int newAndBit=0;;
   if(size1 <= size2){
    newBits = malloc(size1);
    for(int i=0;i<size1;i++){
 		newAndBit = charToHexet((bigBits1->bits[size1-i-1])) & charToHexet((bigBits2->bits[size2-i-1]));
 		if(newAndBit>=0){
 			newBits[size1 -i -1] =(hexetToChar(newAndBit));  
 			}  
    }
  } else {
    newBits = malloc(size2);
    for(int i=0;i<size2;i++){
    	
 		newAndBit = charToHexet((bigBits1->bits[size1-i-1])) & charToHexet((bigBits2->bits[size2 -i-1]));
     
 			if(newAndBit>=0){
 			newBits[size2 -i -1] =(hexetToChar(newAndBit));
 		}
 	}
    }

  return  newBigBits(newBits);
  
}else{
	return NULL;
}
}
/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
	if(bigBits1!=NULL && bigBits2 !=NULL){
  char * newBits;
  int size1 = strlen(bigBits1->bits);
  int size2 = strlen(bigBits2->bits);

  int max = (size1>=size2)?size1:size2;
 		
  	int i=0;
  	int newAndBit=0;;
   if(size1 <= size2){
    newBits = malloc(max);
    for(int i=0;i<max;i++){
 		newAndBit = charToHexet(bigBits1->bits[size1-i-1]) | charToHexet(bigBits2->bits[size2-i-1]);
 		if(size1<i){
 			newAndBit = charToHexet(bigBits2->bits[size2-i-1]);
 		}
 		if(newAndBit>=0){
 			newBits[max -i -1] =(hexetToChar(newAndBit));
 		}
      
      
    }
  } else {
    newBits = malloc(max);
    for(int i=0;i<max;i++){
    	
 		newAndBit = charToHexet(bigBits1->bits[size1-i-1]) | charToHexet(bigBits2->bits[size2 -i-1]);
 		if((size2-i-1)<0){
 			newAndBit = charToHexet(bigBits1->bits[size1-i-1]);
 		}
 		if(newAndBit>=0){
 			newBits[max -i -1] =(hexetToChar(newAndBit));
 		}
    }
    }
  

  return  newBigBits(newBits);
  
}
return NULL;
}


/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
	if(bigBits1!=NULL && bigBits2 !=NULL){
  char * newBits;
  int size1 = strlen(bigBits1->bits);
  int size2 = strlen(bigBits2->bits);

 		
  	int max = (size1>=size2)?size1:size2;
 		
  	int i=0;
  	int newAndBit=0;;
   if(size1 <= size2){
    newBits = malloc(max);
    for(int i=0;i<max;i++){
 		newAndBit = charToHexet(bigBits1->bits[size1-i-1]) ^ charToHexet(bigBits2->bits[size2-i-1]);
 		if(size1<i){
 			newAndBit = charToHexet(bigBits2->bits[size2-i-1]);
 		}
 		if(newAndBit>=0){
 			newBits[max -i -1] =(hexetToChar(newAndBit));
 		}
      
      
    }
  } else {
    newBits = malloc(max);
    for(int i=0;i<max;i++){
    	
 		newAndBit = charToHexet(bigBits1->bits[size1-i-1]) ^ charToHexet(bigBits2->bits[size2 -i-1]);
 		if((size2-i-1)<0){
 			newAndBit = charToHexet(bigBits1->bits[size1-i-1]);
 		}
 		if(newAndBit>=0){
 			newBits[max -i -1] =(hexetToChar(newAndBit));
 		}
    }
    }
  

  return  newBigBits(newBits);
  
}
return NULL;
}