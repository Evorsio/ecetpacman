#include "Include.h"

void pac::initpacsize()
{
	pacsize = 25;
}

void pac::setpacmanx(float a)
{
	pacx = a;
}

void pac::setpacmany(float b)
{
	pacy = b;
}

float pac::getpacmanx()
{
	return pacx;
}

float pac::getpacmany()
{
	return pacy;
}

void pac::uppacman()
{
	pacy -= .005;
}

void pac::downpacman()
{
	pacy += .005;
}

void pac::rightpacman()
{
	pacx += .005;
}

void pac::leftpacman()
{
	pacx -= .005;
}

int pac::collision( int b2_x, int b2_y, int b2_s)
{

    if ( ((b2_x + b2_s) - pacx > 0  && (b2_x + b2_s) - pacx < 3 )
		|| ((b2_y + b2_s) - pacy > 0 && (b2_y + b2_s) - pacy < 30)
		|| ((pacx + pacsize) - b2_x > 30 && (pacx + pacsize) - b2_x  < 60)
		|| ((pacy + pacsize) - b2_y > 30 && (pacy + pacsize) - b2_y < 60) 
		)
	{

	if((b2_x + b2_s) - pacx > 0  && (b2_x + b2_s) - pacx < 3  
		&& (b2_y + b2_s) - pacy > 0 && (b2_y + b2_s) - pacy < 30) // is b1 under b2?
		{
			return 1;
		}
	if((b2_y + b2_s) - pacy > 0 && (b2_y + b2_s) - pacy < 30 
		&& (b2_x + b2_s) - pacx > 0  && (b2_x + b2_s) - pacx < 30) // is b1 under b2?
		{
			return 2;
		}
	if((pacx + pacsize) - b2_x > 10 && (pacx + pacsize) - b2_x  < 12 
		&& (pacy + pacsize) - b2_y > 30 && (pacy + pacsize) - b2_y < 60
		) // is b2 on the right side of b1?
		{
			return 3;
		}
	if((pacx + pacsize) - b2_x > 30 && (pacx + pacsize) - b2_x  < 60 
		&& (pacy + pacsize) - b2_y > 11 && (pacy + pacsize) - b2_y < 13)  // is b2 under b1?
		{
			return 4;
		}

	}
	}
 