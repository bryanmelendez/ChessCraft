#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"
#include "Game.h"
#include "Menu.h"
#include "Log.h"
#include "GameLogic.h"

int main()
{
    // BRYANS TESTS
    /*
        int move_count = 0;
        Coordinates coord = {4,0};
        Coordinates new_coord = {2,0};
        // gameboard[3][3]->piece = (Piece*)malloc(sizeof(Piece));
        // gameboard[coord.column][coord.row]->piece->color = WHITE;
        // gameboard[coord.column][coord.row]->piece->type = QUEEN;

        // empty board to test castling
        gameboard[1][0]->piece = NULL;
        gameboard[2][0]->piece = NULL;
        gameboard[3][0]->piece = NULL;
        gameboard[5][0]->piece = NULL;
        gameboard[6][0]->piece = NULL;

        PrintBoard(gameboard);

        printf("Move Count: %d\n", CalculateMoves(gameboard,coord));

        MovePiece(gameboard, coord, new_coord);

        PrintBoard(gameboard);
        // int color, type, valid;
        // for (int row = 0; row < 8; row++) {
        //     for (int col= 0; col < 8; col++) {
        //         color = GetPieceColor(gameboard, col, row);
        //         type = GetPieceType(gameboard, col, row);
        //         valid = gameboard[col][row]->valid_move;
        //         printf("%d, %d: %c%c Location: %p Valid Move: %d\n", col, row, color, type, gameboard[col][row], valid);
        //     }
        // }
 }   */

    // DAVID'S TESTS

    int old_coords_col[] = {5, 4, 6, 3} /*4, 3, 4, 3, 4, 3, 4, 3, 5};// Testing check:4, 3, 0, 0, 5}*/; // 4, 6, 3, 4, 5, 4};
    int old_coords_row[] = {1, 6, 1, 7};                                                                /*1, 6, 3, 4, 4, 3, 5, 2, 6};// Testing check: 1, 6, 1, 6, 0}; */
    int new_coords_col[] = {5, 4, 6, 7};                                                                /*4, 3, 4, 3, 4, 3, 5, 4, 6};// Testing check: 4, 3, 0, 0, 1};  */
    int new_coords_row[] = {3, 4, 3, 3};                                                                /*3, 4, 4, 3, 5, 2, 6, 1, 7};// Testing check: 3, 4, 3, 4, 4}; */

    Game game;
    LogList *log_list = NewLogList();
    game.color = 0;
    game.game_log = log_list;
    InitializeGameboard(game.gameboard, 1);
    // Board and Variable Setup
    Coordinates user_start_coordinates;
    Coordinates user_end_coordinates;
    game.check = 0;
    game.player = PLAYER1;
    game.mate = 0;

    // While loop to handle player turns
    for (int i = 0; i < 4; i++)
    {
        PrintBoard(game.gameboard);
        printf("It is Player %d's Turn.\n", game.player + 1);
        user_start_coordinates.column = old_coords_col[i];
        user_start_coordinates.row = old_coords_row[i];
        CalculateMoves(&game, game.gameboard, user_start_coordinates, 0);
        user_end_coordinates.column = new_coords_col[i];
        user_end_coordinates.row = new_coords_row[i];
        PrintBoard(game.gameboard);
        MovePiece(game.gameboard, user_start_coordinates, user_end_coordinates, &game);
        ClearBoard(game.gameboard);
        Check(&game, game.gameboard, 0);
        if (game.check)
        {
            // printf("King is in Check\n");
            CheckMate(&game, game.gameboard, 0);
            // game.mate = 1;
            if (game.mate)
            {
                printf("Game Over\n");
                // Exit the game
            }
        }
        // Swap Players
        switch (game.player)
        {
        case PLAYER2:
            game.player = PLAYER1;
            break;

        case PLAYER1:
            game.player = PLAYER2;
            break;
        }

        // Swap Colors
        switch (game.color)
        {
        case BLACK:
            game.color = WHITE;
            break;

        case WHITE:
            game.color = BLACK;
            break;
        }
    }

    PrintBoard(game.gameboard);
    exit(0);
    DeleteLogList(log_list);
    DeleteBoard(game.gameboard);
    return 0;
}
