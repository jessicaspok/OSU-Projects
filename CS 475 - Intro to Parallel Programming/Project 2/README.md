Project #2

OpenMP: Static vs Dynamic and Small vs. Large Chunksize

Investigate OpenMP scheduling by deliberately giving each thread a very different amount of work to do and testing how OpenMP can best accomplish that

1. Create a global floating-point array and fill it with random floating-point numbers
2. Use a variety of number of threads
3. Test both static and dynamic scheduling and chunksizes of 1 and 4096
4. Record the data

Compile in Linux by typing:

% g++ -I/usr/local/common/gcc-5.4.0/ project2.cpp –o proj2 –lm –fopenmp

Execute the program with:

% ./proj2

