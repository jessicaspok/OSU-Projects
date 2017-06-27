#/usr/bin/env python3

from os import system

def main():
    datafile = "proj5Data.csv"

    arraysize = [1000, 10000, 30000, 50000, 70000, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000, 15000000, 20000000, 25000000, 32000000]
    
    tests = ["SIMD vs C++ Multiplication", "SIMD vs C++ Multiplication-Reduction"]
    
    for test in tests:
        with open(datafile, "a") as f:
            f.write("\nTesting {}\n".format(test))
            f.write("Array Size, C++ Peak, C++ Average, SIMD Peak, SIMD Average, Speedup\n")
        for size in arraysize:
            cmd = ("g++ -DARRAYSIZE={} -DTEST={} project5.cpp simd.p5.cpp -o proj5 -lm -fopenmp").format(size, tests.index(test))
            system(cmd)
            cmd = "./proj5 {}".format(datafile)
            system(cmd)
			
    cmd = "rm -f proj5"
    system(cmd)
    cmd = "cat proj5Data.csv"
    system(cmd)

if __name__ == "__main__":
    main()