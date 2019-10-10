#include "big-bits.h"
#include "hex-util.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  char * bits;
  int hexValue;
  
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
  int mask = sizeof(hex)*4;
  const BigBits * newBit = malloc(sizeof(struct BigBits)+1);
  
  char * s = malloc(strlen(hex)+1);
  int curHex = charToHexet(s);
  while()
  if(newBit==NULL || s==NULL){
    newBit->next=NULL;
    fprintf(stderr, "malloc failure: %s\n", strerror(errno));
    exit(1);
  }
  newBit->hexValue=charToHexet(s);
  newBit->bits = s;

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
  const BigBits * newBit = malloc(sizeof(struct BigBits)+1);
  char * s = malloc(strlen(newBit->bits)+1);
  int d = 0 ;
  int val = charToHexet(s);
    for( d = 0; (val & (1<<d)) == 0 && d < 15; )
    {
        d++ ;
    }   

    // Significant digits
    for( int i = 0 ; d < 16; s++; d++ )
    {
        s[i] =hexetToChar(val);
    }    

    return s;

}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  if(bigBits1!=NULL && bigBits2!=NULL ){
  const BigBits * p ;
  int hexV1 = chartoHexet(BigBits1->bits) & chartoHexet(BigBits1->bits);
  char * s1 = hexetToChar(hexV1);
  p = newBigBits(s1);

  }
  return NULL;
}

/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  if(bigBits1!=NULL && bigBits2!=NULL ){
    return bigBits1 | bigBits2;
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
  if(bigBits1!=NULL && bigBits2!=NULL ){
    return bigBits1 ^ bigBits2;
  }
  return NULL;
}
