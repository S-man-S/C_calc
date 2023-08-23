CC=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=../build/


all: graph


graph: input.o calc.o stack.o draw.o graph.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)graph


graph.o: graph.c
	$(CC) $(CFLAGS) -c $^

input.o: input.c
	$(CC) $(CFLAGS) -c $^ 

calc.o: calc.c
	$(CC) $(CFLAGS) -c $^ 

draw.o: draw.c
	$(CC) $(CFLAGS) -c $^ 

stack.o: stack.c
	$(CC) $(CFLAGS) -c $^ 

clean:
	rm -rf *.o $(TARGET)graph

clear:
	rm -rf *.o 

rebuild: clean all
