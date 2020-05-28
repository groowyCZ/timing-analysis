CFLAGS += -Wall -Wextra -std=c++17 -O3

SRC = src/main.cpp src/Channel.cpp
OBJ = ${SRC:.cpp=.o}
DEP = ${SRC:.cpp=.d}

all: main

main: src/main.o src/Channel.o
	g++ ${CFLAGS} -o main src/main.o src/Channel.o

clean:
	rm -f ${DEP} ${OBJ} main

-include ${DEP}
