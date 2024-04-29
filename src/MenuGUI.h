#ifndef MENUGUI_H
#define MENUGUI_
#include "Piece.h"
#include "Board.h"
#include "Game.h"
#include <gtk/gtk.h>
#define WINDOW_BORDER 10


//struct that holds game options toggled 
typedef struct {
        int game_mode;
        int color;
        int diff;
	GtkWidget *Window;
	Game game;
} Options;



void menu(GtkWidget *window, Options *options);
#endif

