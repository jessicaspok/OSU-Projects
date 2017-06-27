CXX = g++
CXX += -Wall
CXX += -pedantic-errors
CXXFLAGS = -std=c++0x

SRCS = tspSolver.cpp tspSolver.hpp

CPPFILES = tspSolver.cpp

all: ${SRCS}
	${CXX} ${CXXFLAGS} ${CPPFILES} -o tsp

project4: ${SRCS}
	${CXX} ${CXXFLAGS} ${CPPFILES} -o tsp

clean:
	rm -f tsp *.o
