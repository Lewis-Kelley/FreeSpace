CC = gcc
CFLAGS = -g -O2 -Wall -std=gnu11 -DDEBUG
LFLAGS = -lSDL2main -lSDL2_image -lSDL2

SRCS = src/main.c src/surface.c src/event_handler.c src/hashmap.c src/stack.c
OBJS = $(SRCS:.c=.o)
PROG = FreeSpace

all : $(PROG) testing

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(LFLAGS)

main.o : src/main.c src/main.h
	$(CC) $(CFLAGS) -c src/main.c

surface.o : src/surface.c src/surface.h src/main.h
	$(CC) $(CFLAGS) -c src/surface.c

event_handler.o : src/event_handler.c src/event_handler.h src/main.h
	$(CC) $(CFLAGS) -c src/event_handler.c

hashmap.o : src/hashmap.c src/hashmap.h src/stack.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o src/hashmap.o

stack.o : src/stack.c src/stack.h
	$(CC) $(CFLAGS) -c src/stack.c -o src/stack.o

hashmap-test : src/hashmap-test.c src/hashmap.c src/hashmap.h src/stack.c src/stack.h
	$(CC) $(CFLAGS) $(LFLAGS) src/hashmap-test.c src/hashmap.c src/stack.c -o hashmap-test

tests.o : tests.c 
	$(CC) $(CFLAGS) -c tests.c

testing : tests.o src/stack.o src/hashmap.o
	$(CC) tests.o src/stack.o src/hashmap.o -o tests $(LFLAGS) -lcunit
	./tests

clean : 
	rm -f $(OBJS) *~ *.o

rebuild : clean $(PROG)
