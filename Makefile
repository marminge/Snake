# -*- Makefile -*-
SRCDIR = ./src
INCDIR = ./include
CC = gcc
INCLUDE = -I/usr/include/SDL2 -I$(INCDIR)
CFLAGS = -g $(INCLUDE) -c
LDFLAGS = -lSDL2 -lSDL2_ttf

snake: main.c snake.c food.c text.c
	$(CC) -o snake main.o snake.o food.o text.o $(LDFLAGS)

main.c: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $(SRCDIR)/main.c

snake.c: $(SRCDIR)/snake.c $(INCDIR)/snake.h
	$(CC) $(CFLAGS) $(SRCDIR)/snake.c

food.c: $(SRCDIR)/food.c $(INCDIR)/food.h
	$(CC) $(CFLAGS) $(SRCDIR)/food.c

text.c: $(SRCDIR)/text.c $(INCDIR)/text.h
	$(CC) $(CFLAGS) $(SRCDIR)/text.c
