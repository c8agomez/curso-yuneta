/***********************************************************************
*       Second task: Print "Hello World loop in C
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float time_diff2(struct timespec *start, struct timespec *end){
	return (end->tv_sec - start->tv_sec) + 1e-9*(end->tv_nsec - start->tv_nsec);
}

int main(int argc, char *argv[])
{
	struct timespec t_ini;
    struct timespec t_fin;
	double seconds;

	clock_gettime(CLOCK_REALTIME, &t_ini);

	int count_loop;

	if(argc < 2) {
		count_loop=100;
	} else {
		count_loop = atoi(argv[1]);
	}

	for(int i=0; i <= count_loop; i++) {
		printf("%d Hello World\n", i);
	};

	clock_gettime(CLOCK_REALTIME, &t_fin);

	seconds=time_diff2(&t_ini, &t_fin)

	printf("\n Spent time: %0.8f s. to print %d times \n\n",seconds, (count_loop));

	return 0;
}
