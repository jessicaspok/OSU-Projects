Project #0

Simple OpenMP Experiment - A great use for parallel programming is identical operations on large arrays of numbers

1. Pick an array size to do the arithmetic on
2. Using OpenMP, pairwise multiply two large floating-point arrays, putting the results in another array
3. Do this for one thread and do this for four threads: 
	#define NUMT 1 
	and 
	#define NUMT 4
4. Time the two runs
5. Calculate the speedup from 1 thread to 4 threads
6. Compute the parallel fraction