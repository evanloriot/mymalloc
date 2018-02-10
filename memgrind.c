#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

#define TEST_SIZE 150
#define FULL_TEST_SIZE 100
#define MEMORY_SIZE 4968

//Receives current time for use in determining runtime
double getTime() {
	struct timeval start;
	int time_received;
	time_received = gettimeofday(&start, NULL);
	if(time_received == 0) {
		double start_time =  (double) start.tv_sec +  (double) (start.tv_usec * .000001);	
		return start_time;
	}
	else {
		printf("Failed to receive time\n");
		exit(0);
	}
}

//malloc() 1 byte and immediately free it 150 times
void A() {
	printf("\n\nInitiating test function A\n");
	char *byte;
	int count;
	for(count = 0; count < TEST_SIZE; count++) {
		byte = (char*) malloc(sizeof(char));
		free(byte);
	}	
}

//malloc() 1 byte, store the pointer in an array 150 times, then free entire array
void B() {
	printf("\n\nInitiating test function B\n");
	void *array[TEST_SIZE]; 
	int count;
	for(count = 0; count < TEST_SIZE; count++) {
		array[count] = (void*) malloc(sizeof(char));
	}
	for(count = 0; count < TEST_SIZE; count++) {
		free(array[count]);
	}
}

//Randomly choose between a 1 byte malloc() or free()ing a byte pointer, done 150 times
void C() {
	printf("\n\nInitiating test function C\n");
	void *array[TEST_SIZE];
	int random;	
	int malCount = 0;
	while(malCount < TEST_SIZE) {
		random = rand() % 2;
		if(random == 1) {
			array[malCount] = malloc(sizeof(char));
			malCount++;
		} else {
			free(array[(rand() % TEST_SIZE + 1) - 1]);
		}
	}
	for(malCount--; malCount > 0; malCount--)
		free(array[malCount]);
}

//Randomly choose between a randomly-sized malloc() or free()ing a pointer, done 150 times
void D(){ 
	printf("\n\nInitiaing test function D\n");
	void *array[TEST_SIZE];
	int random, size;
	int malCount = 0;
	while(malCount < TEST_SIZE) {
		random = rand() % 2;
		if(random == 1) {
			size = rand() % 65;
			array[malCount] = malloc(sizeof(size));
			malCount++;
		} else {
			free(array[(rand() % TEST_SIZE + 1) - 1]);
		}
	}
	for(malCount--; malCount > 0; malCount--)
		free(array[malCount]);
}

//Fills up memory, then repeatedly attempts to malloc() a pointer with a size of 1
void E() {
	printf("\n\nInitiaing test function E\n");
	int count;
	void *ptr1, *ptr2;
	ptr1 = malloc(sizeof(MEMORY_SIZE));
	for(count = 0; count < TEST_SIZE; count++) {
		ptr2 = malloc(sizeof(1));
	}
	free(ptr1);
	free(ptr2);
}

//Fills up memory, frees every other block, then attempts to malloc() a size between each free block size and the total available space
void F() {
	printf("\n\nInitialing test function F\n");
	int count;
	void *array[TEST_SIZE];
	void *ptr;
	for(count = 0; count < TEST_SIZE; count++) {	
		array[count] = malloc(sizeof(MEMORY_SIZE / TEST_SIZE));
	}
	for(count = 0; count < TEST_SIZE; count+=2) {
		free(array[count]);
	}
	for(count--; count > 0; count--) {
		ptr = malloc(sizeof(MEMORY_SIZE / TEST_SIZE) * 2);
	}
	free(ptr);
	for(count = 0; count < TEST_SIZE; count++) {	
		free(array[count]);
	}
}

//Runs every function 100 times, records the runtime for each workload, then prints out the average workload time
int main(int argc, char** argv){ 
	double start_time, end_time, run_time, total_time, mean_time;
	total_time = 0;
	int count;
	for(count = 0; count < FULL_TEST_SIZE; count++) {
		start_time = getTime();
		A();
		B();
		C();
		D();
		E();
		F();
		end_time = getTime();
		run_time = (double) end_time - (double) start_time;
		total_time += run_time;
	}
	mean_time = (double) total_time / (double) FULL_TEST_SIZE;
	printf("Average time per workload: %lf seconds\n", mean_time);
	return 0;
}
