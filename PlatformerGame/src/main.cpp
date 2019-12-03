#include "Game.h"

static constexpr int SCRN_WIDTH{ 800 };
static constexpr int SCRN_HEIGHT{ 600 };

int main()
{
	Game game(SCRN_WIDTH, SCRN_HEIGHT);

	game.Run();

	return 0;
}