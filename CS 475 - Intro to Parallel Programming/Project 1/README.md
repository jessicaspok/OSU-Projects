Project #1

OpenMP: Numeric Integration with OpenMP

Take two Bézier surfaces and use numerical techniques to find the volume between the bottom surface and the top surface

1. Using OpenMP, compute the total volume betwen the two surfaces
2. Use a variety of number of subdivisions (NUMNODES) and number of threads (NUMT)
3. Record the data
4. Compute the parallel fraction
5. Determine what maximum speed-up you could ever get

Compile in Linux by typing:

%    g++ -I/usr/local/common/gcc-5.4.0/ project1.cpp –o proj1 –O3 –lm –fopenmp

Execute the program with:

%    ./proj1
