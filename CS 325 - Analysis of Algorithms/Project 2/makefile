#Student: Edward Francis
#Class: CS 325 Algorithms
#Date: January 26, 2017
#Description: makefile for Project 2: Making Change

CXX = g++
CXX += -Wall
CXX += -pedantic-errors
CXXFLAGS = -std=c++0x


all: changefromfile.cpp algotiming.cpp
	${CXX} ${CXXFLAGS} changefromfile.cpp -o changefromfile
	${CXX} ${CXXFLAGS} algotiming.cpp -o algotiming

project2: changefromfile.cpp algotiming.cpp
	${CXX} ${CXXFLAGS} changefromfile.cpp -o changefromfile
	${CXX} ${CXXFLAGS} algotiming.cpp -o algotiming
	
changefromfile: changefromfile.cpp
	${CXX} ${CXXFLAGS} changefromfile.cpp -o changefromfile
	
algotiming: algotiming.cpp
	${CXX} ${CXXFLAGS} algotiming.cpp -o algotiming
	
clean:
	rm -f changefromfile algotiming *.o
