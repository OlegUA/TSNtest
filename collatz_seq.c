#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>

inline __attribute__((always_inline)) int collatz(int start);

int main(int ac, char *av[]) {
	int start = 0;
	char *p = NULL;
	struct timespec s, e;
	int cycles = 1;
	unsigned long long avg = 0LL, tmp;

	if(ac <= 1) {
		fprintf(stderr, "Use: %s <Collatz start number> [cycles count], where \"number\" is starting of the Collatz sequence and should be integer > 1\n", av[0]);
		fprintf(stderr, " The \"optional parameter\" cycles count is used for more accuracy timing calculation.");
		return(-1);
	}

	for(p = av[1]; *p; ++p) {
		if(!isdigit((int)*p) && *p != '+') {
			fprintf(stderr, "Wrong input parameter, only positive integer values are allowed.\n");
			return(-2);
		}
	}
	start = atoi(av[1]);
	if(start <= 1) {
		fprintf(stderr, "The starting number should be >= 1\n");
		return(-3);
	}

	if(ac > 2) {
		cycles = atoi(av[2]);
		printf("Cycles = %d\n", cycles);
	}

	int max_stopped_time = 0;

	printf("Start value=%d, collatz stop time for this value=%d, cycles=%d\n", start, collatz(start), cycles);

	for(int i = 0; i < cycles; i++) {
		int save_start = start;
		clock_gettime(CLOCK_REALTIME, &s);

		while(start) {
			int stop_t = collatz(start--);
			if(stop_t > max_stopped_time) max_stopped_time = stop_t;
		}

		clock_gettime(CLOCK_REALTIME, &e);
		tmp = (unsigned long long)(e.tv_sec - s.tv_sec) * 1000000LL + (unsigned long long)(e.tv_nsec - s.tv_nsec);
		avg = (tmp + i * avg) / (i + 1);
		start = save_start;
	}

	printf("\nMax stopped time=%d\nAverage elapsed time = %lld ns\n", max_stopped_time, avg);

	return(0);
}

inline int collatz(int start) {
	int stop_t = 0;
	while(start > 1) {
		if((start & 1) != 0) {
			start = start * 3 + 1;
		} else {
			start >>= 1;
		}
		//printf("%d ", start);
		++stop_t;
	}
	return stop_t;
}
