#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

/*
	Handels hi-scores.

	Automatically generates scores.dat if it doesn't exist,
	Automatically saves when gets destroyed
*/
class Leaderboard
{
private:
	// A better way of storing hi-scores is having a structure, but that's not really needed for such a small project
	int scores[10];
	char *names[10];

	void Create();
	void Load();
public:
	char* GetName(int i)
	{
		return names[i];
	}

	int GetScore(int i)
	{
		return scores[i];
	}

	void Save();
	void PostScore(int score, const char *name);
	bool IsHIScore(int score)
	{
		// We only need to check if score is higher than last place
		return score > scores[9];
	}
	Leaderboard();
	~Leaderboard();
};

#endif