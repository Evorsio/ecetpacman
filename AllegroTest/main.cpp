#include "Include.h"



int main(int argc, char **argv)
{

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Variable Initialization"
	
	const float FPS = 60;
	int screenw = 900;
	int screenh = 650;
	float bounce = 25;
	float bouncer_x = 604;
	float bouncer_y = 300;
	float wall1_x = 140.0;
	float wall1_y = 30.0;
	float wall1_w = 30.0;
	float wall1_h = 30.0;
	float wall2_x = 140.0;
	float wall2_y = 30.0;
	float wall2_w = 70.0;
	float wall2_h = 70.0;
	float food_x = 146;
	float food_y = 37;
	float food_h = 10;
	float food_w = 10;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool exiting = false;
	bool menu = false;
	int maze[20][20];
	int dir = 0;
	int coly[20][20] = {0};

#pragma region "Maze Init"
	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			maze[row][col] = true;
		}
	}

	int row = 1;
	while (1)
	{
		for (int col = 0; col < 3; col++)
		{
			maze[1][col] = false;
		}
		for (int col = 4; col < 16; col++)
		{
			maze[1][col] = false;
		}
		for (int col = 17; col < 20; col++)
		{
			maze[1][col] = false;
		}
		row = row + 14;
		if (row > 15)
			break;
	}

	int col = 4;
	while (1)
	{
		for (int row = 2; row < 16; row++)
		{
			maze[row][col] = false;
		}

		col = col + 11;
		if (col > 15)
			break;
	}

	for (int col = 2; col < 8; col++)
	{
		maze[3][col] = false;
	}
	for (int col = 12; col < 18; col++)
	{
		maze[3][col] = false;
	}

	col = 1;
	while (1)
	{
		for (int row = 3; row < 7; row++)
		{
			maze[row][col] = false;
		}

		col = col + 17;
		if (col > 18)
			break;
	}

	for (col = 7; col < 13; col++)
	{
		maze[4][col] = false;
	}

	row = 6;
	while (1)
	{
		for (int col = 2; col < 18; col++)
		{
			maze[row][col] = false;
		}

		row = row + 5;
		if (row > 11)
			break;
	}

	col = 2;
	while (1)
	{
		for (int row = 7; row < 16; row++)
		{
			maze[row][col] = false;
		}

		col = col + 15;
		if (col > 17)
			break;
	}

	maze[7][9] = false;
	maze[7][10] = false;

	col = 0;
	while (1)
	{
		for (int row = 10; row < 14; row++)
		{
			maze[row][col] = false;
		}

		col = col + 19;
		if (col > 19)
			break;
	}

	for (int col = 6; col < 14; col++)
	{
		maze[13][col] = false;
	}

	col = 1;
	while (1)
	{
		for (row = 16; row < 18; row++)
		{
			maze[row][col] = false;
		}

		col = col + 17;
		if (col > 18)
			break;
	}

	for (int col = 5; col < 8; col++)
	{
		maze[17][col] = false;
	}
	for (int col = 12; col < 15; col++)
	{
		maze[17][col] = false;
	}

	for (col = 1; col < 6; col++)
	{
		maze[18][col] = false;
	}
	for (col = 7; col < 13; col++)
	{
		maze[18][col] = false;
	}
	for (col = 14; col < 19; col++)
	{
		maze[18][col] = false;
	}

	maze[2][2] = false;
	maze[2][17] = false;
	maze[7][9] = false;
	maze[7][10] = false;
	maze[12][6] = false;
	maze[12][13] = false;
	maze[16][5] = false;
	maze[16][14] = false;
	maze[16][2] = false;
	maze[16][4] = false;
	maze[16][17] = false;
	maze[16][15] = false;
	maze[1][0] = true;
	maze[1][19] = true;
	maze[1][1] = true;
	maze[1][18] = true;
	maze[1][2] = true;
	maze[1][17] = true;
	maze[2][2] = true;
	maze[2][17] = true;


	for (int row = 8; row < 10; row++)
	{
		for (int col = 6; col < 14; col++)
		{
			maze[row][col] = false;
		}
	}
#pragma endregion

	enum MYKEYS 
	{
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
	};
	pac game;

	game.setpacmanx(bouncer_x);
	game.setpacmany(bouncer_y);
	game.initpacsize();

	ALLEGRO_DISPLAY *display = NULL;			
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *wall1 = NULL;
	ALLEGRO_BITMAP *food = NULL;
	ALLEGRO_BITMAP *wall2[20][20] = {NULL};
	ALLEGRO_BITMAP *ghostb = NULL;
	ALLEGRO_BITMAP *ghostg = NULL;
	ALLEGRO_BITMAP *ghostr = NULL;
	ALLEGRO_BITMAP *ghostp = NULL;
	ALLEGRO_COLOR color;

#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "System Protection" 
	
	// Begining Initialization
	// Checks if Allegro is initialized
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	//Checks if keyboard is initialized
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	//Checks if mouse is initialized
	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	//Intializes timer to fps and then checks if there is a timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	//checks if there is a display
	display = al_create_display(screenw , screenh);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	al_init_primitives_addon();
	
	ALLEGRO_FONT *font = al_load_ttf_font("DroidSans.ttf", 23, 0);
	ALLEGRO_FONT *font2 = al_load_ttf_font("DroidSans.ttf", 12, 0);

	if (!font){
		fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
		return -1;
	}

	bouncer = al_create_bitmap(bounce,bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	ghostb = al_create_bitmap(bounce,bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	ghostg = al_create_bitmap(bounce,bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	ghostr = al_create_bitmap(bounce,bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	ghostp = al_create_bitmap(bounce,bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	wall1 = al_create_bitmap(wall1_w, wall1_h);
	if (!wall1) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	food = al_create_bitmap(food_w, food_h);
	if (!food) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					wall2[col][row] = al_create_bitmap(wall1_w,wall1_w);

					al_set_target_bitmap(wall2[col][row]);

					al_clear_to_color(al_map_rgb(0, 0, 255));

					al_set_target_bitmap(al_get_backbuffer(display));
				}
			}



	al_init_image_addon();


	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	

	al_set_target_bitmap(food);

	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(255, 255, 0));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(ghostb);

	al_clear_to_color(al_map_rgb(0, 150, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(ghostr);

	al_clear_to_color(al_map_rgb(255, 0, 0));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(ghostg);

	al_clear_to_color(al_map_rgb(0, 255, 0));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(ghostp);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	al_set_target_bitmap(wall1);

	al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Event Initialization"
	al_register_event_source(event_queue, al_get_display_event_source(display));  //display event handler
	al_register_event_source(event_queue, al_get_timer_event_source(timer));   //time envent handler
	al_register_event_source(event_queue, al_get_keyboard_event_source());   //keyboard event handler
	al_register_event_source(event_queue, al_get_mouse_event_source());  //mouse event handler
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);
#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Simple Menu"
	while (!menu)
	{
		ALLEGRO_EVENT ev;
		al_install_audio();
		al_reserve_samples(1);
		ALLEGRO_SAMPLE *sample = al_load_sample("song.wav");
		ALLEGRO_SAMPLE_INSTANCE *songinstance;
		//songinstance = al_create_sample_instance(sample);
		//al_set_sample_instance_playmode(songinstance, ALLEGRO_PLAYMODE_ONCE);
		//al_attach_sample_instance_to_mixer(songinstance, al_get_default_mixer());
		al_wait_for_event(event_queue, &ev);
		al_install_mouse();
		al_init_image_addon();
		ALLEGRO_BITMAP *image = al_load_bitmap("Pacman.jpg"); 
		//al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		ALLEGRO_FONT *font24 = al_load_font("PAC-FONT.ttf", 35, 0);
		//ALLEGRO_BITMAP *title = al_load_bitmap("title.jpg"); 
		al_register_event_source(event_queue, al_get_mouse_event_source());

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) 
		{
			if (ev.mouse.button == 1 && ev.mouse.x > 500 && ev.mouse.x < 700 && ev.mouse.y > 525) 
				{
					menu = true;
					break;
				}
			else if(ev.mouse.button == 1 && ev.mouse.x > 500 && ev.mouse.y < 475 && ev.mouse.y > 425 )
			{
				al_show_native_message_box(NULL, "Credits", "Created by:", "Anuraag Shankar, Ronit Sharma, and Sahana Premkumar", NULL, NULL);
					
			}
			else if(ev.mouse.button == 1 && ev.mouse.x > 500 && ev.mouse.y < 420 )
			{
				al_show_native_message_box(NULL, "Controls", "Movement- Arrow Keys", "Objective: Avoid ghosts and collect maximum pellets", NULL, NULL);
					
			}
			
		}
		
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
		


		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_init_primitives_addon();
			
			al_init_acodec_addon();
			
			//al_play_sample(sample, 255, 0, 2000, ALLEGRO_PLAYMODE_ONCE, 0);
			al_draw_text(font24, al_map_rgb(255, 255, 255), 420, 150, 0, "Pacman: The Game");
			//al_draw_bitmap(title, 700, (50), NULL);
			al_draw_bitmap(image, 100, (100), NULL);
			al_draw_filled_rectangle(500,300,804,375, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(500,500,804,575, al_map_rgb(255, 0, 0));
			al_draw_filled_rectangle(500,400,804,475, al_map_rgb(255, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 650, 315, ALLEGRO_ALIGN_CENTRE, "Controls");
			al_draw_text(font, al_map_rgb(255, 255, 255), 650, 525, ALLEGRO_ALIGN_CENTRE, "Click to play");
			al_draw_text(font, al_map_rgb(255, 255, 255), 650, 415, ALLEGRO_ALIGN_CENTRE, "Credits");

			

			al_flip_display();
		}

	}

#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Driver Program"

	while (!exiting)
	{

#pragma region "Timer Events"

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if(key[KEY_UP]  && game.getpacmany() >= 4.0 ) {
				for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					if(coly[row][col] !=2)
					{
						game.uppacman();
						dir = 1;
						
					}
				}
			}
			}

			if (key[KEY_DOWN] && game.getpacmany() <= screenh - bounce - 4.0 ) {

				for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					if(coly[row][col] != 4)
					{
						game.downpacman();
						dir = 2;
						
					}
				}
			}
			}

			if (key[KEY_LEFT] && game.getpacmanx() >= 4.0) {
				for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					if(coly[row][col] != 1)
					{
						game.leftpacman();
						dir = 3;
						
					}
				}
			}
			}

			if (key[KEY_RIGHT] && game.getpacmanx() <= screenw - bounce - 4.0) {
				for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					if(coly[row][col] != 3)
					{
						game.rightpacman();
						dir = 4;
						
					}
				}
			}
			}

			redraw = true;
		}

// "Closes the Window When Pressing X button"
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
#pragma endregion

#pragma region "Checks for when key was pressed down"
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
#pragma endregion 

#pragma region "Checks for when key was released"
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				exiting = true;
				break;

			case ALLEGRO_KEY_Q:
				exiting = true;
				break;

			//Full screen when f is pressed
			case ALLEGRO_KEY_F:
				if (screenw != disp_data.width)
				{
					al_set_new_display_flags(ALLEGRO_FULLSCREEN);
					display = al_create_display(disp_data.width, disp_data.height);
					screenw = disp_data.width;
					screenh = disp_data.height;
					wall1_x = 2 * (screenw / 10);
					wall1_y = (screenh / screenh) + 50 * (screenh / screenh);
				}
				
				break;

			//Normal screen when n is pressed
			case ALLEGRO_KEY_N:
				
					al_show_native_message_box(al_get_current_display(), 
                                 "THIS IS THE END", 
                                 "YOU LOST", 
                                 "Game Over",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
				break;
			
			case ALLEGRO_KEY_P:
					cout << "bx:" << (wall1_x + wall1_w + 13) - game.getpacmanx() << endl;
					cout << "by:" << (wall1_y + wall1_w + 13) - game.getpacmany() << endl;
					cout << "dx:" << (game.getpacmanx() + bounce) - wall1_x << endl;
					cout << "dy:" << (game.getpacmany() + bounce) - wall1_y << endl;
					cout << "dir:" << coly << endl;
					cout << "x:" << game.getpacmanx() << endl;
					cout << "y:" << game.getpacmany() << endl;
			}
		}

#pragma endregion

#pragma region "Redraw Objects"
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{

					if (maze[row][col] == 1)
					{
						al_draw_bitmap(wall1, wall1_x + col*30, wall1_y + row*30, 0);
					//	al_draw_bitmap(wall2[row][col], wall1_x + col*30, wall1_y + row*30, 0);
						coly[row][col] = game.collision(wall1_x + col*30,wall1_y + row*30,wall1_w + 13);
					}
					else
						al_draw_bitmap(food, food_x + col*30, food_y + row*30, 0);
				}
			}


			int x = game.getpacmanx();
			int y = game.getpacmany();

			color = al_map_rgb(255,200,0);

			//al_draw_bitmap(bouncer, game.getpacmanx(), game.getpacmany(), 0);
			al_draw_filled_circle(game.getpacmanx(),game.getpacmany(),13.0,color);
			al_draw_bitmap(ghostb,screenw/2, 63, 0);
			al_draw_bitmap(ghostr,screenw/2 - 20, 213, 0);
			al_draw_bitmap(ghostg,screenw/2 - 20, 363, 0);
			al_draw_bitmap(ghostp, screenw/2 - 246,500, 0);

#pragma region "TEST CODE"
			if(game.getpacmanx() - screenw/2 > 30 && game.getpacmanx() - screenw/2< 33)
			{
				al_show_native_message_box(al_get_current_display(), 
                                 "THIS IS THE END", 
                                 "YOU LOST", 
                                 "Game Over",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
			}

#pragma endregion

			al_draw_text(font2, al_map_rgb(255, 0, 0), screenw / 2, (screenh / screenh), ALLEGRO_ALIGN_CENTRE, "PAC-MAN VERSION 1.0");

			al_flip_display();
		}
#pragma endregion

	}

#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Destroyers"

	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(wall1);
		for (int row = 0; row < 20; row++) //display
			{
				for (int col = 0; col < 20; col++)
				{
					al_destroy_bitmap(wall2[row][col]);
				}
			}	
	al_destroy_bitmap(food);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
#pragma endregion

	return 0;
}