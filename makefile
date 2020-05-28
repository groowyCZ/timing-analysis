CFLAGS += -Wall -Wextra -std=c++17 -O3 -g

SRC = src/main.cpp src/Channel.cpp
OBJ = ${SRC:.cpp=.o}
DEP = ${SRC:.cpp=.d}

all: main

%.o: %.cpp
	g++ -c ${CFLAGS} $< -o $@

main: src/main.o src/Channel.o
	g++ ${CFLAGS} -o main src/main.o src/Channel.o

clean:
	rm -f ${DEP} ${OBJ} main

-include ${DEP}
