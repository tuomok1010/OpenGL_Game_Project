#include "Game.h"

static constexpr int SCRN_WIDTH{ 800 };
static constexpr int SCRN_HEIGHT{ 600 };

/*
	There is a crash at the end of the program. Probably due to shallow copying somewhere. TODO find and fix!!!
*/

int main()
{
	Game game(SCRN_WIDTH, SCRN_HEIGHT);

	game.Run();

	return 0;
}