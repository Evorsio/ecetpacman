#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


using namespace std;

class pac

{
private:
	float pacx;
	float pacy;
	float pacsize;

public:
	int maze[20][20];
	void playbutton();
	void setbutton();
	float getpacmanx();
	float getpacmany();
	void initpacsize();
	void setpacmanx(float);
	void setpacmany(float);
	void uppacman();
	void downpacman();
	void rightpacman();
	void leftpacman();
	void ghost();
	int direction(int, int , int, float [20][20]);
	void allegroinit();
	int collision(int,int,int);
};