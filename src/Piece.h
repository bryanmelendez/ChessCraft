#ifndef __PIECE_H__
#define __PIECE_H__

#include <stdio.h>
#include <assert.h>

#define BOARD_SIZE 8

typedef enum piece_type
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
} PieceType;

typedef enum piece_color
{
	WHITE,
	BLACK,
} PieceColor;

typedef struct
{
	PieceType type;
	PieceColor color;
	int first_move;
} Piece;

typedef struct
{
	Piece *piece;
	int valid_move;
	int check_move;
	int castle;
	// 0 if no, 1 if white en passant, 2 if black en passant
    int en_passant; 
} Location;

// Location information
typedef struct
{
	int column;
	int row;
} Coordinates;

typedef enum current_player
{
    PLAYER1,
    PLAYER2,
} CurrentPlayer;

// Checks location provided as argument, return value indicates status of location
int CheckLocation(Location *location, PieceColor player_color);
// The following functions are called by CalculateMoves based on piece type
int PawnMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check, CurrentPlayer player);
int KnightMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check);
int BishopMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check);
int RookMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check);
int QueenMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check);
int KingMove(Location *gameboard[][BOARD_SIZE], Coordinates coords, int for_check);
// General function for calculating castling move
int CheckCastling(Location *gameboard[][BOARD_SIZE], Coordinates coords);
// Checks if pawn can make en passant move
int CheckEnPassant(Location *gameboard[][BOARD_SIZE], Coordinates coords);

#endif
