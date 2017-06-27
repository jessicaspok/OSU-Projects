README:

Welcome to the test driver for the Project 1 max subarray algorithms assignment.
The four algorithms written for this assignment find the maximum subarray
within several input arrays provided in file MSS_Problems.txt.

There are two programs included - a program to verify that the algorithms work correctly,
based on an input file MSS_TestProblems.txt, and a program that finds each algorithm's running
time for a random array of size n, based on user input, and outputs a table comparing the
results of ten test runs.

To run the "testing for correctness" program:

0) change directories to the TestingforCorrectness subfolder
1) compile the program using the included makefile (run "make")
2) ensure that the inputfile "MSS_TestProblems.txt" is in the current folder
3) execute the binary that is generated, called "main".
4) view the output maximum subarray boundaries and sum for each algorithm, for 
	each line in the input file. Results are also written to the output file "MSS_Results.txt"

To run the "experimental analysis" program

0) change directories to the ExperimentalTesting subfolder
1) Compile the program using the included makefile (run "make")
2) Execute the binary that is generated. It is called "main".
3) Enter the size of array to use for the test. E.g., 10, 100, or 1000.
4) View the resulting execution time for 10 runs of each algorithm, arranged by column.