#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

//gcc -Wall -Werror -O2 -std=gnu90 MatrixMult.c
//valgrind --leak-check=yes -q --vgdb=no ./a.out < input.txt > output.txt

int * * * input;
int * * * results;
int * * dimensions;
int count = 0;
int row0 = 0;
int AAA = 0;
#ifdef _REENTRANT
	int read_wall = -1;
	int write_wall = -1;
	pthread_mutex_t lockread, lockwrite;
	pthread_cond_t signalMult, signalPrint;
#endif

/**
 * while (read_wall < i) {
 * 	this is bad idea?
 * }
 * Hint:
 * How many locks? Mutexes?
 * what are the critical sections?
 * we will work on making it actually good next assigment.
 **/

void * read_matrices() {
	int r;
	int c;
	int i; 
	int j, tmp;
	//printf("Read time bois \n");
	AAA = scanf("%d %d", &r, &c);
	int * * arr;
	dimensions[0] = malloc(sizeof(int) * 101);
	dimensions[1] = malloc(sizeof(int) * 101);
	
	//garuntee intialized
	dimensions[1][0] = 0;
	dimensions[0][1] = 0;
	
	count = -1;
	row0 = r;
	while (r != 0 && c != 0) { 
		
		count++;
		dimensions[0][count] = r;
		dimensions[1][count] = c;
		arr = malloc(sizeof(int *) * r);
		for (i = 0; i < r; ++i) {
			arr[i] = malloc(sizeof(int) * c);
			for (j = 0; j < c; ++j) {
				AAA = scanf("%d", &tmp);
				arr[i][j] = tmp;

			}
		}
		#ifdef _REENTRANT
			pthread_mutex_lock(&lockread);
		#endif
		input[count] = arr;
		#ifdef _REENTRANT
			read_wall += 1;
			//printf("read wall is now %d \n", read_wall);
			pthread_cond_signal(&signalMult);
			pthread_mutex_unlock(&lockread);
		#endif

		AAA = scanf("%d %d", &r, &c);
	}
	#ifdef _REENTRANT
		pthread_mutex_lock(&lockread);
		read_wall += 1;
		//printf("read wall is now %d \n", read_wall);
		pthread_cond_signal(&signalMult);
		pthread_mutex_unlock(&lockread);
	#endif
	return NULL;
}

void * mult_matrices() { 
	//sleep(1);
	//printf("I do Start CLAC \n");
    int i;
	int j;
	int k; 
	int z = 0;
	int * * arr;
	#ifdef _REENTRANT
		pthread_mutex_lock(&lockread);
		while(read_wall<0){
			pthread_cond_wait(&signalMult, &lockread);
		}
		pthread_mutex_unlock(&lockread);
	#endif
	results[0] = malloc(sizeof(int *) * row0);
	//printf("I start pre loop \n");
	#ifdef _REENTRANT
		pthread_mutex_lock(&lockwrite);
	#endif
	for (i = 0; i < row0; i++) {
		results[0][i] = malloc(sizeof(int) * dimensions[1][0]);
		for (j = 0; j < dimensions[1][0]; j++) {
			results[0][i][j] = input[0][i][j];
		}
	}
	#ifdef _REENTRANT
		pthread_mutex_unlock(&lockwrite);
	#endif

	for (z = 1; z <= count; z++) {
		#ifdef _REENTRANT
			pthread_mutex_lock(&lockread);
			while(read_wall<z) {
				pthread_cond_wait(&signalMult, &lockread);
			}
			pthread_mutex_unlock(&lockread);
		#endif
		arr = malloc(sizeof(int *) * dimensions[0][z]);
		//printf("I on count %d \n", z);
		for (i = 0; i < row0; i++) { 
			//printf("I on row %d \n", i);
			arr[i] = malloc(sizeof(int) * dimensions[1][z]);
			for (j = 0; j < dimensions[1][z]; j++) {
				//printf("I on init time %d \n", z); 
				//printf("%d %d \n", i, j);
				arr[i][j] = 0; 
				//printf("I on math TIME %d \n", j);
				for (k = 0; k < dimensions[0][z]; k++) {
					arr[i][j] += results[z-1][i][k]*input[z][k][j];
				}
				//printf("I on sort TIME %d \n", j);
				int l = j;
				int temp;
                while(l > 0 && arr[i][l] < arr[i][l-1]) {
                    temp = arr[i][l-1];
                    arr[i][l-1] = arr[i][l];
                    arr[i][l] = temp;
                    l--;
                }
			} 
		} 
		#ifdef _REENTRANT
			pthread_mutex_lock(&lockwrite);
		#endif
		results[z] = arr;
		#ifdef _REENTRANT
			write_wall += 1;
			//printf("write wall is now %d \n", write_wall);
			pthread_cond_signal(&signalPrint);
			pthread_mutex_unlock(&lockwrite);
		#endif
	}
	#ifdef _REENTRANT
		pthread_mutex_lock(&lockwrite);
		write_wall += 1;
		//printf("write wall is now %d \n", write_wall);
		pthread_cond_signal(&signalPrint);
		pthread_mutex_unlock(&lockwrite);
	#endif
	//printf("I done calc \n");
	return NULL;
}

void * show_matrices() {
	int i, j, k, tmp;


	#ifdef _REENTRANT
		pthread_mutex_lock(&lockwrite);
		while (write_wall < 2){
			pthread_cond_wait(&signalPrint, &lockwrite);
		}
		pthread_mutex_unlock(&lockwrite);
	#endif

	//Free
	for(i=0; i < row0; i++) {
        free(input[0][i]);
        free(results[0][i]);
    }
    free(input[0]);
    free(results[0]);
    for(k=1; k <= count; k++) {
		#ifdef _REENTRANT
			pthread_mutex_lock(&lockwrite);
			while(write_wall<k){
				pthread_cond_wait(&signalPrint, &lockwrite);
			}
			pthread_mutex_unlock(&lockwrite);
        #endif
		tmp = dimensions[1][k];
        printf("%d %d\n", row0, tmp);

        for(i=0; i < row0; i++) {
			tmp = results[k][i][0];
            printf("%d", tmp);
            for(j = 1; j < dimensions[1][k]; j++) {
				tmp = results[k][i][j];
                printf(" %d",tmp);
            }
            printf("\n");
            free(results[k][i]);
        }
        for(i=0; i < dimensions[0][k]; i++) {
            free(input[k][i]);
        }
        free(input[k]);
        free(results[k]);
    }
    printf("0 0\n");
    free(input);
    free(results);
	for(i = 0; i < 2; i++) {
        free(dimensions[i]);
    }
    free(dimensions);
	return NULL;
}

int main() {
	#ifdef _REENTRANT
		pthread_t readThred;
		pthread_t multThred;
		pthread_t showThred;
		pthread_mutex_init(&lockwrite, NULL);
    	pthread_mutex_init(&lockread, NULL);	
	#endif
	u_int64_t diff;
	u_int64_t read;
	u_int64_t mult;
	u_int64_t show;
	struct timespec start;
	struct timespec startr, endr;
	struct timespec startm, endm;
	struct timespec starts, ends;
	//printf("I do Start \n");
    // initialize any global variables
	input = malloc(sizeof(int * *) * 100);
	results = malloc(sizeof(int * *) * 100);
	dimensions = malloc(sizeof(int *) * 2);

	clock_gettime(CLOCK_REALTIME, &start);
	
	//run
	#ifdef _REENTRANT
		clock_gettime(CLOCK_REALTIME, &startr);
    	pthread_create(&readThred,NULL,read_matrices,NULL);
    #else
		clock_gettime(CLOCK_REALTIME, &startr);
    	read_matrices();
		clock_gettime(CLOCK_REALTIME, &endr);
		read = 1000000000 * (endr.tv_sec - startr.tv_sec) + endr.tv_nsec - startr.tv_nsec;
	#endif

	#ifdef _REENTRANT
		clock_gettime(CLOCK_REALTIME, &startm);
		pthread_create(&multThred,NULL,mult_matrices,NULL);
	#else
		clock_gettime(CLOCK_REALTIME, &startm);
		mult_matrices();
		clock_gettime(CLOCK_REALTIME, &endm);
		mult = 1000000000 * (endm.tv_sec - startm.tv_sec) + endm.tv_nsec - startm.tv_nsec;
	#endif

	#ifdef _REENTRANT
		clock_gettime(CLOCK_REALTIME, &starts);
		pthread_create(&showThred,NULL,show_matrices,NULL);
	#else
		clock_gettime(CLOCK_REALTIME, &starts);
		show_matrices();
		clock_gettime(CLOCK_REALTIME, &ends);
		show = 1000000000 * (ends.tv_sec - starts.tv_sec) + ends.tv_nsec - starts.tv_nsec;
	#endif

	#ifdef _REENTRANT
        pthread_join(readThred, NULL);
        clock_gettime(CLOCK_REALTIME, &endr);
        read = 1000000000 * (endr.tv_sec - startr.tv_sec) + endr.tv_nsec - startr.tv_nsec;
    #endif

    #ifdef _REENTRANT
        pthread_join(multThred, NULL);
        clock_gettime(CLOCK_REALTIME, &endm);
        mult = 1000000000 * (endm.tv_sec - startm.tv_sec) + endm.tv_nsec - startm.tv_nsec;
    #endif

    #ifdef _REENTRANT
        pthread_join(showThred, NULL);
        clock_gettime(CLOCK_REALTIME, &ends);
        show = 1000000000 * (ends.tv_sec - starts.tv_sec) + ends.tv_nsec - starts.tv_nsec;
    #endif
	
	diff = 1000000000 * (ends.tv_sec - start.tv_sec) + ends.tv_nsec - start.tv_nsec;
	printf("Reading: %luns\n", read);
	printf("Computing: %luns\n", mult);
	printf("Writing: %luns\n", show);
	printf("Elapsed: %luns\n", diff);

    // report time
	return 0;
}