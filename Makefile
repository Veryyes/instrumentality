CC = gcc
FLAGS = -w
SRC = ./src/game.c
INCLUDE = ./include
LINKS = -lSDL2 -lSDL2_image

all:
	$(CC) $(FLAGS) $(SRC) -I $(INCLUDE) $(LINKS) -o game
