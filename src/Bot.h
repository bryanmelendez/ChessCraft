#ifndef __BOT_H__
#define __BOT_H__

#include "GameLogic.h"
#include <time.h>
#include <stdlib.h>

typedef enum {EASY, MEDIUM, HARD} Difficulty;

typedef struct {
    Difficulty difficulty;
    Coordinates start_location;
    Coordinates end_location;
    PieceColor color;
} Bot;

// Pass in Bot struct, function updates start and end location
int GetBotMove(Bot* bot, Game* game, int bot_turn);
int EasyMove(Bot* bot, Game* game);
int MediumMove(Bot* bot, Game* game, int bot_turn);
int HardMove(Bot* bot, Game* game, int bot_turn);
void GetRandomCoordinates(Coordinates* coords);
void GetRandomPosition(Bot* bot, Coordinates *coords, Location* gameboard[BOARD_SIZE][BOARD_SIZE]);
void GetRandomMove(Bot* bot, Coordinates* coords, Location* gameboard[BOARD_SIZE][BOARD_SIZE]);

#endif
