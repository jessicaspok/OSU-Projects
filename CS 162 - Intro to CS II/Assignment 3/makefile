CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = Barbarian.o BlueMen.o Creature.o Die.o Game.o HarryPotter.o Vampire.o Medusa.o main.o

SRCS = Barbarian.cpp BlueMen.cpp Creature.cpp Die.cpp Game.cpp HarryPotter.cpp Vampire.cpp Medusa.cpp main.cpp

HEADERS = Barbarian.h BlueMen.h Creature.h Die.h Game.h HarryPotter.h Vampire.h Medusa.h 

Lab1: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o Assign3

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm	-f	*.o Assign3
