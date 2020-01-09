#include "pch.h"
#include "SoundModule.h"

#pragma comment(lib, "irrKlang.lib")
using namespace irrklang;

int BravoThread(int argc, char** argv)
{
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	engine->play2D("../media/The_Cave.wav", true);

	do
	{
		printf("Press any key to play some sound, press 'p' to stop.\n");

		// play a single sound
		engine->play2D("../media/explosion.wav");
	} while (_getch() != 'p');
	engine->drop();
	return 0;
}
