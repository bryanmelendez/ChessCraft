#include "Menu.h"
#include <stdio.h>

int Menu1(int play_option){
	int game_mode_option = 0;
	int valid_option = 0;

	if(play_option !=2) {
	printf("\n-------ChessCraft-------\n\nWelcome to ChessCraft v.3.0\n");
	}

		//if the input is not an integer:
	while(valid_option == 0) {
		printf("\nGame modes:\n1. One Player\n2. Two Players\n3. AI vs. AI\n4. Quit Game\n\nSelect a game mode (1-4): ");
		if(scanf("%d", &game_mode_option) != 1) {
			printf("\n!!Invalid option!!\n");
			valid_option = 0;

			//clear input buffer
			while (getchar() != '\n') {
            	continue;
			}

			continue;
		}

		if (game_mode_option == 1 || game_mode_option == 2 || game_mode_option == 3 || game_mode_option == 4) {
			valid_option = 1;
			}
		
		else {
			printf("\n!!Invalid option!!\n");
			}	
	}
	return game_mode_option;
}	

int Menu2(int game_option) {
	int color_option = 0;
	PieceColor piece_color_option;
	int valid_option = 0;

	while (valid_option == 0) {

		if(game_option == 3) {
			printf("\nSelect to Bot1 to play as White (1) or Black (2): ");			
		}
		else {
		printf("\nSelect to play as White (1) or Black (2): ");
		}

	//if the input is not an integer:
	if(scanf("%d", &color_option) != 1) {
		printf("\n!!Invalid option!!\n");
		valid_option = 0;

		//clear input buffer
		while (getchar() != '\n') {
			continue;
		}

		continue;
	}

	if (color_option == 1 || color_option == 2) {
		valid_option = 1;
		}
	
	else {
		printf("\n!!Invalid option!!\n");
		}	
	}

	piece_color_option = (color_option == 1)? WHITE: BLACK;
	return piece_color_option;
}

int Menu3(int bot_num) {
	int diff_option = 0;
	int valid_option = 0;

	while (valid_option == 0) {

		if(bot_num == 1 || bot_num == 2) {
		printf("\nDifficulty Levels: \n 1.Easy \n 2.Medium\n 3.Hard\n\n Select a Difficulty Level for Bot%d: ", bot_num);
		}
		else {
		printf("\nDifficulty Levels: \n 1.Easy \n 2.Medium\n 3.Hard\n\n Select a Difficulty Level: ");
		}

	//if the input is not an integer:
	if(scanf("%d", &diff_option) != 1) {
		printf("\n!!Invalid option!!\n");
		valid_option = 0;

		//clear input buffer
		while (getchar() != '\n') {
			continue;
		}

		continue;
	}

	if (diff_option == 1 || diff_option == 2 || diff_option == 3) {
		valid_option = 1;
		}
	
	else {
		printf("\n!!Invalid option!!\n");
		}	
	}

	return diff_option;
}

int Menu4() {
	int play_option = 0;
	int valid_option = 0;

	while (valid_option == 0) {
		printf("\nSelect to Play (1) or Change Options (2): ");

		//if the input is not an integer:
		if(scanf("%d", &play_option) != 1) {
			printf("\n!!Invalid option!!\n");
			valid_option = 0;

			//clear input buffer
			while (getchar() != '\n') {
				continue;
			}

			continue;
		}

		if (play_option == 1 || play_option == 2) {
			valid_option = 1;
			}

		else {
			printf("\n!!Invalid option!!\n");
			}	
		}	
	return play_option;
}
