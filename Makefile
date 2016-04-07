CC = gcc
CFLAGS = -g -O2 -Wall -std=gnu11
LFLAGS = -lSDLmain -lSDL_image -lSDL2

SRCS = src/main.c src/surface.c src/event_handler.c hashmap/hashmap.c hashmap/stack.c src/image.c src/update.c
HDRS = src/main.h src/surface.h src/event_handler.c hashmap/hashmap.h hashmap/stack.h src/image.h src/update.h
OBJS = $(SRCS:.c=.o)
PROG = FreeSpace

all : $(PROG)

$(PROG) : $(OBJS) $(HDRS)
	$(CC) $(OBJS) -o $(PROG) $(LFLAGS)

event_handler.o : src/event_handler.c src/event_handler.h src/main.h src/game_state.h src/coord.h
	$(CC) $(CFLAGS) -c src/event_handler.c

hashmap.o : hashmap/hashmap.c hashmap/hashmap.h hashmap/stack.h
	$(CC) $(CFLAGS) -c hashmap/hashmap.c

image.o : src/image.c src/image.h
	$(CC) $(CFLAGS) -c src/image.c

main.o : src/main.c src/main.h src/game_state.h src/update.h src/surface.h src/event_handler.h src/image.h
	$(CC) $(CFLAGS) -c src/main.c

stack.o : hashmap/stack.c hashmap/stack.h
	$(CC) $(CFLAGS) -c hashmap/stack.c

surface.o : src/surface.c src/surface.h src/main.h
	$(CC) $(CFLAGS) -c src/surface.c

tests.o : tests.c 
	$(CC) $(CFLAGS) -c tests.c

testing : tests.o hashmap/stack.o hashmap/hashmap.o
	$(CC) tests.o hashmap/stack.o hashmap/hashmap.o -o tests $(LFLAGS) -lcunit
	./tests

update.o : src/update.c src/update.h src/battle_entity.h src/game_state.h src/main.h
	$(CC) $(CFLAGS) -c src/battle_entity.c

clean : 
	rm -f $(OBJS) *~ *.o

rebuild : clean $(PROG)
