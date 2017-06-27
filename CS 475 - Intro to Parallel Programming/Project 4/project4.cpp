/**********************************************
 * Jessica Spokoyny
 * CS 475 - Project 4
 * May 15, 2017
 *********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =	0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =				2.0;	// plus or minus noise

const float AVG_TEMP =					50.0;	// average
const float AMP_TEMP =					20.0;	// plus or minus
const float RANDOM_TEMP =				10.0;	// plus or minus noise

const float MIDTEMP =					40.0;
const float MIDPRECIP =					10.0;

int		NowYear;		// 2017 - 2022
int		NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int		NowNumDeer;		// number of deer in the current population
int 	NowNumCoyotes;	// number of coyotes in the current population

unsigned int seed = 0;	// seed the random number generator

float Ranf(unsigned int *seedp, float low, float high) {
        float r = (float) rand_r(seedp);              // 0 - RAND_MAX
        return(low  +  r * (high - low) / (float)RAND_MAX);
}

int Ranf(unsigned int *seedp, int ilow, int ihigh) {
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;
        return (int)(Ranf(seedp, low, high));
}

float SQR(float x) {
        return x*x;
}

void GrainDeer();
void Grain();
void Watcher();
void Coyote();

int main(int argc, char* argv[]) {

	#ifndef _OPENMP
		fprintf( stderr, "OpenMP is not supported here -- sorry.\n");
		return 1;
	#endif
	
	// starting date and time:
	NowMonth =    0;
	NowYear  = 2017;

	// starting state (feel free to change this if you want):
	NowNumDeer = 10;
	NowHeight =  10.;
	
	NowTemp = 60.;
	NowPrecip = 10.;
	NowNumCoyotes = 8;
	
	omp_set_num_threads(4);	// same as # of sections
	
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		#pragma omp section
		{
			Coyote( );	// your own
		}
	}   // implied barrier -- all functions must return in order to allow any of them to get past here
		
	return 0;	
}
	
	
void GrainDeer() {
	while(NowYear < 2023) {
		// compute a temporary next-value for this quantity based on the current state of the simulation:
		int  tmpNumDeer = NowNumDeer;
		
		// grain height effect on deer
		if (NowHeight > tmpNumDeer)
			tmpNumDeer++;
		else if (NowHeight < tmpNumDeer)
			tmpNumDeer--;
		
		// coyote effect on deer
		if (tmpNumDeer < .75 * NowNumCoyotes)
			tmpNumDeer--;
 
		if (tmpNumDeer <= 0)
			tmpNumDeer = 0;
		
		// DoneComputing barrier:
		#pragma omp barrier
		NowNumDeer = tmpNumDeer;

		// DoneAssigning barrier:
		#pragma omp barrier

		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void Grain() {
	while(NowYear < 2023) {
		// compute a temporary next-value for this quantity based on the current state of the simulation: 
		float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));
		float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));
		
		float tmpHeight = NowHeight;
		tmpHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		tmpHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		
		if(tmpHeight <= 0)
			tmpHeight = 0;

		// DoneComputing barrier:
		#pragma omp barrier
		NowHeight = tmpHeight;

		// DoneAssigning barrier:
		#pragma omp barrier

		// DonePrinting barrier:
		#pragma omp barrier
	}
}

void Watcher() {
	while(NowYear < 2023){
		FILE * f;
		f = fopen("./results.csv", "a");
	
		// DoneComputing barrier:
		#pragma omp barrier
		
		// DoneAssigning barrier:
		#pragma omp barrier
		
		// Write to file
		fprintf(f, "%d, %d, %d, %f, %f, %f\n", NowMonth, NowNumDeer, NowNumCoyotes, NowPrecip, NowTemp, NowHeight);
		
		// print information
		printf("Now Year = %d\n",     	 NowYear);
		printf("Now Month = %d\n",    	 NowMonth);
		printf("Now Num Deer = %d\n", 	 NowNumDeer);
		printf("Now Num Coyotes = %d\n", NowNumCoyotes);
		printf("Now Precip = %f\n",   	 NowPrecip);
		printf("Now Temp = %f\n",     	 NowTemp);
		printf("Now Height = %f\n\n",    NowHeight);
		
		NowMonth += 1;
		
		if (NowMonth == 12) {
			NowMonth = 0;
			NowYear++;
		}
		
		// current state information:
		float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);

		float temp = AVG_TEMP - AMP_TEMP * cos(ang);
		
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
		
		// Compute temperature and precipition 
		NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);
		NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);

		if (NowPrecip <= 0.)
			NowPrecip = 0.;
		
		// DonePrinting barrier:
		#pragma omp barrier
		
		fclose(f);
	}
}

/* if the number of deer in the population is at least twice as big as the number of coyotes in the population, the coyotes
   will have enough deer to eat and the population will grow by 1. But, if the population of deer is
   not twice as big as the population of coyotes, 1 coyote will die of hunger */
void Coyote() {
	while(NowYear < 2023){
		// compute a temporary next-value for this quantity based on the current state of the simulation:
		int tmpNumCoyotes = NowNumCoyotes;
		
		if (NowNumDeer < .5 * tmpNumCoyotes)
			tmpNumCoyotes--;
		else
			tmpNumCoyotes++;
		
		if (tmpNumCoyotes <= 0)
			tmpNumCoyotes = 0;
		
		// DoneComputing barrier:
		#pragma omp barrier
		
		NowNumCoyotes = tmpNumCoyotes;
		//NowHeight = tmpHeight;
		
		// DoneAssigning barrier:
		#pragma omp barrier
		
		// DonePrinting barrier:
		#pragma omp barrier
	}
}


