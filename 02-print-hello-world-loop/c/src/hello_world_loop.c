/***********************************************************************
 *       Second task: Print "Hello World loop in C
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
   int count_loop;
   clock_t t_inicio, t_final;
   double segundos;
   if(argc < 2) {
      count_loop=100;
   } else {
      count_loop = atoi(argv[1]);
   }
   t_inicio = clock();
   for(int i=0; i <= count_loop; i++) {
      printf("%d Hello World\n", i);
   };
   t_final = clock();
   segundos = (double) (t_final-t_inicio) /CLOCKS_PER_SEC; // Time to do
   printf("\n Spent time: %f s. to print %d times \n\n",segundos, (count_loop));  //Print spent time
   return 0;
}
