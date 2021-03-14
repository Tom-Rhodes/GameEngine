
#include <GLFW_EngineCore.h>


#include "Game.h"

int main()
{
	GLFW_EngineCore* engineCore;

	engineCore = new GLFW_EngineCore;

	//Data type to store rectangle info
	RECT rect;
	//Fills the above rect with the window's dimensions
	GetWindowRect(GetDesktopWindow(), &rect);
	//Scales window to 3/4 of the size
	int width = ((rect.right - rect.left)*3/4);
	int height = ((rect.bottom - rect.top) * 3 / 4);
	
	//Attempts to initilise the window in the engine with the above window size
	if (!engineCore->initWindow(width, height, "Shapes - P16203335"))
		return -1;

	Game myFirstGame;
	//Runs the engine for the game
	engineCore->runEngine(myFirstGame);

	return 0;
}
