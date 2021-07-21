CC=g++
INCLUDES=include
SOURCES= source/Graph.cpp 
BINARY= ./test
PROG=source/main.cpp
FLAGS=-Wall -Werror -g -lm
VFLAGS = --track-origins=yes --leak-check=full --show-leak-kinds=all

all:
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) $(FLAGS)
run:
	$(BINARY)
valgrind:
	@valgrind $(BINARY) $(FLAGS) $(VFLAGS)
zip:
	zip -r GrafoTAD.zip include source test Makefile
