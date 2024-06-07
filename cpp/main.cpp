#include "game.h"
#include "general.h"
#include <iostream> 
#include <time.h> 

using std::srand;

void main()
{
	srand(time(0));
	ShowConsoleCursor(false);
	Game().run();
	gotoxy(0, 7);
}
