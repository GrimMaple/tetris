#ifndef _TETRIS_GAME_H_
#define _TETRIS_GAME_H_

#include "..\framework\Window.h"
#include "..\framework\RectangleBatch.h"
#include "..\framework\LinesBatch.h"
#include "..\framework\Font.h"

class Cup;
class Figure;
class Leaderboard;

/*
	The game handler.
*/
class TetrisGame : public Framework::Window
{
private:
	Framework::RectangleBatch *rectBatch;
	Framework::LinesBatch     *linesBatch;
	Framework::Font *font;

	Cup *cup;
	Figure *figure, *next;
	Leaderboard *leaderboard;

	// Game process variables
	int fx, fy;
	int totalElapsed;
	int maxElapsed;
	int score;
	int level;
	int state;

	// This is used for entering a name once you hit a hi-score
	char tmpName[25];
	int nameLen;

	void GenerateFigure();
	void DrawNext();
	void DrawScores();
	void SetLevel();
	void PerformGameInput(int code);
	void PerformEndInput(int code);
	void StartGame();
	void GameUpdate(int elapsed);
	void EndGame();
	void FigureDone();

protected:
	void Draw(int elapsed);
	void Update(int elapsed);
	void KeyDown(int code);
	void OnResize();
public:
	TetrisGame(int width, int height);
	~TetrisGame();
};

#endif