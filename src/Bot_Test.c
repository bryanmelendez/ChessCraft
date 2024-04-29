#include "Board.h"
#include "Piece.h"
#include "Bot.h"
#include "GameLogic.h"

int main()
{
    // BRYANS TESTS
    Game game;
    Location *gameboard[BOARD_SIZE][BOARD_SIZE];
    InitializeGameboard(gameboard, 1);
    // int move_count = 0;
    // Coordinates coord = {4,0};
    // Coordinates new_coord = {2,0};
    // gameboard[3][3]->piece = (Piece*)malloc(sizeof(Piece));
    // gameboard[coord.column][coord.row]->piece->color = WHITE;
    // gameboard[coord.column][coord.row]->piece->type = QUEEN;

    Bot bot1 = {.color = WHITE, .difficulty = EASY};
    Bot bot2 = {.color = BLACK, .difficulty = EASY};
    system("clear");
    PrintBoard(gameboard);

    for (int i = 0; i < 30; i++)
    {
        printf("Press Enter to continue...\n");
        getchar();

        GetBotMove(&bot1, gameboard, );
        system("clear");

        printf("Bot 1 move\n");
        printf("start\tCol: %d, Row: %d\n", bot1.start_location.column, bot1.start_location.row);
        printf("end\tCol: %d, Row: %d\n", bot1.end_location.column, bot1.end_location.row);

        MovePiece(gameboard, bot1.start_location, bot1.end_location, &game);
        PrintBoard(gameboard);

        printf("Press Enter to continue...\n");
        getchar();

        GetBotMove(&bot2, gameboard);
        system("clear");

        printf("Bot 2 move\n");
        printf("start\tCol: %d, Row: %d\n", bot2.start_location.column, bot2.start_location.row);
        printf("end\tCol: %d, Row: %d\n", bot2.end_location.column, bot2.end_location.row);

        MovePiece(gameboard, bot2.start_location, bot2.end_location, &game);

        PrintBoard(gameboard);
    }

    // int color, type, valid;
    // for (int row = 0; row < 8; row++) {
    //     for (int col= 0; col < 8; col++) {
    //         color = GetPieceColor(gameboard, col, row);
    //         type = GetPieceType(gameboard, col, row);
    //         valid = gameboard[col][row]->valid_move;
    //         printf("%d, %d: %c%c Location: %p Valid Move: %d\n", col, row, color, type, gameboard[col][row], valid);
    //     }
    // }

    return 0;
}
