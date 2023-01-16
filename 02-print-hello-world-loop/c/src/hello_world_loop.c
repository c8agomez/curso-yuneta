/***********************************************************************
*       Second task: Print "Hello World loop in C
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* Devuelve "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}


int main(int argc, char *argv[])
{
	struct timeval t_ini, t_fin;
	double seconds;

	gettimeofday(&t_ini, NULL);

	int count_loop;

	if(argc < 2) {
		count_loop=100;
	} else {
		count_loop = atoi(argv[1]);
	}

	for(int i=0; i <= count_loop; i++) {
		printf("%d Hello World\n", i);
	};

	gettimeofday(&t_fin, NULL);

	seconds = timeval_diff(&t_fin, &t_ini);
	printf("\n Spent time: %f s. to print %d times \n\n",seconds, (count_loop));

	return 0;
}
