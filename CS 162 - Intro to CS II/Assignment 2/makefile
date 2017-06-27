CXX = g++
CXXFLAGS = -std=c++0x 
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = List.o Item.o groceryMain.o

SRCS = List.cpp Item.cpp groceryMain.cpp

HEADERS = List.h Item.h

Lab1: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o Assign2

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm	-f	*.o Assign2
