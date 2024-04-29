#include "GameLogic.h"
#include "Bot.h"
#include <ctype.h>

//This function starts the game by calling functions to initialize the board and handles turns afterwards
int PlayGame(Game, Bot bot1, Bot bot2);

//This function will return if a piece is captured or not
// int CapturePiece(Game);

//Capitalize input
void CapitalizeUserInput(char *user_selection);

//Get user input
void GetUserInput(char *user_selection, int move_step);

//Check user input
int CheckUserInput(char user_selection[], Game* game, int move_step);

//Check syntax of Coordinates input
int NotValidUserCoordinate(char user_selection[], Game* game, int move_step);

//Execute the inputted string of the user
void ExecuteUserInput(Coordinates user_start_coordinates, Coordinates user_end_coordinates, int input_type, int *quit, int *move_step, int *finish_move, Game* game);

//Cancel and choose another 
void Cancel(Location* gameboard[BOARD_SIZE][BOARD_SIZE], int *move_step);

//Converts user input to coordinates
Coordinates ConvertToCoordinates(char user_selection[]);

//Gives a user a hint
void GetRandomHint(Game* game);