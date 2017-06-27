CXX = g++
CXX += -Wall
CXX += -pedantic-errors
CXXFLAGS = -std=c++0x

SRCS = main.cpp
CPPFILES = main.cpp

all: ${SRCS}
	${CXX} ${CXXFLAGS} ${CPPFILES} -o main

project1: ${SRCS}
	${CXX} ${CXXFLAGS} ${CPPFILES} -o main

clean:
	rm -f main *.o
