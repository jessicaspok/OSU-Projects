/**********************************************
 * Jessica Spokoyny
 * CS 475 - Project 3
 * May 8, 2017
 *********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUMTRIES 		100

struct s {
	float value;
	int pad[NUMPAD];
} Array[4];


int main() {
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
	
	omp_set_num_threads(NUMT);
	
	double maxMegaAdds = 0.;
    double sumMegaAdds = 0.;

	const int SomeBigNumber = 100000000;	// keep < 2B

	for(int t = 0; t < NUMTRIES; t++) {
		
		double time0 = omp_get_wtime( );
		
 		if (FIX == 1) {
			#pragma omp parallel for
			for(int i = 0; i < 4; i++) {
				unsigned int seed = 0;		// automatically private
				for(unsigned int j = 0; j < SomeBigNumber; j++) {
					Array[i].value = Array[i].value + (float)rand_r(&seed);
				}
			}
		}
		
		else { 
			#pragma omp parallel for
			for(int i = 0; i < 4; i++) {
				unsigned int seed = 0;		// automatically private
				float temp = Array[i].value;
				for(unsigned int j = 0; j < SomeBigNumber; j++ ) {
					temp = temp + (float)rand_r(&seed);
				}
				Array[i].value = temp;
			}
			
		}
		
		double time1 = omp_get_wtime( );
		
        double megaAdds = (double)(4*SomeBigNumber)/(time1-time0)/1000000.;
        
		sumMegaAdds += megaAdds;
        
		if(megaAdds > maxMegaAdds)
            maxMegaAdds = megaAdds;
	}
	
	fprintf( stderr, "\n            Threads = %d \n            Padding = %d \n\n", NUMT, NUMPAD);
	
	double avgMegaAdds = sumMegaAdds/(double)NUMTRIES;
    printf( "   Peak Performance = %6.2lf MegaAdds/Sec\n", maxMegaAdds );
    printf( "Average Performance = %6.2lf MegaAdds/Sec\n\n", avgMegaAdds );
}