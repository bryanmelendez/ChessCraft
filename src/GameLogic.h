// Include Libraries
#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__
#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "Log.h"
#include "Piece.h"

typedef struct
{
    Location *gameboard[8][8];
    LogList *game_log; // linked list or however we decide to implement it
    CurrentPlayer player;
    PieceColor color;
    int game_mode;
    int check;
    int mate;
} Game;

// General function called to calculate possible moves
int CalculateMoves(Game* game, Location* gameboard[BOARD_SIZE][BOARD_SIZE], Coordinates coords, int for_check);
// filters out moves that cause the player to put themselves in check
int FilterMoves(Game* game, Location* gameboard[BOARD_SIZE][BOARD_SIZE], Coordinates coords);
// Makes a copy of the gameboard for use in check function
void CopyGameBoard(Location* old_board[BOARD_SIZE][BOARD_SIZE], Location* new_board[BOARD_SIZE][BOARD_SIZE]);
// This function checks to see if the king is in check. If it is, sets the game check to 1
int Check(Game* game, Location* gameboard[BOARD_SIZE][BOARD_SIZE], int same_side);
// This function will take the current coordinate of a piece chosen by the user and move to a new place given the move is valid.
int MovePiece(Location *game_board[BOARD_SIZE][BOARD_SIZE], Coordinates start_place, Coordinates end_place, Game* game);
// this function allows the castling move by a user if move is valid
int Castle(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece *king, Coordinates new_king, Game* game);
// this function allows the EnPassant move by a user if move is valid
int EnPassant(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece* pawn, Coordinates end_place);
// clears the en passant member of location struct
int ClearEnPassant(Game* game);
// this function allows Pawn Promotion by a user if move is valid
int PawnPromotion(Location *game_board[BOARD_SIZE][BOARD_SIZE], CurrentPlayer player);
// Arguments not finalized, still pseudocoding
int CheckMate(Game *game, Location* gameboard[BOARD_SIZE][BOARD_SIZE], int same_side);
// Captures the piece
void CapturePiece(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece* moved_piece, Coordinates end_place);
// Clears the board's valid moves
void ClearBoard(Location *gameboard[BOARD_SIZE][BOARD_SIZE]);

#endif
