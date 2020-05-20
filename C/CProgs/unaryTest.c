#include <stdio.h>

void main()
{
  int a=1,b=2;
  int c=a+++(++b);
  printf("%d\n",c);
  a=1,b=2;c=a+(++b);
  printf("%d\n",c);
  a=1,b=2;c=(a++)+b;
  printf("%d\n",c);
}