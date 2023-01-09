/* Second task: Print "Hello World loop in C */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

   int choice;

   while(1) {
      printf("1.Print 100 times\n");
      printf("2.Select number of times to print\n");
      printf("3.Exit");
      printf("\n\nEnter Your choice : ");
      fflush(stdin);
      scanf("%d",&choice);
      int i=1;
      int n;
      clock_t t_inicio, t_final;
      double segundos;

      switch(choice)
        {
            case 1:
               t_inicio = clock();
               while(i <=100){
                  printf("%d Hello World\n", i);
                  i++;
               };
               t_final = clock();
               segundos = (double) (t_final-t_inicio) /CLOCKS_PER_SEC;
               printf("\n Spent time: %f s. to print %d times \n\n",segundos, (i-1));
               break;
            case 2:
               t_inicio = clock();
               printf("\nEnter number of times:");
               scanf("%d",&n);
               while(i <=n){
                  printf("%d Hello World\n", i);
                  i++;
               };
               t_final = clock();
               segundos = (double) (t_final-t_inicio) /CLOCKS_PER_SEC;
               printf("\n Spent time: %f s. to print %d times \n\n",segundos, (i-1));
               break;
            case 3:
                exit(1);
            default:
                printf("Invalid Input!!!\n");
        }
    }
   return 0;
}

