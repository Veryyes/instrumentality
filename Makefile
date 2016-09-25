CC = gcc
OPTS = -w -g -O0

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin
LIBDIR = ./lib

SRCS = $(SRCDIR)/game.c\
$(SRCDIR)/util.c\
$(SRCDIR)/player.c\
$(SRCDIR)/map.c\
$(SRCDIR)/surface_hashmap.c


INCLUDE = $(addprefix -I ,$(INCDIR))
LINKS = -lSDL2 -lSDL2_image -lquadtree -lm
LIBS = $(addprefix -L, $(LIBDIR))

OBJS = ${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}

CFLAGS = $(OPTS) $(INCLUDE) $(LIBS) $(LINKS)

TARGET = $(BINDIR)/game

all: $(TARGET)

$(TARGET): $(OBJS)
	${CC} -o $@ $(OBJS) ${CFLAGS}

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS)
cleanall:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*
