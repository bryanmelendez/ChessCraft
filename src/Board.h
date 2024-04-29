
//This is the header file for functions dealing with the setup and updating of the board
//
#ifndef BOARD_H
#define BOARD_H
#include <assert.h>
#include "Piece.h"

/* sets up starting gameboard with pieces */
void InitializeGameboard(Location* gameboard[8][8], int color);

/* returns piece color as a char "B" or "W" */
char GetPieceColor(Location* gameboard[8][8], int col, int row);

/* returns piece type as a char "R", "P", "K",... */
char GetPieceType(Location* gameboard[8][8], int col, int row);

/* prints board */
void PrintBoard(Location* gameboard[8][8]);

/* frees board memory */
void DeleteBoard(Location* gameboard[8][8]);

/* frees piece memory */ 
void DeletePiece(Piece* piece);
#endif 

