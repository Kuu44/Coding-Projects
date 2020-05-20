/********
 *
 * Sujit Maharjan
 *
 * lab2
 *  Write a program to find the position of the character 'C' in the sentence "idea without execution is worthless" using pointer and string.
 *
 ********/

#include <stdio.h>
// header file for input and output

int main()
{
  // declaring string 
  char* line = "idea without execution is worthless";
  // pointer that points to a char of the string
  char* c;
  // initialization
  c = line;
  while( *c != '\0') // loop util the end of the string
    {
      if( *c == 'c') // cheking if c is in the present position 
	{
	  printf("Found %c in position %d\n", *c , (int)(c-line)); // displays the position
	}
      c++; // move to the next char in the string.
    }
  return 0;
}
