#include "Menu.h"
#include "Game.h"
#include "Log.h"
#include "MenuGUI.h"

int main()
{
	int game_op = 0;
	PieceColor color_op = 0;
	int diff_op = 0;
	int play_op = 0;

        Game game;
        game.mate = 0;
	
	Bot bot;

        GtkWidget *window;
        Options *options = malloc(sizeof(Options));
        options->game_mode = 1;
        options->color = 1;
        options->diff = 1;
        gtk_init(NULL, NULL);

        options->game = game;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        menu(window, options);

        printf("just testing tiiming !!! \n");
     
        gtk_widget_show_all(window);
 
         gtk_main();

//assign Options from toggled buttons to the variables

//once the user exits the gtk window, the game will start in the terminal
	
printf("this is a test \n");
int i=0;
while (i<9) {
	printf("co9unting\n");
	i++;

}

//PlayGame(game, bot);
//DeleteLogList(log_list);
return 0;
}
