#include <stdio.h>

void f(void);

int x = 2234, y = 2324;

int 
main() 
{
  f();
  printf("x = 0x%x, y = 0x%x\n", x, y);
  return 0;
}
