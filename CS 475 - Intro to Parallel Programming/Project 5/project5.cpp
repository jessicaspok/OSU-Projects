/**********************************************
 * Jessica Spokoyny
 * CS 475 - Project 5
 * May 22, 2017
 *********************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "simd.p5.h"

#define NUMTRIES 		200

using namespace std;

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

float Ranf(unsigned int *seedp, float low, float high);
void FillArray(float *arry, int size);

void CppMulSum(float *A, float *B, float *C, int len);
float CppMulSum(float *A, float *B, int len);

int main(int argc, char *argv[]) {
	
	#ifndef _OPENMP
		fprintf( stderr, "OpenMP is not supported here -- sorry.\n");
		return 1;
	#endif
	
	// open data files
	FILE *datafile = fopen(argv[1], "a");

	FillArray(A, ARRAYSIZE);
	FillArray(B, ARRAYSIZE);

	float cppSumTime = 0;
	float cppAvgTime = 0;
	float cppPeakTime = 100;
	float simdSumTime = 0;
	float simdAvgTime = 0;
	float simdPeakTime = 100;

	double time0;
	double time1;

	// SIMD vs C++ multiplication
	if (TEST == 0) {
		// C++ multiplication
		for(int i = 0; i < NUMTRIES; i++) {
			time0 = omp_get_wtime();
            CppMulSum(A, B, C, ARRAYSIZE);
			time1 = omp_get_wtime();
			
			cppSumTime += time1 - time0;
			if (time1 - time0 < cppPeakTime)
				cppPeakTime = time1 - time0; 
		}
		
		cppAvgTime = cppSumTime / NUMTRIES;

		// SIMD multiplication
		for(int i = 0; i < NUMTRIES; i++) {
			time0 = omp_get_wtime();
			SimdMul(A, B, C, ARRAYSIZE);
			time1 = omp_get_wtime();
			
			simdSumTime += time1 - time0;
			if (time1 - time0 < simdPeakTime)
				simdPeakTime = time1 - time0; 
		}
		
		simdAvgTime = simdSumTime / NUMTRIES;
	} 
	
	// SIMD vs C++ multiplication-reduction
	else {
		// C++ multiplication + reduction
		for(int i = 0; i < NUMTRIES; i++) {
			time0 = omp_get_wtime();
            float sum = CppMulSum(A, B, ARRAYSIZE);
			time1 = omp_get_wtime();
			
			cppSumTime += time1 - time0;
			if (time1 - time0 < cppPeakTime)
				cppPeakTime = time1 - time0; 

		}
		
		cppAvgTime = cppSumTime / NUMTRIES;

		// SIMD multiplication-reduction
		for(int i = 0; i < NUMTRIES; i++) {
			time0 = omp_get_wtime();
			float sum = SimdMulSum(A, B, ARRAYSIZE);
			time1 = omp_get_wtime();
			
			simdSumTime += time1 - time0;
			if (time1 - time0 < simdPeakTime)
				simdPeakTime = time1 - time0; 

		}
		
		simdAvgTime = simdSumTime / NUMTRIES;
	}

	fprintf(datafile, "%d, %.8f, %.8f, %.8f, %.8f, %.8f\n", ARRAYSIZE, cppPeakTime, cppAvgTime, simdPeakTime, simdAvgTime, cppPeakTime / simdPeakTime);

	fclose(datafile);		

	return 0;	
}

void CppMulSum(float *A, float *B, float *C, int len) {
    for (int i = 0; i < len; i++) {
		C[i] = A[i]*B[i];
	}
}

float CppMulSum(float *A, float *B, int len) {
    float sum = 0;
	
	for (int i = 0; i < len; i++) {
		sum += A[i]*B[i];
	}
    return sum;
}

void FillArray(float *array, int size) {
	unsigned int seed = 0;

	for(int i = 0; i < size; i++) {
		array[i] = Ranf(&seed, -1., 1.);
	}
}

float Ranf(unsigned int *seedp, float low, float high) {
	float r = (float) rand_r(seedp);
	return(low + r * (high - low) / (float)RAND_MAX);
}