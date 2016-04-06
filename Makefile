CC = gcc
CFLAGS = -g -O2 -Wall -std=gnu11
LFLAGS = -lSDLmain -lSDL_image -lSDL2

SRCS = src/main.c src/surface.c src/event_handler.c hashmap/hashmap.c hashmap/stack.c
HDRS = src/main.h src/surface.h src/event_handler.c hashmap/hashmap.h hashmap/stack.h
OBJS = $(SRCS:.c=.o)
PROG = FreeSpace

all : $(PROG)

$(PROG) : $(OBJS) $(HDRS)
	$(CC) $(OBJS) -o $(PROG) $(LFLAGS)

main.o : src/main.c src/main.h
	$(CC) $(CFLAGS) -c src/main.c

surface.o : src/surface.c src/surface.h src/main.h
	$(CC) $(CFLAGS) -c src/surface.c

event_handler.o : src/event_handler.c src/event_handler.h src/main.h
	$(CC) $(CFLAGS) -c src/event_handler.c

hashmap.o : hashmap/hashmap.c hashmap/hashmap.h hashmap/stack.h
	$(CC) $(CFLAGS) -c hashmap/hashmap.c -o hashmap/hashmap.o

stack.o : hashmap/stack.c hashmap/stack.h
	$(CC) $(CFLAGS) -c hashmap/stack.c -o hashmap/stack.o

tests.o : tests.c 
	$(CC) $(CFLAGS) -c tests.c

testing : tests.o hashmap/stack.o hashmap/hashmap.o
	$(CC) tests.o hashmap/stack.o hashmap/hashmap.o -o tests $(LFLAGS) -lcunit
	./tests

clean : 
	rm -f $(OBJS) *~ *.o

rebuild : clean $(PROG)
