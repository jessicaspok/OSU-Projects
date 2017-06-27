#/usr/bin/env python3

from os import system

def main():
    datafile = "proj6DataMR.csv"

    locals = [32, 64, 128, 256]
    globals = [1024, 10240, 102400, 512000, 1024000, 5120000, 8000000]

    with open(datafile, "a") as f:
        f.write("\nTesting Multiplication Reduction\n")
        f.write("Num_Elements, Local_Size, Num_Work_Groups, Performance\n")
    for g in globals:
        for l in locals:
            cmd = ("g++ -o second second.cpp -lm -fopenmp -lOpenCL -DNUM_ELEMENTS={} -DLOCAL_SIZE={}").format(g, l)
            system(cmd)
            cmd = "./second {}".format(datafile)
            system(cmd)
			
    cmd = "rm -f second"
    system(cmd)
    cmd = "cat proj6DataMR.csv"
    system(cmd)

if __name__ == "__main__":
    main()