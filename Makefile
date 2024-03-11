CC = g++
CFLAGS = -W -Wall
SRC = add_nbo.cpp 
OBJ = add_nbo.o
PROG = run

all : ${PROG}
${PROG} : ${OBJ}
	${CC} -o ${PROG} ${OBJ}
	rm *.o
${Obj} : ${SRC}
	${CC} ${CFLAGS} -c -o add_nbo.o add_nbo.cpp
clean :
	rm *.o run
