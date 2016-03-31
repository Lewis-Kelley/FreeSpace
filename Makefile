CC = gcc
CFLAGS = -g -O2 -Wall -std=gnu11 -DDEBUG
LFLAGS = -lSDL2main -lSDL2_image -lSDL2

SRCS = src/main.c src/surface.c src/event_handler.c src/hashmap.c src/stack.c
OBJS = $(SRCS:.c=.o)
PROG = FreeSpace

all : $(PROG) hashmap-test

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(LFLAGS)

main.o : main.c main.h
	$(CC) $(CFLAGS) -c src/main.c

surface.o : surface.c surface.h main.h
	$(CC) $(CFLAGS) -c src/surface.c

event_handler.o : event_handler.c event_handler.h main.h
	$(CC) $(CFLAGS) -c src/event_handler.c

hashmap.o : hashmap.c hashmap.h stack.h
	$(CC) $(CFLAGS) -c src/hashmap.c

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c src/stack.c

hashmap-test : src/hashmap-test.c src/hashmap.c src/hashmap.h src/stack.c src/stack.h
	$(CC) $(CFLAGS) $(LFLAGS) src/hashmap-test.c src/hashmap.c src/stack.c -o hashmap-test
clean : 
	rm -f $(OBJS) *~

rebuild : clean $(PROG)
