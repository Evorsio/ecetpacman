#include "Include.h"


int main(int argc, char **argv)
{

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Variable Initialization"
	
	const float FPS = 60;
	int screenw = 900;
	int screenh = 650;
	float bounce = 32;
	float bouncer_x = screenw / 2.0 - bounce / 2.0;
	float bouncer_y = screenh / 2.0 - bounce / 2.0;
	float wall1_x = 30.0;
	float wall1_y = 40.0;
	float wall1_w = 30.0;
	float wall1_h = 30.0;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool exiting = false;
	bool menu = false;
	enum MYKEYS 
	{
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
	};
	pac game;

	game.setpacmanx(bouncer_x);
	game.setpacmany(bouncer_y);


	ALLEGRO_DISPLAY *display = NULL;			
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *wall1 = NULL;

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

	ALLEGRO_FONT *font = al_load_ttf_font("DroidSans.ttf", 36, 0);
	ALLEGRO_FONT *font2 = al_load_ttf_font("DroidSans.ttf", 12, 0);

	if (!font){
		fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
		return -1;
	}

	bouncer = al_create_bitmap(bounce, bounce);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	wall1 = al_create_bitmap(wall1_w, wall1_h);
	if (!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_init_image_addon();


	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	

	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(255, 0, 0));

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
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					menu = true;
					break;
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(255, 255, 255));


			al_draw_text(font, al_map_rgb(0, 0, 0), screenw / 2, (screenh / 2), ALLEGRO_ALIGN_CENTRE, "Press Enter to Start");

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

			if(key[KEY_UP] && game.getpacmany() >= 4.0) {
				game.uppacman();
			}

			if (key[KEY_DOWN] && game.getpacmany() <= screenh - bounce - 4.0) {
				game.downpacman();
			}

			if (key[KEY_LEFT] && game.getpacmanx() >= 4.0) {
				game.leftpacman();
			}

			if (key[KEY_RIGHT] && game.getpacmany() <= screenw - bounce - 4.0) {
				game.rightpacman();
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
				if (screenw != 640)
				{
					al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
					display = al_create_display(640, 480);
					screenw = 640;
					screenh = 480;
				}
				break;

			}
		}

#pragma endregion

#pragma region "Redraw Objects"
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(wall1, wall1_x, wall1_y, 0);

			al_draw_bitmap(bouncer, game.getpacmanx(), game.getpacmany(), 0);

			al_draw_text(font2, al_map_rgb(255, 0, 0), screenw / 2, (screenh / screenh), ALLEGRO_ALIGN_CENTRE, "Moving a Square");

			al_flip_display();
		}
#pragma endregion

	}

#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------
#pragma region "Destroyers"

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
#pragma endregion

	return 0;
}