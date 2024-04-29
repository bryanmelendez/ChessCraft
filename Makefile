######################################################################
# Makefile: Makefile for ChessCrafters 
######################################################################

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -Wall -std=c11
LFLAGS = -Wall -lm

OPTS = -g

PROJECT = simple

all: Chess 

tar: 
	tar cvzf Chess_V1.0_src.tar.gz bin doc/Chess_SoftwareSpec.pdf doc/Chess_UserManual.pdf src INSTALL_src.md README.md COPYRIGHT.md Makefile 
	tar tvzf Chess_V1.0_src.tar.gz
	make clean all
	tar cvzf Chess_V1.0.tar.gz bin doc/Chess_UserManual.pdf INSTALL.md README.md COPYRIGHT.md 
	tar tvzf Chess_V1.0.tar.gz

########### generate object files ###########

#target to generate Bot.o
Bot.o: src/Bot.h src/Bot.c
	$(CC) $(CFLAGS) -c src/Bot.c -o src/Bot.o

#target to generate Pieces.o 
Piece.o: src/Piece.h src/Piece.c
	$(CC) $(CFLAGS) -c src/Piece.c -o src/Piece.o

#target to generate Board.o
Board.o: src/Board.h src/Piece.h src/Board.c
	$(CC) $(CFLAGS) -c src/Board.c -o src/Board.o

#target to generate Board_Test.o
Board_Test.o: src/Board_Test.c src/Piece.h src/Board.h src/GameLogic.h
	$(CC) $(CFLAGS) -c src/Board_Test.c -o src/Board_Test.o

#target to generate Menu.o
Menu.o: src/Menu.h src/Menu.c
	$(CC) $(CFLAGS) -c src/Menu.c -o src/Menu.o

#target to generate Log.o
Log.o: src/Log.h src/Log.c 
	$(CC) $(CFLAGS) -c src/Log.c -o src/Log.o

#target to generate GameLogic.o
GameLogic.o: src/GameLogic.c src/GameLogic.h src/Piece.h src/Board.h
	$(CC) $(CFLAGS) -c src/GameLogic.c -o src/GameLogic.o

#target to generate Game.o
Game.o: src/Game.c src/Game.h src/GameLogic.h
	$(CC) $(CFLAGS) -c src/Game.c -o src/Game.o

#target to generate Chess.o
Chess.o: src/Chess.c src/GameLogic.h
	$(CC) $(CFLAGS) -c src/Chess.c -o src/Chess.o


#target to generate Chess.o
Chess_Test.o: src/Log.h src/Chess.c src/Menu.h src/Piece.h src/GameLogic.h
	$(CC) $(CFLAGS) -c src/Chess.c -o src/Chess_Test.o
 
Chess: src/Chess.o src/Game.o src/Bot.o src/GameLogic.o src/Log.o src/Menu.o src/Board.o src/Piece.o
	$(CC) $(LFLAGS) src/Chess.o src/Game.o src/Bot.o src/GameLogic.o src/Log.o src/Menu.o src/Board.o src/Piece.o -o bin/chess

#target to generate Board.o
test: src/Board.o src/Piece.o src/Board_Test.o src/GameLogic.o src/Log.o src/Menu.o src/Game.o src/Bot.o
	$(CC) $(CFLAGS) src/Board.o src/Piece.o src/GameLogic.o src/Bot.o src/Board_Test.o src/Log.o src/Menu.o src/Game.o -o bin/Board_Test
	./bin/Board_Test

#target to clean the directory
clean:
	rm -f src/*.o
	rm -f bin/*_Test
	rm -f bin/chess
