#include "Include.h"

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
	pacy -= 4.0;
}

void pac::downpacman()
{
	pacy += 4.0;
}

void pac::rightpacman()
{
	pacx += 4.0;
}

void pac::leftpacman()
{
	pacx -= 4.0;
}