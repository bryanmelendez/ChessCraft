// This is the source file for all the functions needed in the Game Logic
#include "GameLogic.h"
#include "Board.h"
#include "Log.h"
#include "Piece.h"
#include <assert.h>
#include <string.h>

// You can pass in either the game->gameboard or a copy of it
int CalculateMoves(Game *game, Location *gameboard[BOARD_SIZE][BOARD_SIZE], Coordinates coords, int for_check)
{
    Location *selected_location = gameboard[coords.column][coords.row];
    // stores return value from functions
    int move_count;

    if (!for_check)
    {
        ClearEnPassant(game);
    }

    if (!selected_location->piece)
    {
        // printf("Empty location: %d,%d\n", coords.column, coords.row);
        return -1;
    }

    switch (selected_location->piece->type)
    {
    case PAWN:
        move_count = PawnMove(gameboard, coords, for_check, game->player);
        break;
    case KNIGHT:
        move_count = KnightMove(gameboard, coords, for_check);
        break;
    case BISHOP:
        move_count = BishopMove(gameboard, coords, for_check);
        break;
    case ROOK:
        move_count = RookMove(gameboard, coords, for_check);
        break;
    case QUEEN:
        move_count = QueenMove(gameboard, coords, for_check);
        break;
    case KING:
        move_count = KingMove(gameboard, coords, for_check);
        break;
    default:
        return -1; // -1 when error occurs
    }

    // remove all invalid moves that cause check
    // only executes filter if board is the official game board
    if (game->gameboard == gameboard && move_count > 0)
    {
        // printf("gameboard %p\n", gameboard);
        move_count -= FilterMoves(game, gameboard, coords);
//        printf("move count %d\n", move_count);
    }

    return move_count;
}

// Filters out moves based on check
// Return value is number of moves that are removed
int FilterMoves(Game *game, Location *gameboard[BOARD_SIZE][BOARD_SIZE], Coordinates coords)
{
   // printf("filtering moves\n");

    Location *gameboard_copy[BOARD_SIZE][BOARD_SIZE];
    CopyGameBoard(game->gameboard, gameboard_copy);
    Coordinates new_coords;
    // negative move count
    int move_count = 0;
    
    // when check is not set
    if (game->check == 0)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                new_coords.column = x;
                new_coords.row = y;

                if (game->gameboard[x][y]->valid_move)
                {
                    if (game->gameboard[x][y]->castle)
                    {
     //                   printf("checking castle\n");
                        // if king is currently in check
                        Check(game, gameboard_copy, 1);

                        if (game->check)
                        {
                            printf("King is in check, cannot castle\n");
                            game->check = 0;
                            game->gameboard[x][y]->valid_move = 0;
                            continue;
                        }

                        // Right side castle
                        if (new_coords.column == 6)
                        {
                            // check intermediate move
                            gameboard_copy[new_coords.column - 1][new_coords.row]->piece = gameboard_copy[new_coords.column][new_coords.row]->piece;

                            gameboard_copy[new_coords.column][new_coords.row]->piece = NULL;
                            Check(game, gameboard_copy, 1);

                            if (game->check)
                            {
                                printf("Intermediate move puts king check, cannot castle\n");
                                game->check = 0;
                                game->gameboard[x][y]->valid_move = 0;
                                continue;
                            }

                            // check final move
                            gameboard_copy[new_coords.column][new_coords.row]->piece = gameboard_copy[new_coords.column - 1][new_coords.row]->piece;

                            gameboard_copy[new_coords.column - 1][new_coords.row]->piece = NULL;
                            Check(game, gameboard_copy, 1);

                            if (game->check)
                            {
                                printf("Final move puts king check, cannot castle\n");
                                game->check = 0;
                                game->gameboard[x][y]->valid_move = 0;
                                continue;
                            }
                        }

                        // Left side castle
                        if (new_coords.column == 2)
                        {
                            // check intermediate move
                            gameboard_copy[new_coords.column + 1][new_coords.row]->piece = gameboard_copy[new_coords.column][new_coords.row]->piece;

                            gameboard_copy[new_coords.column][new_coords.row]->piece = NULL;
                            Check(game, gameboard_copy, 1);

                            if (game->check)
                            {
                                printf("Intermediate move puts king check, cannot castle\n");
                                game->check = 0;
                                game->gameboard[x][y]->valid_move = 0;
                                continue;
                            }

                            // check final move
                            gameboard_copy[new_coords.column][new_coords.row]->piece = gameboard_copy[new_coords.column + 1][new_coords.row]->piece;

                            gameboard_copy[new_coords.column + 1][new_coords.row]->piece = NULL;
                            Check(game, gameboard_copy, 1);

                            if (game->check)
                            {
                                printf("Final move puts king check, cannot castle\n");
                                game->check = 0;
                                game->gameboard[x][y]->valid_move = 0;
                                continue;
                            }
                        }
                    }
                    else
                    {
 //                       printf("checking valid move location: %d, %d\n", x, y);
                        //gameboard_copy[new_coords.column][new_coords.column]->piece 
                        //    = gameboard_copy[coords.column][coords.row]->piece;
                        //gameboard_copy[coords.column][coords.row]->piece = NULL;
                        MovePiece(gameboard_copy, coords, new_coords, game);
       //                 printf("moving piece\n");
                        Check(game, gameboard_copy, 1);
   //                     printf("check %d\n", game->check);

                        if (game->check)
                        {
                            printf("Invalid move, puts king in check\n");
                            game->gameboard[x][y]->valid_move = 0;
                            move_count++;
                            // undo check
                            game->check = 0;
                        }

                        // Move piece back to original location
                        gameboard_copy[coords.column][coords.row]->piece = gameboard_copy[new_coords.column][new_coords.row]->piece;
                        gameboard_copy[new_coords.column][new_coords.row]->piece = NULL;

                        // printf("undo piece move\n");
                        UndoMove(game->game_log);
                    }
                }
            }
        }
    }
    // when check is set
    else if (game->check == 1)
    {
     //   printf("filter: game is in check\n");
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                new_coords.column = x;
                new_coords.row = y;

                if (game->gameboard[x][y]->valid_move)
                {
                    MovePiece(gameboard_copy, coords, new_coords, game);

                    Check(game, gameboard_copy, 1);

                    if (game->check)
                    {
                        printf("Invalid move, does not remove check\n");
                        game->gameboard[x][y]->valid_move = 0;
                        move_count++;
                    }
                    // if it is 0 then it is a valid move
                    else if (game->check == 0)
                    {
                        // reset check
       //                 printf("resetting check\n");
                        game->check = 1;
                    }

                    // Move piece back to original location
                    gameboard_copy[coords.column][coords.row]->piece = gameboard_copy[new_coords.column][new_coords.row]->piece;
                    gameboard_copy[new_coords.column][new_coords.row]->piece = NULL;

                    // undo the move from the log list
                    UndoMove(game->game_log);
                }
            }
        }
    }

    DeleteBoard(gameboard_copy);

    return move_count;
}

void CopyGameBoard(Location *old_board[BOARD_SIZE][BOARD_SIZE], Location *new_board[BOARD_SIZE][BOARD_SIZE])
{
    // printf("Copying game board!\n");
    assert(old_board);
    assert(new_board);

    Location *location_copy = NULL;
    Piece *piece_copy = NULL;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            location_copy = (Location *)malloc(sizeof(Location));
            piece_copy = (Piece *)malloc(sizeof(Piece));
            assert(location_copy);
            // printf("Location copy: %p\n", location_copy);

            // printf("Piece copy: %p\n", piece_copy);

            location_copy->castle = old_board[i][j]->castle;
            location_copy->check_move = old_board[i][j]->check_move;
            location_copy->en_passant = old_board[i][j]->en_passant;
            location_copy->valid_move = old_board[i][j]->valid_move;

            new_board[i][j] = location_copy;
            assert(new_board[i][j]);

            if (old_board[i][j]->piece)
            {

                assert(piece_copy);
                piece_copy->color = old_board[i][j]->piece->color;
                piece_copy->type = old_board[i][j]->piece->type;
                piece_copy->first_move = old_board[i][j]->piece->first_move;

                new_board[i][j]->piece = piece_copy;
                assert(new_board[i][j]->piece);
            }
            else
            {
                new_board[i][j]->piece = NULL;
            }

            // printf("seg fault check\n");
        }
    }
}

// This function will take the current coordinate of a piece chosen by the user and move to a new place given the move is valid.
int MovePiece(Location *game_board[BOARD_SIZE][BOARD_SIZE], Coordinates start_place, Coordinates end_place, Game *game)
{
    if (!game_board[start_place.column][start_place.row])
    {
        printf("The end location does not exist!\n");
        return -1;
    }

    if (!game_board[end_place.column][end_place.row]->valid_move)
    {
        printf("Invalid Move\n");
        return -1;
    }
    else
    {
        char *log_text = LogText(start_place, end_place);
        AddMove(game->game_log, log_text);
        free(log_text);
        // Stores the original piece in a temproary pointer
        Piece *moved_piece = game_board[start_place.column][start_place.row]->piece;
        if (!moved_piece->first_move)
        {
            moved_piece->first_move = 1;
            // set en passant
            if (moved_piece->type == PAWN)
            {
                if (moved_piece->color == WHITE)
                {
                    if ((end_place.row - start_place.row == 2) && (start_place.column == end_place.column))
                    {
                        // printf("setting en passant\n");
                        game_board[end_place.column][end_place.row - 1]->en_passant = 1;
                        // printf("En passant: %d\n",
                        // game_board[end_place.column][end_place.row-1]->en_passant);
                    }
                }
                else if (moved_piece->color == BLACK)
                {
                    if ((start_place.row - end_place.row == 2) && (start_place.column == end_place.column))
                    {
                        // printf("setting en passant\n");
                        game_board[end_place.column][end_place.row + 1]->en_passant = 2;
                        // printf("En passant: %d\n",
                        // game_board[end_place.column][end_place.row+1]->en_passant);
                    }
                }
            }
        }
        // check if castling move is selected
        if (game_board[end_place.column][end_place.row]->castle)
        {
            // initiate castle move
            game_board[start_place.column][start_place.row]->piece = NULL;
            Castle(game_board, moved_piece, end_place, game);
        }
        // check if en passant move is selected
        else if (game_board[end_place.column][end_place.row]->en_passant)
        {
            game_board[start_place.column][start_place.row]->piece = NULL;
            EnPassant(game_board, moved_piece, end_place);
        }
        // check if piece is capturing
        else if (game_board[end_place.column][end_place.row]->piece)
        {
            // return error if trying to take piece of same color
            if (game_board[start_place.column][start_place.row]->piece->color == game_board[end_place.column][end_place.row]->piece->color)
            {
                printf("Error: taking piece of same color\n");
                return -1;
            }

            game_board[start_place.column][start_place.row]->piece = NULL;
            CapturePiece(game_board, moved_piece, end_place);
        }
        // normal move
        else
        {
            if ((moved_piece->type == PAWN) && ((end_place.row == 7) || (end_place.row == 0)))
            {
                int new_piece = 0;
                while (new_piece == 0)
                {
                    printf("What piece should your pawn be promoted to? 1 for Knight, 2 for Bishop, 3 for Rook, and 4 for queen: ");
                    scanf("%d", &new_piece);
                    moved_piece->type = (new_piece == 1) ? KNIGHT : ((new_piece == 2) ? BISHOP : ((new_piece == 3) ? ROOK : (new_piece == 4 ? QUEEN : 0)));
                }
            }
            // Removes the piece from the old location and places it in the new one
            game_board[start_place.column][start_place.row]->piece = NULL;
            game_board[end_place.column][end_place.row]->piece = moved_piece;
        }
    }
    return 0;
}

void CapturePiece(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece *moved_piece, Coordinates end_place)
{
    // delete the piece being captured
    DeletePiece(game_board[end_place.column][end_place.row]->piece);

    // assign new piece to location
    game_board[end_place.column][end_place.row]->piece = moved_piece;
}

// This function will make all valid and check moves of the board 0
void ClearBoard(Location *gameboard[BOARD_SIZE][BOARD_SIZE])
{
    for (int COL = 0; COL < 8; COL++)
    {
        for (int ROW = 0; ROW < 8; ROW++)
        {
            gameboard[COL][ROW]->valid_move = 0;
            gameboard[COL][ROW]->check_move = 0;
        }
    }
}
// This function checks to see if the king is in check passing the game, the recent move made, and the color of the most recent user. If it is, sets the game check to 1
int Check(Game *game, Location *gameboard[BOARD_SIZE][BOARD_SIZE], int same_side)
{
    Location *gameboard_copy[BOARD_SIZE][BOARD_SIZE];
    CopyGameBoard(gameboard, gameboard_copy);

    //printf("OLD BOARD\n");
    //PrintBoard(game->gameboard);
    //printf("\n\n\nNEW BOARD\n");
    //PrintBoard(gameboard_copy);

    // Initalized variable to hold the king and the piece moved recently to check
    Coordinates king_location;
    Coordinates temp_coords;
    // Cleans the original check
    ClearBoard(gameboard_copy);
    // Checks the entire board to find the king
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            // Checks if the piece is a king and the opposite color
            if (CheckLocation(gameboard_copy[x][y], game->color) == (same_side + 1))
            {
                if (gameboard_copy[x][y]->piece->type == KING)
                {
                    king_location.column = x;
                    king_location.row = y;
                }
            }
        }
    }
    for (int COL = 0; COL < 8; COL++)
    {
        for (int ROW = 0; ROW < 8; ROW++)
        {
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (2 - same_side))
            {
                temp_coords.column = COL;
                temp_coords.row = ROW;
                CalculateMoves(game, gameboard_copy, temp_coords, 1);
            }
        }
    }
    if (gameboard_copy[king_location.column][king_location.row]->check_move)
    {
        game->check = 1;
        printf("Game is in check!\n");
    }
    else
    {
        game->check = 0;
    }

    // printf("OLD BOARD\n");
    // PrintBoard(game->gameboard);
    // printf("\n\n\nNEW BOARD\n");
    // PrintBoard(gameboard_copy);

    DeleteBoard(gameboard_copy);
    return 0;
}

int CheckMate(Game *game, Location *gameboard[BOARD_SIZE][BOARD_SIZE], int same_side)
{
    Location *gameboard_copy[BOARD_SIZE][BOARD_SIZE];
    CopyGameBoard(game->gameboard, gameboard_copy);

    if (!game->check)
    {
        printf("King is not in Check\n");
        return -1;
    }
    // This returns how many possible ways out of checkmate the king can move
    int move_count = 0;
    // Initalized variable to hold the king and the piece moved recently to check
    Coordinates king_coord;
    Coordinates opp_piece;
    Coordinates checking_piece;
    Coordinates temp_coords;
    Coordinates new_location;
    Piece *save_piece;
    Piece *moved_piece;

    // Checks the entire board to find the king
    for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
    {
        for (int COL = 0; COL < BOARD_SIZE; COL++)
        {
            // Checks if the piece is a king and the opposite color
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (same_side + 1))
            {
                if (gameboard_copy[COL][ROW]->piece->type == KING)
                {
                    king_coord.column = COL;
                    king_coord.row = ROW;
 //                   printf("king here: %d, %d", king_coord.column, king_coord.row);
                }
            }
        }
    }
    CalculateMoves(game, gameboard_copy, king_coord, 0);
    for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
    {
        for (int COL = 0; COL < BOARD_SIZE; COL++)
        {
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (2 - same_side))
            {
                temp_coords.column = COL;
                temp_coords.row = ROW;
                CalculateMoves(game, gameboard_copy, temp_coords, 1);
            }
        }
    }
    for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
    {
        for (int COL = 0; COL < BOARD_SIZE; COL++)
        {
            // Checks if the piece is a king and the opposite color
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (same_side + 1))
            {
                if (gameboard_copy[COL][ROW]->piece->type == KING)
                {
                    king_coord.column = COL;
                    king_coord.row = ROW;
   //                 printf("king here: %d, %d\n", king_coord.column, king_coord.row);
                }
            }
        }
    }
    // This checks if the king can move anywhere
    for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
    {
        for (int COL = 0; COL < BOARD_SIZE; COL++)
        {
            if ((gameboard_copy[COL][ROW]->valid_move) && (!gameboard_copy[COL][ROW]->check_move))
            {
                printf("The King can move\n");
                move_count++;
            }
        }
    }
    ClearBoard(gameboard_copy);

    // This checks if any of the opponents pieces can capture the pieces causing check
    for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
    {
        for (int COL = 0; COL < BOARD_SIZE; COL++)
        {
            // Looks to find one of the opponents pieces
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (same_side + 1))
            {
                opp_piece.column = COL;
                opp_piece.row = ROW;
                CalculateMoves(game, gameboard_copy, opp_piece, 0);
                // This checks if the opponent can capture a piece of the current player
                for (int x = 0; x < BOARD_SIZE; x++)
                {
                    for (int y = 0; y < BOARD_SIZE; y++)
                    {
                        if (gameboard_copy[x][y]->valid_move && (CheckLocation(gameboard_copy[x][y], game->color) == (2 - same_side)))
                        {
                            checking_piece.column = x;
                            checking_piece.row = y;
                            CalculateMoves(game, gameboard_copy, checking_piece, 1);
                            // This sees if the capturable piece puts the king in check
                            if (gameboard_copy[king_coord.column][king_coord.row]->check_move)
                            {
                                // game->gameboard[checking_piece.column][checking_piece.row]->valid_move = 1;
 //                               printf("Can capture a piece\n");
                                move_count++;
                            }
                        }
                    }
                }
            }
        }
    }
    ClearBoard(gameboard_copy);
    // This checks if one of the opponents pieces can block check
    //
    for (int COL = 0; COL < BOARD_SIZE; COL++)
    {
        for (int ROW = 0; ROW < BOARD_SIZE; ROW++)
        {
            // Finds a piece of the opposite color and calculates its moves
            if (CheckLocation(gameboard_copy[COL][ROW], game->color) == (same_side + 1))
            {
                opp_piece.column = COL;
                opp_piece.row = ROW;
                CalculateMoves(game, gameboard_copy, opp_piece, 0);
                // Checks if when that piece is moved, if it will stop check
                for (int x = 0; x < BOARD_SIZE; x++)
                {
                    for (int y = 0; y < BOARD_SIZE; y++)
                    {
                        // If that move is valid than it moves the piece there
                        if (gameboard_copy[x][y]->valid_move)
                        {
                            new_location.column = x;
                            new_location.row = y;
                            save_piece = gameboard_copy[new_location.column][new_location.row]->piece;
                            moved_piece = gameboard_copy[opp_piece.column][opp_piece.row]->piece;
                            gameboard_copy[new_location.column][new_location.row]->piece = moved_piece;
                            gameboard_copy[opp_piece.column][opp_piece.row]->piece = NULL;
                            // Calculates check of all the current piece
                            for (int B = 0; B < BOARD_SIZE; B++)
                            {
                                for (int A = 0; A < BOARD_SIZE; A++)
                                {
                                    if (CheckLocation(gameboard_copy[A][B], game->color) == (2 - same_side))
                                    {
                                        temp_coords.column = A;
                                        temp_coords.row = B;
                                        CalculateMoves(game, gameboard_copy, temp_coords, 1);
                                    }
                                }
                            }
                            // PrintBoard(game->gameboard);
                            // If the king is no longer in check than the move is valid
                            if (!gameboard_copy[king_coord.column][king_coord.row]->check_move)
                            {
     //                           printf("Can block with a piece from %d, %d and move to %d, %d\n", COL, ROW, x, y);
                                move_count++;
                            }
                            // Moves piece to original location
                            gameboard_copy[opp_piece.column][opp_piece.row]->piece = gameboard_copy[new_location.column][new_location.row]->piece;
                            gameboard_copy[new_location.column][new_location.row]->piece = save_piece;
                        }
                    }
                }
            }
            ClearBoard(gameboard_copy);
        }
    }
 //   printf("move count: %d\n", move_count);
    // Need to check if moving the piece that captures another piece will put the king in check
    if (move_count == 0)
    {
        game->mate = 1;
    }

    DeleteBoard(gameboard_copy);

    return move_count;
}

// this function allows the castling move by a user if move is valid
int Castle(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece *king, Coordinates new_king, Game *game)
{
    /*
       moving the pieces for castling: (make corresponding function in GameLogic.c)

        - if new location->castling = true
                (this condition implies that the king and rook are in their original
                locations, this means that coordinates for the castling move can
                be hardcoded)

        flow:
        - user inputs selection
        - calculate moves is called
            - calculates castling moves
            ** Castling moves need to be checked
                    - this requires upper level game logic that
                        cannot be accessed by the piece functions
        - board is printed showing possible moves
        - move is inputted
        - move piece is called
        - updated board is outputted


        possible king moves (columns): 2,6 for actual castle /
                                        also 0,7 for chess.com like castling
        cross over locations: 3, 5

    */
 //   printf("Starting castling move\n");

    // right side castle
    if (new_king.column == 6)
    {
        game_board[new_king.column][new_king.row]->piece = king;
        // moves rook to new location
        game_board[new_king.column - 1][new_king.row]->piece = game_board[7][new_king.row]->piece;
        game_board[7][new_king.row]->piece = NULL;
    }
    // left side castle
    else if (new_king.column == 2)
    {
        game_board[new_king.column][new_king.row]->piece = king;
        // moves rook to new location
        game_board[new_king.column + 1][new_king.row]->piece = game_board[0][new_king.row]->piece;
        game_board[0][new_king.row]->piece = NULL;
    }
    return 0;
}
// This function allows the EnPassant move by a user if move is valid
int EnPassant(Location *game_board[BOARD_SIZE][BOARD_SIZE], Piece *pawn, Coordinates end_place)
{
    // if player is white, black pawn is endplace - 1
    // if player is black, white pawn is endplace + 1

    // find the opponents pawn based on color and delete it
    // then move player's pawn to en passant location

    Piece *opponent_pawn = NULL;

    // if trying to take black pawn
    if (pawn->color == WHITE && game_board[end_place.column][end_place.row - 1]->piece)
    {
        opponent_pawn = game_board[end_place.column][end_place.row - 1]->piece;
        if (opponent_pawn->color == BLACK)
        {
            DeletePiece(opponent_pawn);
        }
        else
        {
            printf("En passant error!\n");
            return -1;
        }

        game_board[end_place.column][end_place.row]->piece = pawn;
    }
    // if trying to take white pawn
    else if (pawn->color == BLACK && game_board[end_place.column][end_place.row + 1]->piece)
    {
        opponent_pawn = game_board[end_place.column][end_place.row + 1]->piece;
        if (opponent_pawn->color == WHITE)
        {
            DeletePiece(opponent_pawn);
        }
        else
        {
            printf("En passant error!\n");
            return -1;
        }

        game_board[end_place.column][end_place.row]->piece = pawn;
    }

    return 0;
}

int ClearEnPassant(Game *game)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (game->gameboard[i][j]->en_passant == 1 && game->color == WHITE)
            {
 //               printf("clearing en passant\n");
                game->gameboard[i][j]->en_passant = 0;
            }
            else if (game->gameboard[i][j]->en_passant == 2 && game->color == BLACK)
            {
   //             printf("clearing en passant\n");
                game->gameboard[i][j]->en_passant = 0;
            }
        }
    }

    return 0;
}
