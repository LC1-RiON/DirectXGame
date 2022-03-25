#include "OurUniqueGame.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Framework* game = new OurUniqueGame();

    game->Run();

    delete game;

	return 0;
}