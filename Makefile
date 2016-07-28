CC = gcc
CFLAGS = -w -g
INCLUDE = -I ./include
LINKS = -lSDL2 -lSDL2_image
OBJS = ./obj/map.o\
./obj/util.o

game: $(OBJS)
	$(CC) $(CFLAGS) ./src/game.c $(INCLUDE) $(LINKS) -o bin/game $(OBJS)

./obj/map.o: ./obj/util.o
	$(CC) $(CFLAGS) ./src/map.c -c $(INCLUDE) $(LINKS) ./obj/util.o -o ./obj/map.o

./obj/util.o:
	$(CC) $(CFLAGS) ./src/util.c -c $(INCLUDE) $(LINKS) -o ./obj/util.o

clean:
	rm -f bin/*
cleanall:
	rm -f bin/*
	rm -f obj/*
