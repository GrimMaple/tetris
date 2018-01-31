#include "game\TetrisGame.h"


/*
	The entry point. I like to make it look clear and small, so pretty much everything is covered inside other classes.
*/
void main()
{
	// All I have to do is make a TetrisGame and then Run() it!
	TetrisGame *game = new TetrisGame(800, 600);
	game->Run();

	// Don't forget to clean up tho
	delete game;
}