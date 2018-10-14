/* program for counting newlines , tab, blanks*/

#include<stdio.h>


int main(void) 
{
    int blanks, tabs, newline;
    int c;
    blanks = tabs = newline = 0;

   while ( (c = getchar()) != EOF)
   {
       if (c == '\n')       // if new line comes increment 
           newline++;

       else if ( c == '\t')  //if tab 
           tabs++;
       
       else if (c == ' ')    // if blank space
           blanks++;
//       else
  //         printf ("enter correct option \n");
   }
  printf ("no of new lines is %d\n", newline); 
  printf ("no of tabs is %d\n", tabs); 
  printf ("no of blanks is %d\n",blanks);
}
