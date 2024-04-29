#include "MenuGUI.h"


//Callback function when "play" button is clicked
//closes menu window and starts game in terminal

void play_button_click(GtkWidget *widget, gpointer data) {
         Options *options = (Options* )data;
         LogList *log_list = NewLogList();
         Game game = options->game;
         game.game_log = log_list;
         game.game_mode = options->game_mode;
         game.color = (options->color==1)?WHITE: BLACK;

//         InitializeGameboard(game.gameboard, options->color);
//                 //closes menu window

	GtkWidget *menu_window = options->Window;
         gtk_main_quit();
//      start game in terminal
printf("testing play button");
}

void options_selected(GtkWidget *widget, gpointer data) {
        Options *options = (Options *)data;
        GtkWidget *button =  gtk_bin_get_child(GTK_BIN(widget));
        const gchar *label = gtk_label_get_text(GTK_LABEL(button));
        if (GTK_TOGGLE_BUTTON(widget)->active) {
                if(strcmp(label, "One Player")==0) {
                        options->game_mode = 1;
                        }
                else if (strcmp(label, "Two Players")==0) {
                        options->game_mode = 2;
                        }
                else if (strcmp(label, "AI vs AI")==0) {
                        options->game_mode = 3;
                        }
                else if (strcmp(label, "White")==0) {
                        options->color = 1;
                        }
                else if (strcmp(label, "Black")==0) {
                        options->color = 2;
                        }
                else if (strcmp(label, "Easy")==0) {
                        options->diff = 1;
                        }
                else if (strcmp(label, "Medium")==0) {
                        options->diff = 2;
                        }
                else if (strcmp(label, "Hard")==0) {
                        options->diff = 3;
                 }
        }

}

void menu(GtkWidget *window, Options *options) {
    //Widget variable declarations
    GtkWidget *title_label;
    GtkWidget *title_box, *all_options_box, *mode_box, *color_box, *diff_box, *play_box;
    GtkWidget *game_mode_label, *color_label, *diff_label;
    GtkWidget *mode1_button, *mode2_button, *mode3_button, *color1_button, *color2_button, *diff1_button, *diff2_button, *diff3_button, *play1_button, *play2_button;
    GtkWidget *mode1_label, *mode2_label, *mode3_label, *color1_label, *color2_label, *diff1_label, *diff2_label, *diff3_label, *play1_label, *play2_label;

    //Color declaration/initialization

    GdkColor blue1 = {0, 0xCE00, 0xE500, 0xF200};
    GdkColor blue2 = {0, 0xAC00, 0xCB00, 0xE100};
    GdkColor blue3 = {0, 0x7C00, 0x9800, 0xB300};
    GdkColor gray = {0, 0x5300, 0x6B00, 0x7800};
    //Setting up Menu Window

    gtk_window_set_title(GTK_WINDOW(window), "ChessCrafters");
    gtk_window_set_default_size(GTK_WINDOW(window), 950, 800);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &gray);

    /*create a vertical box for the title*/
    title_box = gtk_vbox_new(FALSE, 30);
    gtk_container_add(GTK_CONTAINER(window), title_box);

    /*create title*/
    title_label = gtk_label_new("ChessCraft !");
    gtk_label_set_markup(GTK_LABEL(title_label), "<span font_desc=\"Helvetica Bold 60\">ChessCraft !</span>");
    gtk_label_set_justify(GTK_LABEL(title_label), GTK_JUSTIFY_CENTER); // Center align the text
    gtk_widget_modify_fg(title_label, GTK_STATE_NORMAL, &blue2);

    gtk_box_pack_start(GTK_BOX(title_box), title_label, FALSE, FALSE, 50);

    /*create a horizontal box for game options*/
    all_options_box = gtk_hbox_new(FALSE, 80);
    gtk_box_pack_start(GTK_BOX(title_box), all_options_box, FALSE, FALSE, 0);

    /*create first options group*/
    mode_box = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(all_options_box), mode_box, FALSE, FALSE, 50);
    game_mode_label = gtk_label_new("Game Mode: ");
    gtk_label_set_markup(GTK_LABEL(game_mode_label), "<span font_desc=\"Times Bold 20\">Game Mode: </span>");
    gtk_label_set_justify(GTK_LABEL(game_mode_label), GTK_JUSTIFY_LEFT);
    gtk_widget_modify_fg(game_mode_label, GTK_STATE_NORMAL, &blue2);
    gtk_box_pack_start(GTK_BOX(mode_box), game_mode_label, FALSE, FALSE, 0);
    mode1_button = gtk_radio_button_new_with_label_from_widget(NULL, "One Player");
    mode2_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(mode1_button),"Two Players");
    mode3_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(mode1_button),"AI vs AI");

    gtk_widget_modify_bg(mode1_button, GTK_STATE_PRELIGHT, &gray);
    gtk_widget_modify_bg(mode2_button, GTK_STATE_PRELIGHT, &gray);
    gtk_widget_modify_bg(mode3_button, GTK_STATE_PRELIGHT, &gray);

    mode1_label = gtk_bin_get_child(GTK_BIN(mode1_button));
    mode2_label = gtk_bin_get_child(GTK_BIN(mode2_button));
    mode3_label = gtk_bin_get_child(GTK_BIN(mode3_button));

    gtk_label_set_markup(GTK_LABEL(mode1_label), "<span font_desc=\"Helvetica 18\">One Player</span>");
    gtk_label_set_markup(GTK_LABEL(mode2_label), "<span font_desc=\"Helvetica 18\">Two Players</span>");
    gtk_label_set_markup(GTK_LABEL(mode3_label), "<span font_desc=\"Helvetica 18\">AI vs AI</span>");

    gtk_widget_modify_fg(mode1_label, GTK_STATE_NORMAL, &blue2);
    gtk_widget_modify_fg(mode2_label, GTK_STATE_NORMAL, &blue2);
    gtk_widget_modify_fg(mode3_label, GTK_STATE_NORMAL, &blue2);

    gtk_widget_set_size_request(mode1_button, 100, 140);
    gtk_widget_set_size_request(mode2_button, 100, 140);
    gtk_widget_set_size_request(mode3_button, 100, 140);

    gtk_box_pack_start(GTK_BOX(mode_box), mode1_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mode_box), mode2_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mode_box), mode3_button, FALSE, FALSE, 0);

    g_signal_connect(mode1_button, "toggled", G_CALLBACK(options_selected), options);
    g_signal_connect(mode2_button, "toggled", G_CALLBACK(options_selected), options);
    g_signal_connect(mode3_button, "toggled", G_CALLBACK(options_selected), options);


    /*create second options group */
    color_box = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(all_options_box), color_box, FALSE, FALSE, 0);

    color_label = gtk_label_new("Color: ");
    gtk_label_set_markup(GTK_LABEL(color_label), "<span font_desc=\"Times Bold 20\">Color: </span>");
    gtk_label_set_justify(GTK_LABEL(color_label), GTK_JUSTIFY_LEFT);
    gtk_widget_modify_fg(color_label, GTK_STATE_NORMAL, &blue2);
    gtk_box_pack_start(GTK_BOX(color_box), color_label, FALSE, FALSE, 0);

    color1_button = gtk_radio_button_new_with_label_from_widget(NULL, "White");
    color2_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(color1_button),"Black");

    gtk_widget_modify_bg(color1_button, GTK_STATE_PRELIGHT, &gray);
    gtk_widget_modify_bg(color2_button, GTK_STATE_PRELIGHT, &gray);

    color1_label = gtk_bin_get_child(GTK_BIN(color1_button));
    color2_label = gtk_bin_get_child(GTK_BIN(color2_button));

    gtk_label_set_markup(GTK_LABEL(color1_label), "<span font_desc=\"Helvetica 18\">White</span>");
    gtk_label_set_markup(GTK_LABEL(color2_label), "<span font_desc=\"Helvetica 18\">Black</span>");

    gtk_widget_modify_fg(color1_label, GTK_STATE_NORMAL, &blue2);
    gtk_widget_modify_fg(color2_label, GTK_STATE_NORMAL, &blue2);

    gtk_widget_set_size_request(color1_button, 100, 140);
    gtk_widget_set_size_request(color2_button, 100, 140);

    gtk_box_pack_start(GTK_BOX(color_box), color1_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(color_box), color2_button, FALSE, FALSE, 0);

    g_signal_connect(color1_button, "toggled", G_CALLBACK(options_selected), options);
    g_signal_connect(color2_button, "toggled", G_CALLBACK(options_selected), options);
    
    //ceate an option group for difficulty level
    diff_box = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(all_options_box), diff_box, FALSE, FALSE, 0);

    diff_label = gtk_label_new("Difficulty: ");
    gtk_label_set_markup(GTK_LABEL(diff_label), "<span font_desc=\"Times Bold 20\">Difficulty: </span>");
    gtk_label_set_justify(GTK_LABEL(diff_label), GTK_JUSTIFY_LEFT);
    gtk_widget_modify_fg(diff_label, GTK_STATE_NORMAL, &blue2);
    gtk_box_pack_start(GTK_BOX(diff_box), diff_label, FALSE, FALSE, 0);

    diff1_button = gtk_radio_button_new_with_label_from_widget(NULL, "Easy");
    diff2_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(diff1_button),"Medium");
    diff3_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(diff1_button), "Hard");

    gtk_widget_modify_bg(diff1_button, GTK_STATE_PRELIGHT, &gray);
    gtk_widget_modify_bg(diff2_button, GTK_STATE_PRELIGHT, &gray);
    gtk_widget_modify_bg(diff3_button, GTK_STATE_PRELIGHT, &gray);

    diff1_label = gtk_bin_get_child(GTK_BIN(diff1_button));
    diff2_label = gtk_bin_get_child(GTK_BIN(diff2_button));
    diff3_label = gtk_bin_get_child(GTK_BIN(diff3_button));

    gtk_label_set_markup(GTK_LABEL(diff1_label), "<span font_desc=\"Helvetica 18\">Easy</span>");
    gtk_label_set_markup(GTK_LABEL(diff2_label), "<span font_desc=\"Helvetica 18\">Medium</span>");
    gtk_label_set_markup(GTK_LABEL(diff3_label), "<span font_desc=\"Helvetica 18\">Hard</span>");

    gtk_widget_modify_fg(diff1_label, GTK_STATE_NORMAL, &blue2);
    gtk_widget_modify_fg(diff2_label, GTK_STATE_NORMAL, &blue2);
    gtk_widget_modify_fg(diff3_label, GTK_STATE_NORMAL, &blue2);

    gtk_widget_set_size_request(diff1_button, 100, 140);
    gtk_widget_set_size_request(diff2_button, 100, 140);
    gtk_widget_set_size_request(diff3_button, 100, 140);

    gtk_box_pack_start(GTK_BOX(diff_box), diff1_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(diff_box), diff2_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(diff_box), diff3_button, FALSE, FALSE, 0);

    g_signal_connect(diff1_button, "toggled", G_CALLBACK(options_selected), options);
    g_signal_connect(diff2_button, "toggled", G_CALLBACK(options_selected), options);
    g_signal_connect(diff3_button, "toggled", G_CALLBACK(options_selected), options);

    /*play and  quit buttons */
    play_box = gtk_vbox_new(FALSE, 20);
    gtk_box_pack_start(GTK_BOX(all_options_box), play_box, FALSE, FALSE, 0);

    play1_button = gtk_button_new_with_label("PLAY");
    play2_button = gtk_button_new_with_label("QUIT");

    play1_label = gtk_bin_get_child(GTK_BIN(play1_button));
    play2_label = gtk_bin_get_child(GTK_BIN(play2_button));

    gtk_label_set_markup(GTK_LABEL(play1_label), "<span font_desc=\"Helvetica 24\">PLAY</span>");
    gtk_label_set_markup(GTK_LABEL(play2_label), "<span font_desc=\"Helvetica 24\">QUIT</span>");

    gtk_widget_set_size_request(play1_button, 200, 100);
    gtk_widget_set_size_request(play2_button, 200, 100);

    gtk_box_pack_start(GTK_BOX(play_box), play1_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(play_box), play2_button, FALSE, FALSE, 0);

    options->Window = window;
    //Callback to play_button_click function when "Play" button is clicked
    g_signal_connect(play1_button, "clicked", G_CALLBACK(play_button_click), options);
    //Callback to gtk_main_quit when "Quit" button is clicked or if window is destroyed
    g_signal_connect(play2_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 //   gtk_widget_show_all(window);
 
//    gtk_main();

}
