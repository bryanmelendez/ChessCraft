#include "Menu.h"
#include "Game.h"
#include "Log.h"
int main()
{
	int game_op = 0;
	PieceColor color_op = 0;
	int diff_op1 = 0;
	int diff_op2= 0;
	int play_op = 0;
	Game game;
	game.mate = 0;
	LogList *log_list = NewLogList();
	Bot bot1;
	Bot bot2;

	// do-while loop for cases where user decides to change options (if they input 2 for the 'play' option)
	do
	{
		game_op = Menu1(play_op);
		switch(game_op) {
			case 1:
				color_op = Menu2(0);
				diff_op1 = Menu3(0);
				play_op = Menu4();
				break;
			case 2:
				color_op = Menu2(0);
				play_op = Menu4();
				break;
			case 3:
				color_op = Menu2(3);
				diff_op1 = Menu3(1);
				diff_op2 = Menu3(2);
				play_op = Menu4();
				break;
			case 4:
        		printf("You have exited the game.\n");
				exit(0);
		}

		// assiging user input to game object
		game.game_mode = game_op;
		game.color = color_op;
		game.game_log = log_list;


		//assigning user input to bot1 object
		switch(diff_op1) {
			case 1:
				bot1.difficulty = EASY;
				break;
			case 2:
				bot1.difficulty = MEDIUM;
				break;
			case 3:
				bot1.difficulty = HARD;
				break;

		//assigning user input to bot2 object				
		}
		switch(diff_op2) {
			case 1:
				bot2.difficulty = EASY;
				break;
			case 2:
				bot2.difficulty = MEDIUM;
				break;
			case 3:
				bot2.difficulty = HARD;
				break;
				
		}

		if(game_op == 1) {
			switch(color_op) {
				case 0:
					bot1.color = BLACK;
					break;
				case 1:
					bot1.color = WHITE;
					break;
			}
		}

		else if(game_op == 3) {
			switch(color_op) {
				case 0:
					bot1.color = WHITE;
					bot2.color = BLACK;
					break;
				case 1:
					bot1.color = BLACK;
					bot2.color = WHITE;
					break;
			}
		}

	} while (play_op == 2);
	game.color = color_op;
	PlayGame(game, bot1, bot2);
	DeleteLogList(log_list);
	return 0;
}