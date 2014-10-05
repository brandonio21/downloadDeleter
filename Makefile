# Makefile for downloadDeleter.c

EXEC_NAME = downloadDeleter
CC_FLAGS = -Wall -o ${EXEC_NAME}
CC = gcc

downloadDeleter.c: strings.h downloadDeleter.service
	${CC} ${CC_FLAGS} $@
	echo ExecStart=${PWD}/${EXEC_NAME} >> downloadDeleter.service
	
