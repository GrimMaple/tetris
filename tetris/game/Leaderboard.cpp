#include "Leaderboard.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

// Static hi-score data

// Hi-score names
const char defaultNames[10][25] = {
	"Ben",
	"Toshi",
	"Zetsubou",
	"Roku",
	"Jay",
	"Shiroi",
	"Kris",
	"Cartman",
	"Maple",
	"Grim"
};

// Hi-score scores
const int defaultScores[] = {
	100000,
	50000,
	20000,
	10000,
	8000,
	6000,
	3000,
	2000,
	1000,
	500
};

Leaderboard::Leaderboard()
{
	for (int i = 0; i < 10; i++)
	{
		names[i] = new char[25];
		memset(names[i], 0, 25);
	}
	Load();
}

void Leaderboard::Load()
{
	// If we cannot open scores.dat then create it and try again
	FILE *f = fopen("scores.dat", "rb");
	if (f == NULL)
	{
		// This might lead to stack overflow and can be rewritten in a safier way.
		// Stack overflow is a realy rare scenario tho, it might be possible if user doesn't
		// have acces to directory from which he runs the game
		Create();
		Load();
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		fread(names[i], sizeof(char), 25, f);
		fread(&scores[i], sizeof(int), 1, f);
	}

	fclose(f);
}

void Leaderboard::Create()
{
	FILE *f = fopen("scores.dat", "wb+");
	for (int i = 0; i < 10; i++)
	{
		fwrite(defaultNames[i], sizeof(char), 25, f);
		fwrite(&defaultScores[i], sizeof(int), 1, f);
	}

	fclose(f);
}

void Leaderboard::Save()
{
	FILE *f = fopen("scores.dat", "wb");
	for (int i = 0; i < 10; i++)
	{
		fwrite(names[i], sizeof(char), 25, f);
		fwrite(&scores[i], sizeof(int), 1, f);
	}
}

void Leaderboard::PostScore(int score, const char *name)
{
	for (int i = 0; i < 10; i++)
	{
		// Find out on which place posted score is
		if (scores[i] > score)
			continue;
		else
		{
			// Shift scores down
			for (int j=9; j > i; j--)
			{
				// Using strcpy as pointer magic isn't really appriciated by compiler and runtime
				strcpy(names[j], names[j - 1]);
				scores[j] = scores[j-1];
			}
			strcpy(names[i], name);
			scores[i] = score;
			break;
		}
	}
}

Leaderboard::~Leaderboard()
{
	// Save just to be sure
	Save();

	for (int i = 0; i < 10; i++)
		delete names[i];
}