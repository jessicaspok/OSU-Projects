/**********************************************
 * Jessica Spokoyny
 * CS 475 - Project 2
 * April 30, 2017
 *********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

#define NUMT 			1
#define CHUNKSIZE 		1
#define ARRAYSIZE 		32768
#define NUMTRIES 		100

float Array[ARRAYSIZE];

float Ranf(float, float);

int main() {
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
	
	omp_set_num_threads( NUMT );
	
	double maxMegaMults = 0.;
    double sumMegaMults = 0.;
	
	for( int t = 0; t < NUMTRIES; t++ ) {
		
		double time0 = omp_get_wtime( );

		for (int k = 0; k < ARRAYSIZE; k++) {
			Array[k] = Ranf( -1.f, 1.f );
		}
		
		#pragma omp parallel for schedule(static,1)
		for (int i = 0; i < ARRAYSIZE; i++) {
			float prod = 1;
			
			for (int j = 0; j < i; j++) {
				prod *= Array[j];
			}
		}
		
		double time1 = omp_get_wtime( );
		long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done
        double megaMults = (double)numMuled/(time1-time0)/1000000.;
        sumMegaMults += megaMults;
        if( megaMults > maxMegaMults )
            maxMegaMults = megaMults;
	}
	
	fprintf( stderr, "\n            Threads = %d \n          ChunkSize = %d \n         Scheduling = static \n\n", NUMT, CHUNKSIZE);
	
	double avgMegaMults = sumMegaMults/(double)NUMTRIES;
    printf( "   Peak Performance = %10.2lf MegaMults/Sec\n", maxMegaMults );
    printf( "Average Performance = %10.2lf MegaMults/Sec\n\n", avgMegaMults );

	return 0;
}

float Ranf(float low, float high) {
	float r = (float) rand();		// 0 - RAND_MAX

	return(low + r * (high - low) / (float)RAND_MAX);
}