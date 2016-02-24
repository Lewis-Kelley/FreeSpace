CC = gcc
CFLAGS = -g -O2 -Wall -std=gnu11
LFLAGS = -lSDLmain -lSDL_image -lSDL

SRCS = main.c surface.c event_handler.c
OBJS = $(SRCS:.c=.o)
PROG = FreeSpace

$(PROG) : $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(LFLAGS)

main.o : main.c main.h
	$(CC) $(CFLAGS) -c main.c

surface.o : surface.c surface.h main.h
	$(CC) $(CFLAGS) -c surface.c

event_handler.o : event_handler.c event_handler.h main.h
	$(CC) $(CFLAGS) -c event_handler.c

clean : 
	rm -f $(OBJS) *~

rebuild : clean $(PROG)
