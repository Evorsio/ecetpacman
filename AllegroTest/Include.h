#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>


class pac

{
private:
	float pacx;
	float pacy;

public:
	void playbutton();
	void setbutton();
	float getpacmanx();
	float getpacmany();
	void setpacmanx(float);
	void setpacmany(float);
	void uppacman();
	void downpacman();
	void rightpacman();
	void leftpacman();
	void ghost();
};