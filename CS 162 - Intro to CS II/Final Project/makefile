CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = Bathroom.o Bedroom.o Hallway.o Kitchen.o LivingRoom.o main.o Player.o Space.o 

SRCS = Bathroom.cpp Bedroom.cpp Hallway.cpp Kitchen.cpp LivingRoom.cpp main.cpp Player.cpp Space.cpp 

HEADERS = Bathroom.hpp Bedroom.hpp Hallway.hpp Kitchen.hpp LivingRoom.hpp Player.hpp Space.hpp 

Lab1: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o Final

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm	-f	*.o Final
