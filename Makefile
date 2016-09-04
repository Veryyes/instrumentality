CC = gcc
CFLAGS = -w -g -O0
INCLUDE = -I ./include
LINKS = -lSDL2 -lSDL2_image
OBJS = ./obj/map.o\
./obj/util.o\
./obj/player.o\
./obj/surface_hashmap.o\
./obj/quadtree.o

game: $(OBJS)
	$(CC) $(CFLAGS) ./src/game.c $(INCLUDE) $(LINKS) -o bin/game $(OBJS)

./obj/map.o: ./obj/util.o ./obj/surface_hashmap.o ./obj/quadtree.o
	$(CC) $(CFLAGS) ./src/map.c -c $(INCLUDE) $(LINKS) ./obj/surface_hashmap.o ./obj/util.o ./obj/quadtree.o -o ./obj/map.o

./obj/util.o:
	$(CC) $(CFLAGS) ./src/util.c -c $(INCLUDE) $(LINKS) -lJPEG -o ./obj/util.o

./obj/player.o: ./obj/util.o ./obj/surface_hashmap.o
	$(CC) $(CFLAGS) ./src/player.c -c $(INCLUDE) $(LINKS) ./obj/surface_hashmap.o ./obj/util.o -o./obj/player.o

./obj/surface_hashmap.o:
	$(CC) $(CFLAGS) ./src/surface_hashmap.c -c $(INCLUDE) $(LINKS) -o ./obj/surface_hashmap.o

./obj/quadtree.o:
	$(CC) $(CFALGS) ./src/quadtree.c -c $(INCLUDE) -o ./obj/quadtree.o

clean:
	rm -f bin/*
cleanall:
	rm -f bin/*
	rm -f obj/*
