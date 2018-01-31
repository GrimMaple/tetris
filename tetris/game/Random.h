#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <stdlib.h>
#include <time.h>

/*
	Little static helper-class to deal with RNG nicely.

	It lacks a useful function Next(int min, int max) but I didn't need that
*/
class Random
{
public:
	static void Init()
	{
		srand((unsigned int)time(NULL));
	}

	static int Next(int max)
	{
		return rand() % max;
	}
};

#endif