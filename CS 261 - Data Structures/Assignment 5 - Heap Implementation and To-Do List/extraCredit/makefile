CC = gcc
CFLAGS = -g -Wall -std=c99

all : tests prog

tests : tests.o dynamicArray.o CuTest.o task.o
	$(CC) $(CFLAGS) -o $@ $^

prog : main.o dynamicArray.o task.o
	$(CC) $(CFLAGS) -o $@ $^

dynamicArray.o : dynamicArray.h dynamicArray.c

main.o : main.c dynamicArray.h task.h

task.o : task.c task.h

tests.o : tests.c dynamicArray.h CuTest.h task.h

CuTest.o : CuTest.h CuTest.c

.PHONY : memCheckTests memCheckToDo clean

memCheckTests :
	valgrind --tool=memcheck --leak-check=yes tests

clean :
	-rm *.o
	-rm tests
	-rm prog
