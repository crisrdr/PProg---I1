########################## VARIABLES ##########################

EXE = play
OBJ = command.o game_loop.o game_reader.o game.o graphic_engine.o space.o
GCC = gcc -Wall -ansi -pedantic -c -g


##################### ETIQUETAS DEL MAKE #####################

all: $(EXE)

$(EXE): $(OBJ)
	gcc -o $(EXE) $(OBJ) -L ./ -lscreen

command.o: command.c command.h
	$(GCC) command.c

game_loop.o: game_loop.c graphic_engine.h game.h command.h space.h types.h
	$(GCC) game_loop.c

game_reader.o: game_reader.c game_reader.h types.h space.h game.h command.h
	$(GCC) game_reader.c

game.o: game.c game.h command.h space.h types.h game_reader.h
	$(GCC) game.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h space.h types.h libscreen.h
	$(GCC) graphic_engine.c

space.o: space.c space.h types.h
	$(GCC) space.c


clean: 
	rm $(EXE) *.o 

run:
	./$(EXE) hormiguero.dat

val:
	valgrind --leak-check=full -s ./play hormiguero.dat