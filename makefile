CFLAGS += -Wall -Wextra -std=c++17 -O3

SRC = main.cpp
OBJ = ${SRC:.cpp=.o}
DEP = ${SRC:.cpp=.d}

all: main

main: main.o
	g++ ${CFLAGS} -o main main.o

clean:
	rm -f ${DEP} ${OBJ} main

-include ${DEP}
