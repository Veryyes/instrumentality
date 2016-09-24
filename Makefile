CC = gcc
OPTS = -w -g -O0

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
BINDIR = ./bin

SRCS = $(SRCDIR)/game.c\
$(SRCDIR)/util.c\
$(SRCDIR)/player.c\
$(SRCDIR)/map.c\
$(SRCDIR)/surface_hashmap.c

INCLUDE = $(addprefix -I,$(INCDIR))
OBJS = ${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}
CFLAGS = $(OPTS) $(INCLUDE)

TARGET = $(BINDIR)/game

all: $(TARGET)

$(TARGET): $(OBJS)
	${CC} ${CFLAGS} -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
cleanall:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*
