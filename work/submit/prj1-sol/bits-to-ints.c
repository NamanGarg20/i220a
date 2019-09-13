#include "bits-to-ints.h"
#include "errors.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

//@TODO: auxiliary definitions

/** This function should be called with inFile set to an input FILE
 *  stream corresponding to a file named inName.  This FILE should
 *  contain a stream of '0' or '1' bit-value characters optionally
 *  separated by whitespace (as determined by isspace()) characters.
 *  The function should return the next unsigned integer value given
 *  by the next next nBits bit characters read from in.
 *
 *  The nBits argument (which should be > 0) will specify the number
 *  of bits from FILE stream inFile which are to be grouped to form an
 *  unsigned integer value.
 *
 *  The bytes within the bit-stream are assumed to be in big-endian
 *  order (with the most significant byte first), and the bits within
 *  each byte are ordered little-endian with the least-significant bit
 *  first.
 *
 *  For example, assume that nBits is 16 and the least significant bit
 *  in the result is at index 0, and most significant bit in the
 *  result at index 15; i.e., the bits in the BitsValue result are
 *  indexed 15-14-...-1-0.  The order of the corresponding bits in the
 *  input stream will be 8-9-10-11-12-13-14-15 - 0-1-2-3-4-5-6-7.  So
 *  the bit-stream "1101 0101 1011 0011" will result in the BitsValue
 *  0xabcd (which has binary representation 1010_1011_1100_1101).
 *
 *  When the function returns, *isEof should be set to true if
 *  end-of-file is encountered on inFile.  If EOF is encountered
 *  within a partial value, then a suitable error message should be
 *  printed before returning with *isEof true.
 *
 *  If any character other than '0', '1' or whitespace is encountered
 *  in inFile, then a suitable error message should be printed and the
 *  function should return with *isEof set to true.
 */
BitsValue
bits_to_ints(FILE *inFile, const char *inName, int nBits, bool *isEof)
{
  //nBits value should make sense
  assert(0 < nBits && nBits <= CHAR_BIT*sizeof(BitsValue));
  BitsValue value = 0;
  //@TODO
  int count=0;  
  int bits[nBits];
  *isEof = false;
    

    while(count<nBits && *isEof==false){ 
      char c = fgetc(inFile);
    if(c!=EOF){
    	*isEof = false;
    if(c!='0' && c!='1' && !isspace(c)){
      error("entered data %c should be binary ",&c);
      
    }
  }
  else{
    *isEof=true;
  }
    
    if (!isspace(c)){  
        int x = c -'0';
        bits[count] = x;
        count++;
     }    
  
<<<<<<< HEAD
 }    long long ex=1;
 		for(int j=0; j<nBits/4;j++){
            
            for(int i=j*4;i<j*4+4;i++){
      
        value += ex * bits[i];
  
        ex<<=1;
        
            }
}	if(nBits==16){// conversion from little endian to big endian
	value = ((value & 0xFFU) << 8 | (value & 0xFF00U) >> 8); // got the method for this from site www.csharp-examples.net/reverse-bytes/
}
if(nBits==32){
	value=(value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
         (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}
if(nBits==64){
	value = (value & 0x00000000000000FFUL) << 56 | (value & 0x000000000000FF00UL) << 40 |
         (value & 0x0000000000FF0000UL) << 24 | (value & 0x00000000FF000000UL) << 8 |
         (value & 0x000000FF00000000UL) >> 8 | (value & 0x0000FF0000000000UL) >> 24 |
         (value & 0x00FF000000000000UL) >> 40 | (value & 0xFF00000000000000UL) >> 56;
}

=======
 }            
      int ex=1;
	BitsValue byte[nBits/4];
	BitsValue r=0;
	for(int j=0; j<nBits/4;j++){
            for(int i=j*4;i<j*4+4;i++){
      
        r += ex * bits[i];
	
        ex<<=1;
        
            }
	byte[j]=r;
}
	for(int k=0;k<nBits/4;k++){
	if(k%3!=0){
		value=byte[k];
	}
	value = byte[k];
}
>>>>>>> b56c1be017ecb6e6ccfb5e4ac3d5f68c5c0cfde0
      
    return value;
  
}

