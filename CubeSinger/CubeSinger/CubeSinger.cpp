// CubeSinger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "GraphicModule.h"
#include "SoundModule.h"

using namespace irrklang;
using namespace std;

int main(int argc, char **argv)
{
	thread alpha(AlphaThread, argc, argv);
	thread bravo(BravoThread, argc, argv);
	alpha.join();
	bravo.join();
}