CC = gcc
OBJ = main.o map.o game.o world.o terminal.o algorithm.o linkedlist.o
EXEC1 = maze
EXEC2 = linkedlistTest
CFLAGS = -Wall -pedantic -ansi
CONDITION= -DKEEPMOVING

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC1)

$(EXEC2): linkedlistTest.c linkedlist.o
	$(CC) $(CFLAGS) linkedlistTest.c linkedlist.o -o $(EXEC2)

main.o: main.c map.h game.h world.h terminal.h algorithm.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c
	$(CC) $(CFLAGS) -c map.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c $(CONDITION)

world.o: world.c
	$(CC) $(CFLAGS) -c world.c

terminal.o: terminal.c
	$(CC) $(CFLAGS) -c terminal.c

algorithm.o: algorithm.c
	$(CC) $(CFLAGS) -c algorithm.c

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) -c linkedlist.c

clean:
	rm -f $(OBJ) $(EXEC1) $(EXEC2)