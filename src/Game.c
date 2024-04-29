#include "Game.h"
#include "Bot.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int PlayGame(Game game, Bot bot1, Bot bot2)
{
    // Board and Variable Setup
    Coordinates user_start_coordinates;
    Coordinates user_end_coordinates;
    game.check = 0;
    game.player = PLAYER1;
    char user_selection[10];
    int bot1_turn = 0;
    int bot2_turn = 0;

    // if quit == 1 or mate == 1 then exit game
    int quit = 0;
    game.mate = 0;
    int input_type = 0;
    /* Input types:
        1: Options
        2: Hint
        3: Cancel Selected Piece
        4: Quit
        5: Coordinates
        6: Invalid User Input
    */

    int move_step = 0;
    /* move_step list:
    0: Choosing start coordinate phase
    1: Choosing end coordate phase
    2: Finished move
    */

    // if finish move == 1 then move on to next player
    int finish_move = 0;

    // Creating int variable to pass to InitializeGameboard
    int color_value;
    // Human vs. AI
    if (game.game_mode == 1)
    {
        switch (game.color)
        {
        case WHITE:
            color_value = 1;
            game.player = PLAYER1;
            break;
        case BLACK:
            color_value = 2;
            game.player = PLAYER2;
            game.color = WHITE;
            break;
        }

        InitializeGameboard(game.gameboard, color_value);

        // While loop to handle player turns
        while ((game.mate != 1) && (quit != 1))
        {
            PrintBoard(game.gameboard);
            switch (game.player)
            {
            case PLAYER1:
                printf("It is Player %d's Turn.\n", game.player + 1);
                while (finish_move != 1)
                {
                    // Obtaining and executing start coordinate
                    while (move_step == 0)
                    {
                        if (game.check == 1)
                        {
                            printf("Player %d is in check!\n", game.player + 1);
                        }

                        input_type = 0;
                        // Get initial user input
                        GetUserInput(user_selection, move_step);
                        input_type = CheckUserInput(user_selection, &game, move_step);

                        // if the user input is invalid or opens options, get input again
                        while (input_type == 6)
                        {
                            GetUserInput(user_selection, move_step);
                            input_type = CheckUserInput(user_selection, &game, move_step);
                        }

                        // if user input is coordinates, then convert string to coordinates
                        if (input_type == 5)
                        {
                            user_start_coordinates = ConvertToCoordinates(user_selection);
                        }

                        // Execute user input based off of input type
                        ExecuteUserInput(user_start_coordinates, user_end_coordinates, input_type, &quit, &move_step, &finish_move, &game);
                    }

                    // Obtaining and executing end coordinate
                    while (move_step == 1)
                    {
                        input_type = 0;
                        // Get initial user input
                        GetUserInput(user_selection, move_step);
                        input_type = CheckUserInput(user_selection, &game, move_step);

                        // if the user input is invalid or opens options, get input again
                        while (input_type == 6)
                        {
                            GetUserInput(user_selection, move_step);
                            input_type = CheckUserInput(user_selection, &game, move_step);
                        }

                        // if user input is coordinates, then convert string to coordinates
                        if (input_type == 5)
                        {
                            user_end_coordinates = ConvertToCoordinates(user_selection);
                        }

                        // Execute user input based off of input type
                        ExecuteUserInput(user_start_coordinates, user_end_coordinates, input_type, &quit, &move_step, &finish_move, &game);
                    }
                }
                break;

            case PLAYER2:
                bot1_turn++;
                printf("Bot %d is on Turn %d.\n", game.player + 1, bot1_turn);
                GetBotMove(&bot1, &game, bot1_turn);
                move_step = 1;
                ExecuteUserInput(bot1.start_location, bot1.end_location, 5, &quit, &move_step, &finish_move, &game);
                move_step = 0;
                break;
            }

            move_step = 0;
            finish_move = 0;

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
    }

    // Human vs. Human
    if (game.game_mode == 2)
    {
        switch (game.color)
        {
        case WHITE:
            color_value = 1;
            game.player = PLAYER1;
            break;
        case BLACK:
            color_value = 2;
            game.player = PLAYER2;
            game.color = WHITE;
            break;
        }

        InitializeGameboard(game.gameboard, color_value);

        // While loop to handle player turns
        while ((game.mate != 1) && (quit != 1))
        {
            PrintBoard(game.gameboard);
            printf("It is Player %d's Turn.\n", game.player + 1);
            move_step = 0;
            finish_move = 0;

            while (finish_move != 1)
            {

                // Obtaining and executing start coordinate
                while (move_step == 0)
                {
                    if (game.check == 1)
                    {
                        printf("Player %d is in check!\n", game.player + 1);
                    }

                    input_type = 0;
                    // Get initial user input
                    GetUserInput(user_selection, move_step);
                    input_type = CheckUserInput(user_selection, &game, move_step);

                    // if the user input is invalid or opens options, get input again
                    while (input_type == 6)
                    {
                        GetUserInput(user_selection, move_step);
                        input_type = CheckUserInput(user_selection, &game, move_step);
                    }

                    // if user input is coordinates, then convert string to coordinates
                    if (input_type == 5)
                    {
                        user_start_coordinates = ConvertToCoordinates(user_selection);
                    }

                    // Execute user input based off of input type
                    ExecuteUserInput(user_start_coordinates, user_end_coordinates, input_type, &quit, &move_step, &finish_move, &game);
                }

                // Obtaining and executing end coordinate
                while (move_step == 1)
                {
                    input_type = 0;
                    // Get initial user input
                    GetUserInput(user_selection, move_step);
                    input_type = CheckUserInput(user_selection, &game, move_step);

                    // if the user input is invalid or opens options, get input again
                    while (input_type == 6)
                    {
                        GetUserInput(user_selection, move_step);
                        input_type = CheckUserInput(user_selection, &game, move_step);
                    }

                    // if user input is coordinates, then convert string to coordinates
                    if (input_type == 5)
                    {
                        user_end_coordinates = ConvertToCoordinates(user_selection);
                    }

                    // Execute user input based off of input type
                    ExecuteUserInput(user_start_coordinates, user_end_coordinates, input_type, &quit, &move_step, &finish_move, &game);
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
    }

    // AI vs. AI
    if (game.game_mode == 3)
    {
        int turn_generation = 0;
        switch (game.color)
        {
        case WHITE:
            color_value = 1;
            game.player = PLAYER1;
            break;
        case BLACK:
            color_value = 2;
            game.player = PLAYER2;
            game.color = WHITE;
            break;
        }

        InitializeGameboard(game.gameboard, color_value);

        // While loop to handle player turns
        while ((game.mate != 1) && (quit != 1))
        {
            PrintBoard(game.gameboard);
            printf("How many turns do you want to generate: ");
            scanf("%d", &turn_generation);

            for (int i = 0; i < turn_generation; i++)
            {
                switch (game.player)
                {
                case PLAYER1:
                    bot1_turn++;
                    printf("Bot %d is on Turn %d.\n", game.player + 1, bot1_turn);
                    GetBotMove(&bot1, &game, bot1_turn);
                    move_step = 1;
                    ExecuteUserInput(bot1.start_location, bot1.end_location, 5, &quit, &move_step, &finish_move, &game);
                    move_step = 0;
                    break;

                case PLAYER2:
                    bot2_turn++;
                    printf("Bot %d is on Turn %d.\n", game.player + 1, bot2_turn);
                    GetBotMove(&bot2, &game, bot2_turn);
                    move_step = 1;
                    ExecuteUserInput(bot2.start_location, bot2.end_location, 5, &quit, &move_step, &finish_move, &game);
                    move_step = 0;
                    break;
                }

                if (game.mate == 1)
                {
                    break;
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
            }
        }
    }

    return 0;
}

// Returns 1 the if user doesn't enter a valid user coordinate
int NotValidUserCoordinate(char user_selection[], Game *game, int move_step)
{
    Coordinates test_coordinate = ConvertToCoordinates(user_selection);
    Location *test_location = game->gameboard[test_coordinate.column][test_coordinate.row];

    // Syntax errors
    // Check if input length is >3
    if (user_selection[2] != '\0')
    {
        printf("Invalid input! Input is not a valid command.\n");
        return 1;
    }

    // Check if the first character is an alphabet letter
    if (isalpha(user_selection[0]) == 0)
    {
        printf("Invalid input! first character is not an alphabet letter.\n");
        return 1;
    }

    // Check if the first letter is in range a-h or A-H
    if (toupper(user_selection[0]) < 'A' || toupper(user_selection[0]) > 'H')
    {
        printf("Invalid input! First character is not in the range A-H.\n");
        return 1;
    }

    // Check if the second character is a digit
    if (isdigit(user_selection[1]) == 0)
    {
        printf("Invalid input! Second character is not a digit.\n");
        return 1;
    }

    // Check if the second number is in range of 1-8
    if (user_selection[1] < '1' || user_selection[1] > '8')
    {
        printf("Invalid input! Second character is not a digit between 1-8.\n");
        return 1;
    }

    if (move_step == 0)
    {
        // Check if there is a piece on that location of the same color
        //  Returns -1 if error
        //  Returns 0 if empty location
        //  Returns 1 if contains opposite color piece
        //  Returns 2 if contains same color piece
        int location_checker = CheckLocation(test_location, game->color);
        if (location_checker != 2)
        {
            switch (location_checker)
            {
            case -1:
                printf("Invalid input! Inputted Coordinate produces an error.\n");
                break;
            case 0:
                printf("Invalid input! Inputted Coordinate is an empty location.\n");
                break;
            case 1:
                switch (game->color)
                {
                case WHITE:
                {
                    printf("Invalid input! Please choose a white piece.\n");
                    break;
                }
                case BLACK:
                {
                    printf("Invalid input! Please choose a black piece.\n");
                    break;
                }
                }
                break;
            }

            return 1;
        }

        // Check if piece has moves
        if (CalculateMoves(game, game->gameboard, test_coordinate, 0) == 0)
        {
            printf("Invalid input! Selected piece has no valid moves.\n");
            return 1;
        }
    }

    if (move_step == 1)
    {
        // Check if user selected a location with a valid move
        if (!game->gameboard[test_coordinate.column][test_coordinate.row]->valid_move)
        {
            printf("Invalid Move! Please select a location highlighted by **** or type \"cancel\" to cancel your move.\n");
            return 1;
        }
    }

    // If everything is good then returns 0
    return 0;
}

// Capitalizes user input
void CapitalizeUserInput(char *user_selection)
{
    for (int i = 0; i < strlen(user_selection); i++)
    {
        user_selection[i] = toupper(user_selection[i]);
    }
}

// Gets user input, even after they have typed an inccorect input
void GetUserInput(char *user_selection, int move_step)
{
    switch (move_step)
    {
    case 0:
        printf("Select Piece Location or Option(To see option commands, Type \"options\"): ");
        scanf("%s", user_selection);
        CapitalizeUserInput(user_selection);
        break;
    case 1:
        printf("Select Piece Movement or Option(To see option commands, Type \"options\"): ");
        scanf("%s", user_selection);
        CapitalizeUserInput(user_selection);
        break;
    }
}

// Checks if the user entered a valid input
int CheckUserInput(char user_selection[], Game *game, int move_step)
{

    if (strcmp(user_selection, "OPTIONS") == 0)
    {
        return 1;
    }

    if (strcmp(user_selection, "HINT") == 0)
    {
        return 2;
    }

    if (strcmp(user_selection, "CANCEL") == 0)
    {
        return 3;
    }

    if (strcmp(user_selection, "QUIT") == 0)
    {
        return 4;
    }

    if (NotValidUserCoordinate(user_selection, game, move_step) == 0)
    {
        return 5;
    }

    // If none of these satisfy...
    return 6;
}

Coordinates ConvertToCoordinates(char user_selection[])
{
    Coordinates convert_coordinates;
    convert_coordinates.column = toupper(user_selection[0]) - 65;
    convert_coordinates.row = user_selection[1] - '0' - 1;

    return convert_coordinates;
}

void ExecuteUserInput(Coordinates user_start_coordinates, Coordinates user_end_coordinates, int input_type, int *quit, int *move_step, int *finish_move, Game *game)
{

    switch (input_type)
    {
    case 1:
        // print options
        printf("Options (Type the command you want below):\n- Hint\n- Cancel\n- Quit\n");
        return;

    case 2:
        GetRandomHint(game);
        // hint
        return;

    case 3:
        Cancel(game->gameboard, move_step);
        return;

    case 4:
        printf("You have exited the game.\n");
        *move_step = 2;
        *quit = 1;
        *finish_move = 1;
        DeleteBoard(game->gameboard);
        return;
    }

    if ((input_type == 5) && (*move_step == 0))
    {
        CalculateMoves(game, game->gameboard, user_start_coordinates, 0);
        printf("Valid moves:\n");
        PrintBoard(game->gameboard);
        *move_step = 1;
        return;
    }

    else if ((input_type == 5) && (*move_step == 1))
    {
        MovePiece(game->gameboard, user_start_coordinates, user_end_coordinates, game);
        ClearBoard(game->gameboard);
        if (game->check)
        {
            game->check = 0;
        }
        Check(game, game->gameboard, 0);
        if (game->check)
        {
            CheckMate(game, game->gameboard, 0);
        }
        if (game->mate == 1)
        {
            printf("Game Over\n");
            DeleteBoard(game->gameboard);
            *quit = 1;
        }

        *move_step = 0;
        *finish_move = 1;
        return;
    }
}

void Cancel(Location *gameboard[BOARD_SIZE][BOARD_SIZE], int *move_step)
{
    if (*move_step == 1)
    {
        printf("You have cancelled your move.\n");
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                gameboard[x][y]->valid_move = 0;
            }
        }
        *move_step = 0;
        PrintBoard(gameboard);
        return;
    }
    else
    {
        printf("Can't cancel right now!\n");
        return;
    }
}

// Gives a user a hint
void GetRandomHint(Game *game)
{
    Bot HintBot;
    HintBot.color = game->color;
    HintBot.difficulty = EASY;
    GetBotMove(&HintBot, game, 1);
    char start_char;
    char end_char;
    // Start coordinate column conversion
    if (HintBot.start_location.column < 0 || HintBot.start_location.column > 7)
    {
        start_char = ' ';
    }
    else
    {
        start_char = 'A' + HintBot.start_location.column;
    }

    // End coordinate column conversion
    if (HintBot.end_location.column < 0 || HintBot.end_location.column > 7)
    {
        end_char = ' ';
    }
    else
    {
        end_char = 'A' + HintBot.end_location.column;
    }

    int start_int = HintBot.start_location.row + 1;
    int end_int = HintBot.end_location.row + 1;

    printf("Hint: You should move the piece on %c%d to %c%d\n", start_char, start_int, end_char, end_int);
}
