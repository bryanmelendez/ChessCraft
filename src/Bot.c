#include "Bot.h"
#include <stdio.h>

int GetBotMove(Bot* bot, Game *game, int bot_turn)
{
    switch (bot->difficulty) {
        case EASY:   EasyMove(bot, game);
                     break;
        case MEDIUM: MediumMove(bot, game, bot_turn);
                     break;
        case HARD:   HardMove(bot, game, bot_turn);
                     break;
        default: printf("Bot Error\n");
    }

    return 0;
}

int EasyMove(Bot* bot, Game *game)
{
    int move_count = 0;
 
    do {
        // Check this and make sure the actually coordinates struct is being passed
        GetRandomPosition(bot, &bot->start_location, game->gameboard);

        move_count = CalculateMoves(game, game->gameboard, bot->start_location, 0);

        //printf("loop1\n");

    } while (move_count == 0);

    GetRandomMove(bot, &bot->end_location, game->gameboard);

    return 0;
}

int MediumMove(Bot* bot, Game* game, int bot_turn)
{
    int move_count = 0;
    // Returns 0 if empty location
    // Returns 1 if contains opposite color piece
    // Returns 2 if contains same color piece

     //basic book moves chess opening
     if(game->player == PLAYER1) {
        switch(bot_turn) {
            case 1:
                bot->start_location.column = 4;
                bot->start_location.row = 1;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 4;
                bot->end_location.row = 3;
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 2:
                bot->start_location.column = 1;
                bot->start_location.row = 0;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 2;
                bot->end_location.row = 2;
                if(CalculateMoves(game, game->gameboard, bot->start_location, 0) == 0) {
                    EasyMove(bot, game);
                }
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 3:
                bot->start_location.column = 6;
                bot->start_location.row = 0;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 5;
                bot->end_location.row = 2;
                if(CalculateMoves(game, game->gameboard, bot->start_location, 0) == 0) {
                    EasyMove(bot, game);
                }
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 4:
                bot->start_location.column = 3;
                bot->start_location.row = 1;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 3;
                bot->end_location.row = 3;
                if(CalculateMoves(game, game->gameboard, bot->start_location, 0) == 0) {
                    EasyMove(bot, game);
                }
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            default:
                break;
        }
    }

    if(game->player == PLAYER2) {
        switch(bot_turn) {
            case 1:
                bot->start_location.column = 4;
                bot->start_location.row = 6;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 4;
                bot->end_location.row = 4;
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 2:
                bot->start_location.column = 1;
                bot->start_location.row = 7;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 2;
                bot->end_location.row = 5;
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 3:
                bot->start_location.column = 6;
                bot->start_location.row = 7;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 5;
                bot->end_location.row = 5;
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            case 4:
                bot->start_location.column = 3;
                bot->start_location.row = 6;
                CalculateMoves(game, game->gameboard, bot->start_location, 0);
                bot->end_location.column = 3;
                bot->end_location.row = 4;
                if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                    EasyMove(bot, game);
                }
                if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                    EasyMove(bot, game);                    
                }
                break;
            default:
                break;
        }
    }

    if(bot_turn > 4) {
        printf("turn  4 and beyond\n");
        do {
            // Check this and make sure the actually coordinates struct is being passed
            GetRandomPosition(bot, &bot->start_location, game->gameboard);

            move_count = CalculateMoves(game, game->gameboard, bot->start_location, 0);

            //printf("loop1\n");

        } while (move_count == 0);

        GetRandomMove(bot, &bot->end_location, game->gameboard);
    }
    return 0;
}

int HardMove(Bot* bot, Game* game, int bot_turn)
{
    int move_count = 0;
    //stonewall chess opening
    
    if(game->player == PLAYER1) {
        if(bot->color == WHITE) {
            switch(bot_turn) {
                case 1:
                    bot->start_location.column = 3;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 3;
                    bot->end_location.row = 3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 2:
                    bot->start_location.column = 4;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 4;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 3:
                    bot->start_location.column = 5;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 3;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 4:
                    bot->start_location.column = 1;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 3;
                    bot->end_location.row = 1;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 5:
                    bot->start_location.column = 5;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 5;
                    bot->end_location.row = 3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 6:
                    bot->start_location.column = 6;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 5;
                    bot->end_location.row =2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 7:
                    bot->start_location.column = 2;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 2;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 8:
                    bot->start_location.column = 4;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 6;
                    bot->end_location.row = 0;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                default:
                    break;
            }
        }

        if(bot->color == BLACK) {
            switch(bot_turn) {
                case 1:
                    bot->start_location.column = 4;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 4;
                    bot->end_location.row = 3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 2:
                    bot->start_location.column = 3;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 3;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 3:
                    bot->start_location.column = 5;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 5;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                
                    }
                    break;
                case 4:
                    bot->start_location.column = 2;
                    bot->start_location.row = 1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 2;
                    bot->end_location.row = 3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 5:
                    bot->start_location.column = 2;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 4;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 6:
                    bot->start_location.column = 1;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 2;
                    bot->end_location.row = 2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 7:
                    bot->start_location.column = 6;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 4;
                    bot->end_location.row = 1;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 8:
                    bot->start_location.column = 3;
                    bot->start_location.row = 0;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 1;
                    bot->end_location.row = 0;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if(game->player == PLAYER2) {
        if(bot->color == WHITE) {
            switch(bot_turn) {
                case 1:
                    bot->start_location.column = 7-3;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-3;
                    bot->end_location.row = 7-3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 2:
                    bot->start_location.column = 7-4;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-4;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 3:
                    bot->start_location.column = 7-5;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-3;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 4:
                    bot->start_location.column = 7-1;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-3;
                    bot->end_location.row = 7-1;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 5:
                    bot->start_location.column = 7-5;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-5;
                    bot->end_location.row = 7-3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 6:
                    bot->start_location.column = 7-6;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-5;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 7:
                    bot->start_location.column = 7-2;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-2;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 8:
                    bot->start_location.column = 7-4;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-6;
                    bot->end_location.row = 7-0;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                default:
                    break;
            }
        }

        if(bot->color == BLACK) {
            switch(bot_turn) {
                case 1:
                    bot->start_location.column = 7-4;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-4;
                    bot->end_location.row = 7-3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 2:
                    bot->start_location.column = 7-3;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-3;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 3:
                    bot->start_location.column = 7-5;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-5;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                
                    }
                    break;
                case 4:
                    bot->start_location.column = 7-2;
                    bot->start_location.row = 7-1;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-2;
                    bot->end_location.row = 7-3;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 5:
                    bot->start_location.column = 7-2;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-4;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 6:
                    bot->start_location.column = 7-1;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 0);
                    bot->end_location.column = 7-2;
                    bot->end_location.row = 7-2;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 7:
                    bot->start_location.column = 7-6;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 7-0);
                    bot->end_location.column = 7-4;
                    bot->end_location.row = 7-1;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                case 8:
                    bot->start_location.column = 7-3;
                    bot->start_location.row = 7;
                    CalculateMoves(game, game->gameboard, bot->start_location, 7-0);
                    bot->end_location.column = 7-1;
                    bot->end_location.row = 7;
                    if(CheckLocation(game->gameboard[bot->start_location.column][bot->start_location.row], bot->color) != 2) {
                        EasyMove(bot, game);
                    }
                    if((CheckLocation(game->gameboard[bot->end_location.column][bot->end_location.row], bot->color) != 0)) {
                        EasyMove(bot, game);                    
                    }
                    break;
                default:
                    break;
            }
        }
    }


    if(bot_turn > 8) {
    do {
        // Check this and make sure the actually coordinates struct is being passed
        GetRandomPosition(bot, &bot->start_location, game->gameboard);

        move_count = CalculateMoves(game, game->gameboard, bot->start_location, 0);

        //printf("loop1\n");

    } while (move_count == 0);

    GetRandomMove(bot, &bot->end_location, game->gameboard);
    }

    return 0;
}

void GetRandomCoordinates(Coordinates *coords)
{
    coords->column = rand() % 8;
    coords->row = rand() % 8;

    //printf("Random coords: %d, %d\n", coords->column, coords->row);
}

// Finds a location of same color piece and updates coordinates
void GetRandomPosition(Bot* bot, Coordinates* coords, Location* gameboard[BOARD_SIZE][BOARD_SIZE])
{
    srand(time(NULL));

    int valid_location = 0;

    do {
        GetRandomCoordinates(coords);

        if (CheckLocation(gameboard[coords->column][coords->row], bot->color) == 2) {
            valid_location = 1; 
        }
    } while (!valid_location);
}

void GetRandomMove(Bot* bot, Coordinates* coords, Location* gameboard[BOARD_SIZE][BOARD_SIZE])
{
    srand(time(NULL));

    int valid_location = 0;

     do {
        GetRandomCoordinates(coords);

        if (gameboard[coords->column][coords->row]->valid_move == 1) {
            //printf("Valid location\n");
            valid_location = 1; 
        }
    } while (!valid_location); 
}