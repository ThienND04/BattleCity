OBJS = src/*

CC = g++

COMPILER_FLAGS = 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = game

install: ${OBJS}
	${CC} ${COMPILER_FLAGS} ${OBJS} ${LINKER_FLAGS} -o ${OBJ_NAME} 