#include "stdafx.h"
#include "windows.h"
int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Game* _game = new Game(800, 600);
	_game->MainLoop();

	return EXIT_SUCCESS;
}