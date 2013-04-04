
CC = g++
CFLAGS=-c -DLINUX -I. -LSDL/lib
LDFLAGS=-lSDL -lSDL_gfx
SRC = main.cpp game.cpp board.cpp io.cpp pieces.cpp
OBJ = $(SRC:.cpp=.o)
EXE = tetris


build : $(SRC) $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJ) $(EXE)

rebuild : clean build


