
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"

/* sets up gameboard */
void InitializeGameboard(Location* gameboard[8][8], int color) {
	/* memory */
	for (int i = 0; i < 8; i++) {
           for (int j = 0; j < 8; j++) {
                gameboard[i][j] = (Location*)malloc(sizeof(Location));
                gameboard[i][j]->piece = (Piece*)malloc(sizeof(Piece));
                }
        }

	int w, w2, b, b2 = 0;
	if (color == 1) {
		w = 0;
		w2 = 1;
		b = 7;
		b2 = 6;

		/* black side pieces */
		for (int i = 0; i < 8; i++) {
			gameboard[i][b]->piece->type = (i == 0 || i == 7) ? ROOK : ((i == 1 || i == 6) ? KNIGHT : ((i == 2 || i == 5) ? BISHOP : (i == 3 ? QUEEN : KING)));
			gameboard[i][b]->piece->color = BLACK;
			gameboard[i][b]->piece->first_move = 0;
		}
		for (int i = 0; i < 8; i++) {	
			gameboard[i][b2]->piece->type = PAWN;
			gameboard[i][b2]->piece->color = BLACK;
			gameboard[i][b2]->piece->first_move = 0;
		} 
		/* white side pieces */
		for (int j = 0; j < 8; j++) {
					gameboard[j][w]->piece->type = (j == 0 || j == 7) ? ROOK : ((j == 1 || j == 6) ? KNIGHT : ((j == 2 || j == 5) ? BISHOP : (j == 3 ? QUEEN : KING)));
					gameboard[j][w]->piece->color = WHITE;
			gameboard[j][w]->piece->first_move = 0;
			}
			for (int j = 0; j < 8; j++) {  
			gameboard[j][w2]->piece->type = PAWN;
					gameboard[j][w2]->piece->color = WHITE;
			gameboard[j][w2]->piece->first_move = 0;
			} 
		for (int row = 2; row < 6; row++) {
			for (int col = 0; col < 8; col++) {
				gameboard[col][row]->piece = NULL;
			}
		}
	}
	else if (color == 2) {
		w = 7;
		w2 = 6;
		b = 0;
		b2 = 1;
		for (int i = 0; i < 8; i++) {
			gameboard[i][b]->piece->type = (i == 0 || i == 7) ? ROOK : ((i == 1 || i == 6) ? KNIGHT : ((i == 2 || i == 5) ? BISHOP : (i == 3 ? KING : QUEEN)));
			gameboard[i][b]->piece->color = BLACK;
			gameboard[i][b]->piece->first_move = 0;
		}
		for (int i = 0; i < 8; i++) {	
			gameboard[i][b2]->piece->type = PAWN;
			gameboard[i][b2]->piece->color = BLACK;
			gameboard[i][b2]->piece->first_move = 0;
		} 
		/* white side pieces */
		for (int j = 0; j < 8; j++) {
					gameboard[j][w]->piece->type = (j == 0 || j == 7) ? ROOK : ((j == 1 || j == 6) ? KNIGHT : ((j == 2 || j == 5) ? BISHOP : (j == 3 ? KING : QUEEN)));
					gameboard[j][w]->piece->color = WHITE;
			gameboard[j][w]->piece->first_move = 0;
			}
			for (int j = 0; j < 8; j++) {  
			gameboard[j][w2]->piece->type = PAWN;
					gameboard[j][w2]->piece->color = WHITE;
			gameboard[j][w2]->piece->first_move = 0;
			} 
		for (int row = 2; row < 6; row++) {
			for (int col = 0; col < 8; col++) {
				gameboard[col][row]->piece = NULL;
			}
		}
	}   
}

/* returns character of piece color */	
char GetPieceColor(Location* gameboard[8][8], int col, int row) {
	Piece* piece = gameboard[col][row]->piece;
	if (piece != NULL) {
		switch(piece->color) {
			case WHITE:
				return 'w';
			case BLACK:
				return 'b';
			default:
				return ' ';
		}
	}
	else {
		return ' ';
	}	
}

/* returns character of piece type */
char GetPieceType(Location* gameboard[8][8], int col, int row) {
	Piece* piece = gameboard[col][row]->piece;
	if (piece != NULL) {
		switch(piece->type) {
			case PAWN:
				return 'P';
			case KNIGHT:
				return 'N';
			case BISHOP:
				return 'B';
			case ROOK:
				return 'R';
			case QUEEN:
				return 'Q';
			case KING:
				return 'K';
			default:
				return ' ';
		}
	}
	else {
		return ' ';
	}
}

void PrintBoard(Location* gameboard[8][8]) {
	char color, type;
    /* printing board */
    printf("   +----+----+----+----+----+----+----+----+\n");
    for (int row = 7; row >= 0; row--) {
        printf(" %d ", row + 1); // prints row number
        for (int col = 0; col < 8; col++) {
            color = GetPieceColor(gameboard, col, row);
            type = GetPieceType(gameboard, col, row);
            if (gameboard[col][row]->valid_move) {
                if (gameboard[col][row]->piece == NULL) {
                    printf("|****"); }
                else {
                    printf("|*%c%c*", color, type); }
            } else {
                printf("| %c%c ", color, type);
            }
        }
        printf("|\n");
        printf("   +----+----+----+----+----+----+----+----+\n");
    }
    printf("     a    b    c    d    e    f    g    h\n");
}

void DeleteBoard(Location* gameboard[8][8]) {
    /* freeing memory */
    assert(gameboard);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            assert(gameboard[i][j]);
            // if location has a piece, delete it
            if (gameboard[i][j]->piece) {
                DeletePiece(gameboard[i][j]->piece);
                gameboard[i][j]->piece = NULL;
            }
    
            // free each location
            free(gameboard[i][j]);
            gameboard[i][j] = NULL;
        }
    }
}

void DeletePiece(Piece* piece)
{
    // delete the piece
    assert(piece);
    free(piece); 
}
