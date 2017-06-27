#/usr/bin/env python3

from os import system

def main():
    datafile = "proj6DataMA.csv"

    locals = [8, 16, 32, 64, 128, 256, 512]
    globals = [1024, 10240, 102400, 512000, 1024000, 5120000, 8000000]

    with open(datafile, "a") as f:
        f.write("\nTesting Multiplication Addition\n")
        f.write("Num_Elements, Local_Size, Num_Work_Groups, Performance\n")
    for g in globals:
        for l in locals:
            cmd = ("g++ -o first first.cpp -lm -fopenmp -lOpenCL -DNUM_ELEMENTS={} -DLOCAL_SIZE={} -DMULTADD").format(g, l)
            system(cmd)
            cmd = "./first {}".format(datafile)
            system(cmd)
			
    cmd = "rm -f first"
    system(cmd)
    cmd = "cat proj6DataMA.csv"
    system(cmd)

if __name__ == "__main__":
    main()