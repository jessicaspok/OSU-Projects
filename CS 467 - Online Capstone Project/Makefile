CC = g++

CFLAGS = -pipe -std=c++11
OFLAGS = -c -I/usr/include
LFLAGS = $(CFLAGS) -L/usr/lib/

SOURCES =  Object.cpp Character.cpp Detective.cpp Room.cpp gameLoader.cpp Game.cpp main.cpp parsing_module.cpp
OBJECTS =  Object.o Character.o Detective.o Room.o gameLoader.o Game.o main.o parsing_module.o

DEBUG = yes
PROFILE = no
PEDANTIC = no
OPTIMIZATION = -O0

ifeq ($(DEBUG), yes)
	CFLAGS += -g
	OPTIMIZATION = -O0
endif

ifeq ($(PROFILE), yes)
	CFLAGS += -pg
endif

CFLAGS += $(OPTIMIZATION)

all:	game

game: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o game

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o game

rebuild: clean all

.PHONY : clean
.SILENT : clean