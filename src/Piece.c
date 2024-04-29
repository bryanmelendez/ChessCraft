#include "Piece.h"

// Helper function for all move calculations (not in header file)
// Returns -1 if error  
// Returns 0 if empty location
// Returns 1 if contains opposite color piece
// Returns 2 if contains same color piece
int CheckLocation(Location* location, PieceColor player_color) {
    if (location->piece == NULL) {
        return 0;
    }
    else if (location->piece) {
        if (location->piece->color != player_color) {
            return 1;
        }
        else if (location->piece->color == player_color) {
            return 2;
        }
    }
     
    // only return -1 if errors
    return -1;
}


int PawnMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check, CurrentPlayer player) {
    Location* selected = gameboard[coords.column][coords.row];
    Location* current = NULL;
    int side_sign = (player == PLAYER2) ? -1 : 1;
    //This sign chooses to move up or down rows as pawns can only 
    // move forward but forward is depending on the side the pieces start
    // int side_sign = 1;
    // if (current->piece->color == BLACK) {
    //     side_sign = -1;
    // }
    Coordinates up_two = {.column = coords.column,
                            .row = coords.row+(2*side_sign)};
    Coordinates up_one = {.column = coords.column, 
                            .row = coords.row+side_sign};
    // Diagonal coordinates as if current color is at the bottom of the board
    Coordinates right_diag = {.column = coords.column+side_sign, 
                            .row = coords.row+side_sign};
    Coordinates left_diag = {.column = coords.column-side_sign,
                            .row = coords.row+side_sign};
    int move_count = 0;
    int check;

    // Check move 2
    if (selected->piece->first_move == 0) {
        current = gameboard[up_one.column][up_one.row];
        check = CheckLocation(current, selected->piece->color);        
        if (check == 0) {
            current = gameboard[up_two.column][up_two.row];
            check = CheckLocation(current, selected->piece->color);        

            if (check == 0) {
                if (for_check) {
                    current -> check_move = 1;
                } else {
                    current->valid_move = 1; 
                }
                move_count++;
            }
            else if (check == -1) {
                printf("Move Pawn Error\n");
                return -1;
            }
        }
    }
   
    // check move 1
    if ((up_one.column < BOARD_SIZE) && up_two.row < BOARD_SIZE) {
        current = gameboard[up_one.column][up_one.row];
        check = CheckLocation(current, selected->piece->color);        

        if (check == 0) {
            if (for_check) {
                    current -> check_move = 1;
                } else {
                    current->valid_move = 1; 
                }
            move_count++;
        }
        else if (check == -1) {
            printf("Move Pawn Error\n");
            return -1;
        }
    }

    // check right diagonal
    if (right_diag.column >= 0 && right_diag.column < BOARD_SIZE
         && right_diag.row >= 0 && left_diag.row < BOARD_SIZE) {
       current = gameboard[right_diag.column][right_diag.row];
       check =  CheckLocation(current, selected->piece->color);

       if (check == 1) {
           if (for_check) {
               current -> check_move = 1;
           } else {
               current->valid_move = 1; 
           }
           move_count++;
       }
       else if (check == -1) {
           printf("Move Pawn Error\n");
           return -1;
       }

       // check right en passant
       CheckEnPassant(gameboard, right_diag); 
    }

    // check left diagonal
    if (left_diag.column >= 0 && left_diag.column < BOARD_SIZE
         && left_diag.row >= 0 && left_diag.row < BOARD_SIZE) {
       current = gameboard[left_diag.column][left_diag.row];
       check = CheckLocation(current, selected->piece->color);
       
       if (check == 1) {
           if (for_check) {
                    current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
           move_count++;
       }
       else if (check == -1) {
           printf("Move Pawn Error\n");
           return -1;
       }

       // check left en passant
       CheckEnPassant(gameboard, left_diag);
    }
   
    return move_count;
}

int KnightMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check){
    Location* selected = gameboard[coords.column][coords.row];
    Location* current = NULL;
    // All possible moves of a knight hardcoded
    int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int x;
    int y;
    int check;
    int move_count = 0;

    // Loops through all possible moves
    for (int i = 0; i < 8; i++) {
        x = coords.row + X[i]; 
        y = coords.column + Y[i];
        //Checks to see if the calculated place is on the board
        if ((y < 0) || (y > 7) || (x < 0) || (x > 7)) {
            continue;
        }
        current = gameboard[y][x];
        check = CheckLocation(current, selected->piece->color);

        switch (check) {
            case 0:  if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                     move_count++;
                     break;
            case 1:  if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                     move_count++;
                     break;
            case 2: if (for_check) {
                        current -> check_move = 0;
                    } else {
                        current->valid_move = 0; 
                    }
                     break;
            case -1: printf("Move Knight Error\n");
                     return -1;
        }
    }

    return move_count;
}

int BishopMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check)
{
    Location* selected = gameboard[coords.column][coords.row];
    Location* current = NULL;
    int move_count = 0;
    int i = 1;
    int stop_checking_up_right = 0;
    int stop_checking_down_right = 0;
    int stop_checking_up_left = 0;
    int stop_checking_down_left = 0;
    Coordinates up_right;
    Coordinates down_right;
    Coordinates up_left;
    Coordinates down_left;
    int check;

/*  || (!stop_checking_down_right) || (!stop_checking_down_left) */
    while ((!stop_checking_up_right) || (!stop_checking_up_left)
            || (!stop_checking_down_right) || (!stop_checking_down_left)) {
        // check up right
        if (stop_checking_up_right == 0) {
            up_right.column = coords.column + i;
            up_right.row = coords.row + i;

            if ((up_right.column >= BOARD_SIZE) || (up_right.row >= BOARD_SIZE)) {
                stop_checking_up_right = 1;
            }
            else {
                current = gameboard[up_right.column][up_right.row];
                check = CheckLocation(current, selected->piece->color);
            }

            if (stop_checking_up_right == 0) {
                if (check == 0) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    move_count++;
                }
                else if (check == 1) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    stop_checking_up_right = 1;
                    move_count++;
                }
                else if (check == 2) {
                    current->valid_move = 0;
                    stop_checking_up_right = 1;
                }
                else if (check == -1) {
                    printf("Move Bishop Error\n");
                    return -1;
                }
            }
        }

        // check up left 
        if (stop_checking_up_left == 0) {
            up_left.column = coords.column - i;
            up_left.row = coords.row + i;

            if ((up_left.column < 0) || (up_left.row >= BOARD_SIZE)) {
                stop_checking_up_left = 1;
            }
            else {
                current = gameboard[up_left.column][up_left.row];
                check = CheckLocation(current, selected->piece->color);
            }

            if (stop_checking_up_left == 0) {
                if (check == 0) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    move_count++;
                }
                else if (check == 1) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    stop_checking_up_left = 1;
                    move_count++;
                }
                else if (check == 2) {
                    current->valid_move = 0;
                    stop_checking_up_left = 1;
                }
                else if (check == -1) {
                    printf("Move Bishop Error\n");
                    return -1;
                }
            }
        }

        // check down right
        if (stop_checking_down_right == 0) {
            down_right.column = coords.column + i;
            down_right.row = coords.row - i;

            if ((down_right.column >= BOARD_SIZE) || (down_right.row < 0)) {
                stop_checking_down_right = 1;
            }
            else {
                current = gameboard[down_right.column][down_right.row];
                check = CheckLocation(current, selected->piece->color);
            }

            if (stop_checking_down_right == 0) {
                if (check == 0) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    move_count++;
                }
                else if (check == 1) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    stop_checking_down_right = 1;
                    move_count++;
                }
                else if (check == 2) {
                    current->valid_move = 0;
                    stop_checking_down_right = 1;
                }
                else if (check == -1) {
                    printf("Move Bishop Error\n");
                    return -1;
                }
            }
        }

        // check down left 
        if (stop_checking_down_left == 0) {
            down_left.column = coords.column - i;
            down_left.row = coords.row - i;

            if ((down_left.column < 0) || (down_left.row < 0)) {
                stop_checking_down_left = 1;
            }
            else {
                current = gameboard[down_left.column][down_left.row];
                check = CheckLocation(current, selected->piece->color);
            }

            if (stop_checking_down_left == 0) {
                if (check == 0) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    move_count++;
                }
                else if (check == 1) {
                    if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                    stop_checking_down_left = 1;
                    move_count++;
                }
                else if (check == 2) {
                    current->valid_move = 0;
                    stop_checking_down_left = 1;
                }
                else if (check == -1) {
                    printf("Move Bishop Error\n");
                    return -1;
                }
            }
        }
        i++;
    }

    return move_count;
}

int RookMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check)
{
    Location* current = gameboard[coords.column][coords.row];
    Location* selected = gameboard[coords.column][coords.row];
    int move_count = 0;
    int check;
    
    // Check up 
    for (int i = coords.row+1; i < BOARD_SIZE; i++) {
        assert(i < BOARD_SIZE);
        current = gameboard[coords.column][i];
        check = CheckLocation(current, selected->piece->color);
       
        if (check == 0) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
        }
        else if (check == 1) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
            // break because no more moves beyond this point
            break;
        }
        else if (check == 2) {
            current->valid_move = 0;
            // break because no more moves beyond this point
            break;
        }
        else if (check == -1) {
            printf("Move Rook Error\n");
            return -1;
        }

        move_count++;
    }

    // Check down
    for (int i = coords.row-1; i >= 0; i--) {
        assert(i < BOARD_SIZE);
        current = gameboard[coords.column][i];
        check = CheckLocation(current, selected->piece->color);
       
        if (check == 0) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
        }
        else if (check == 1) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
            // break because no more moves beyond this point
            break;
        }
        else if (check == 2) {
            current->valid_move = 0;
            // break because no more moves beyond this point
            break;
        }
        else if (check == -1) {
            printf("Move Rook Error\n");
            return -1;
        }

        move_count++;
    }

    // Check Right 
    for (int i = coords.column + 1; i < 8; i++) {
        assert(i < BOARD_SIZE);
        current = gameboard[i][coords.row];
        check = CheckLocation(current, selected->piece->color);
       
        if (check == 0) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
        }
        else if (check == 1) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
            // break because no more moves beyond this point
            break;
        }
        else if (check == 2) {
            current->valid_move = 0;
            // break because no more moves beyond this point
            break;
        }
        else if (check == -1) {
            printf("Move Rook Error\n");
            return -1;
        }

        move_count++;   
    }
    //Check left
    for (int i = coords.column - 1; i >= 0; i--) {
        assert(i < BOARD_SIZE); 
        current = gameboard[i][coords.row];
        check = CheckLocation(current, selected->piece->color);
       
        if (check == 0) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
        }
        else if (check == 1) {
            if (for_check) {
                current -> check_move = 1;
            } else {
                current->valid_move = 1; 
            }
            // break because no more moves beyond this point
            break;
        }
        else if (check == 2) {
            current->valid_move = 0;
            // break because no more moves beyond this point
            break;
        }
        else if (check == -1) {
            printf("Move Rook Error\n");
            return -1;
        }

        move_count++;   
    }

    //printf("move count: %d\n", move_count);

    return move_count;
}

// Combining bishop and rook logic
int QueenMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check) 
{
    int move_count = 0;

    move_count += BishopMove(gameboard, coords, for_check);
    move_count += RookMove(gameboard, coords, for_check);
    
    return move_count; 
}

int KingMove(Location* gameboard[][BOARD_SIZE], Coordinates coords, int for_check)
{
    Location* selected = gameboard[coords.column][coords.row];
    Location* current = NULL;
    int move_count = 0;    
    int check;
   
    // hardcoded king moves
    int X[8] = {1, 1, 0, -1, -1, -1,  0,  1};
    int Y[8] = {0, 1, 1,  1,  0, -1, -1, -1};
    int x, y;

    // loop through all possible king moves
    for (int i = 0; i < 8; i++) {
        x = coords.row + X[i]; 
        y = coords.column + Y[i];
        if ((y < 0) || (y > 7) || (x < 0) || (x > 7)) {
            continue;
        }
        current = gameboard[y][x];
        check = CheckLocation(current, selected->piece->color);

        switch (check) {
            case 0: if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                     move_count++;
                     break;
            case 1: if (for_check) {
                        current -> check_move = 1;
                    } else {
                        current->valid_move = 1; 
                    }
                     move_count++;
                     break;
            case 2:  current->valid_move = 0;
                     break;
            case -1: printf("Error King Move\n");
                     break;
        }
    }

    if (!(gameboard[coords.column][coords.row]->piece->first_move) && !(for_check)) {
        // debug log
        // printf("Castle: %d\n", CheckCastling(gameboard, coords));
        CheckCastling(gameboard, coords);
    }

    return move_count;
}

int CheckCastling(Location* gameboard[][BOARD_SIZE], Coordinates coords)
{
   // printf("checking castling\n");
    int left_rook = 0;
    int right_rook = 0;

    // check if left rook has been moved
    if (gameboard[0][coords.row]->piece->type == ROOK) {
        if (!(gameboard[0][coords.row]->piece->first_move)) {
            // printf("Left rook not moved\n");
            left_rook = 1;
        }
    }
   
    // check if right rook has been moved
    if (gameboard[7][coords.row]->piece->type == ROOK) {
        if (!(gameboard[7][coords.row]->piece->first_move)) {
            // printf("Right rook not moved\n"); 
            right_rook = 1;
        }
    }

    // check left castling move
    if (left_rook) {
        if (!(gameboard[1][coords.row]->piece)
                && !(gameboard[2][coords.row]->piece)
                && !(gameboard[3][coords.row]->piece)) {
            gameboard[2][coords.row]->valid_move = 1;
            gameboard[2][coords.row]->castle = 1;
        }
    }
    
    // check right castling move
    if (right_rook) {
        if (!(gameboard[5][coords.row]->piece)
                && !(gameboard[6][coords.row]->piece)) {
            gameboard[6][coords.row]->valid_move = 1;
            gameboard[6][coords.row]->castle = 1;
        }
    }

    return 0;
}


/*

    calculating castling algorithm:

    - check if selected piece is king
        - if king: check if itself and both rooks have been moved
        - if rook: figure out which rook and if itself has been moved
                    and if king has been moved
    - check if path between rook and king is empty (just hardcode the coordinates
                                                    that need to be checked)
        - if true: set the castling position to be true
    - now move the king to the "cross over" location and calculate check
        - if in check: remove valid move from location
    - now move the king to the castling location and calculate check
        - if in check: remove valid move from location
    - revert king moves and return from function without errors
    
    
   moving the pieces for castling: (make corresponding function in GameLogic.c)

    - set the castling flag in location struct
    - if new location->castling = true
            (this condition implies that the king and rook are in their original
            locations, this means that coordinates for the castling move can
            be hardcoded) 

    possible king moves (columns): 0,2,6,7
    cross over locations: 3, 5
 */

int CheckEnPassant(Location *gameboard[][BOARD_SIZE], Coordinates coords)
{   
    // printf("Checking en passant\n");
    if (gameboard[coords.column][coords.row]->en_passant 
            && gameboard[coords.column][coords.row]->piece == NULL) {
        gameboard[coords.column][coords.row]->valid_move = 1;
    }

    return 0;
}

/*
 
   En Passant Pseudocode:

    in pawn move:

    - if move two forward
        - move piece two forward
        - set (location - 1).en_passant = 1
            * this marks the "passing location" 
    
    in check en passant:
    
    - Check for passing location (en_passnt = 1)
    - if passing location is a valid move: 
        - set valid move
    

    in gamelogic en passant function

    - if final location is en passant location
        - move the pawn to passing location
        - capture the opponent pawn


    ** En passant needs to be cleared when control is returned to opponent 
*/
