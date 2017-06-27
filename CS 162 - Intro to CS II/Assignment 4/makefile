CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = Barbarian.o BlueMen.o Creature.o Die.o Game.o HarryPotter.o Vampire.o Medusa.o main.o Stack.o Queue.o

SRCS = Barbarian.cpp BlueMen.cpp Creature.cpp Die.cpp Game.cpp HarryPotter.cpp Vampire.cpp Medusa.cpp main.cpp Stack.cpp Queue.cpp

HEADERS = Barbarian.hpp BlueMen.hpp Creature.hpp Die.hpp Game.hpp HarryPotter.hpp Vampire.hpp Medusa.hpp Stack.hpp Queue.hpp

Lab1: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o Assign4

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm	-f	*.o Assign4
