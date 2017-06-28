Project #3

False Sharing

Demonstrate the effects of false sharing on multicore programs

1. Fix #1: pad the rest of the structure with a certain number, NUMPAD, of integers
2. Use a variety of number of threads
3. Time the length of execution
4. Fix #2: accumulate the sum in a variable that is private to each thread
5. Time the length of execution
6. Record the data

Compile and execute the program for fix 1 with a script by typing:

for t in 1 2 4   

> do

> echo NUMT = $t

> for p in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

> do

> echo NUMPAD = $p

> g++ -DNUMT=$t -DNUMPAD=$p -DFIX=1 project3.cpp -o proj3 -lm -fopenmp

> ./proj3

> done

> done


Compile and execute the program again for fix 2 by typing:

for t in 1 2 4   

> do

> echo NUMT = $t

> g++ -DNUMT=$t -DNUMPAD=0 -DFIX=2 project3.cpp -o proj3 -lm -fopenmp

> ./proj3

> done
