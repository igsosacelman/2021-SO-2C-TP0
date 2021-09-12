#Globales
CC = gcc
CFLAGS = -g -Wall
OUTFILE = server.out
MAIN = server.c

LINK = -lpthread -lcommons -lcspecs

SRC = $(shell find ./src -type f -iname "*.c" -exec basename {} \;)
OBJ = $(SRC:%.c=./obj/%.o)

#Reglas
build: makefolder $(OBJ)
	$(CC) -o $(OUTFILE) $(MAIN) $(OBJ) $(CFLAGS)

./obj/%.o: ./src/%.c
	$(CC) -c $< -o $@ $(LINK) $(CFLAGS)

makefolder:
	if [ ! -d ./obj ]; then mkdir obj; fi

#Clean
clean:
	rm -rf obj
	rm -rf *.out
	rm -rf *.log