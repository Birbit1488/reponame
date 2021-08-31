#include <stdio.h>

 void
swap (int *a, int *b)
{
  
int temp = *a;
  
*a = *b;
  
*b = temp;

} 
 
int

main ()
{
  
int a, b;
  
printf ("Provide the a value: ");
  
scanf ("%d", &a);
  
printf ("Provide the b value: ");
  
scanf ("%d", &b);
  
 
swap (&a, &b);
  
printf ("The Swapped values of a and b: a = %d, b = %d\n", a, b);
  
return 0;

}
