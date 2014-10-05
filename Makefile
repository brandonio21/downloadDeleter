# Makefile for downloadDeleter.c

CC_FLAGS = -Wall -o downloadDeleter 
CC = gcc

downloadDeleter.c: strings.h
	${CC} ${CC_FLAGS} $@
	
