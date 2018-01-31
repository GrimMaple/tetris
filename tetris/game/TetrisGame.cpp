#include "TetrisGame.h"
#include "..\framework\RectangleBatch.h"
#include "..\framework\Rectangle.h"
#include "..\framework\Color.h"
#include "..\framework\Point.h"
#include "Cup.h"
#include "Figure.h"
#include "Random.h"
#include "Leaderboard.h"

#include <stdio.h>

using namespace Framework;

// Static data about level goals
const int levelGoals[] = { 0, 1000, 5000, 10000, 20000, 40000, 70000, 100000, 200000 };

// Static data about dropping speed
const int levelSpeeds[] = { 2000, 1000, 700, 500, 350, 200, 100, 50, 30 };

/*
	Having two options basically: making a Scening mechanism and simply implementing a FSM
	I selected the second option as the first one would have taken more time. Besides, this 
	FSM isn't really that big and works well in this case.
*/
enum
{
	StateBefore,
	StateGame,
	StateEnd
};

TetrisGame::TetrisGame(int width, int height) : Window(width, height)
{
	rectBatch = new RectangleBatch();
	linesBatch = new LinesBatch();
	cup = new Cup(this);
	leaderboard = new Leaderboard();
	Random::Init();
	figure = 0, next = 0;
	score = 0;
	level = 0;
	state = StateBefore;
	SetText("Tetris");
	font = new Font("Arial", this);
	memset(tmpName, 0, sizeof(tmpName));
	nameLen = 0;
}

void TetrisGame::Update(int elapsed)
{
	// I only need to update when user is playing
	switch (state)
	{
	case StateGame:
		GameUpdate(elapsed);
		break;
	case StateEnd:
	case StateBefore:
		break;
	}
}

void TetrisGame::GameUpdate(int elapsed)
{
	// I only want to move figure down once in a certain ammount of time
	totalElapsed += elapsed;
	if (totalElapsed > maxElapsed)
	{
		// If figure cannot be moved any lower, place it
		if (cup->MoveFigure(figure, fx, fy + 1))
			fy++;
		else
			FigureDone();

		totalElapsed = 0;
	}
	SetLevel();
}

/*
	Sets difficulty based on current score
*/
void TetrisGame::SetLevel()
{
	int tmpLevel = 0;
	for (int i = 0; i < 10; i++)
	{
		if (score >= levelGoals[i])
			tmpLevel = i;
		else break;
	}

	maxElapsed = levelSpeeds[tmpLevel];
	level = tmpLevel;
}

void TetrisGame::GenerateFigure()
{
	// If next figure isn't yet generated, generate it first!
	if (!next)
	{
		int type = Random::Next(Figure::TotalFigures);
		next = new Figure(type, Random::Next(cup->MaxColors()), Random::Next(Figure::Rotations(type)));
	}

	// Free that figure we don't need anymore
	if (figure)
		delete figure;

	// Swap figures and generate new next figure
	figure = next;
	int type = Random::Next(Figure::TotalFigures);
	next = new Figure(type, Random::Next(cup->MaxColors()), Random::Next(Figure::Rotations(type)));
	fx = 5;
	fy = -3;

	// If figure cannot be placed at its initial position, game over
	if (!cup->MoveFigure(figure, fx, fy))
		EndGame();
}

void TetrisGame::Draw(int elapsed)
{
	Framework::Rectangle r(100, 100, 300, 300);
	Color color(255, 0, 0, 255);
	rectBatch->Begin();

	linesBatch->Begin();
	cup->Draw(linesBatch, rectBatch);
	DrawNext();
	switch (state)
	{
	case StateBefore:
		font->Draw(GetWidth() / 2 - 4*8 - 4, GetHeight() / 2, "Hit enter!");
		break;
	case StateGame:
		cup->DrawFigure(rectBatch, figure, fx, fy);
		break;
	case StateEnd:
		font->Draw(GetWidth() / 2 - 4*8 - 4, GetHeight() / 2, "Enter name");
		font->Draw(GetWidth() / 2 - strlen(tmpName) * 4, GetHeight() / 2 + 32, tmpName);
		break;
	}

	DrawScores();
	linesBatch->End();
	rectBatch->End();
}

void TetrisGame::OnResize()
{
	// On resize recalculate cup's dimensions
	cup->CalculateSize();
}

void TetrisGame::KeyDown(int code)
{
	if (code == VK_F2)
	{
		ToggleFullscreen();
	}
	switch (state)
	{
	case StateBefore:
		if (code == VK_RETURN)
		{
			StartGame();
		}
		if (code == VK_ESCAPE)
		{
			shouldExit = true;
		}
		break;
	case StateGame:
		PerformGameInput(code);
		break;
	case StateEnd:
		PerformEndInput(code);
		break;
	}
}

void TetrisGame::PerformEndInput(int code)
{
	if (isalnum(code) || code == ' ')
	{
		if (nameLen == 24)
			return;
		// Select lower/upper registers based on shift key state
		if (HIWORD(GetKeyState(VK_SHIFT)))
			tmpName[nameLen] = code;
		else
			tmpName[nameLen] = tolower(code);
		nameLen++;
	}
	if (code == VK_BACK)
	{
		nameLen--;
		nameLen = nameLen < 0 ? 0 : nameLen;
		tmpName[nameLen] = 0;
	}
	if (code == VK_RETURN)
	{
		// Do not allow empty names
		if (!nameLen)
			return;
		leaderboard->PostScore(score, tmpName);
		state = StateBefore;
	}
}

void TetrisGame::PerformGameInput(int code)
{
	if (code == VK_LEFT)
	{
		if (cup->MoveFigure(figure, fx - 1, fy))
			fx--;
	}

	if (code == VK_RIGHT)
	{
		if (cup->MoveFigure(figure, fx + 1, fy))
			fx++;
	}
	if (code == VK_DOWN)
	{
		if (cup->MoveFigure(figure, fx, fy + 1))
		{
			fy++;
		}
		else
		{
			FigureDone();
		}
	}
	if (code == VK_SPACE)
	{
		// Try moving figure to the left in attempts of rotating it
		for (int i = 0; i < 4; i++)
			if (cup->CanRotate(figure, fx - i, fy))
			{
				fx -= i;
				figure->Rotate();
				break;
			}
	}

	if (code == VK_ESCAPE)
	{
		EndGame();
	}
}

void TetrisGame::StartGame()
{
	fx = 5;
	fy = -3;
	level = 1;
	totalElapsed = 0;
	score = 0;
	GenerateFigure();
	state = StateGame;
}

void TetrisGame::EndGame()
{
	delete figure;
	delete next;
	figure = next = 0;
	cup->Reset();
	state = leaderboard->IsHIScore(score) ? StateEnd : StateBefore;
}

void TetrisGame::FigureDone()
{
	score += cup->PlaceFigure(figure, fx, fy);
	GenerateFigure();
}

void TetrisGame::DrawNext()
{
	int size = cup->SquareSize();

	// Coordinates of top-left corner of "next figure view"
	int x = GetWidth() - GetWidth() / 4;
	int y = GetHeight() / 4;

	Color white(255, 255, 255, 255);

	// Draws white border
	linesBatch->AddLine(Point(x, y-1), Point(x, y + size * 4), white);
	linesBatch->AddLine(Point(x, y + size * 4), Point(x + size * 4, y + size * 4), white);
	linesBatch->AddLine(Point(x + size * 4, y + size * 4), Point(x + size * 4, y-1), white);
	linesBatch->AddLine(Point(x + size * 4, y), Point(x, y-1), white);

	font->Draw(x, y + 4 * size + 32, "Score: %d", score);
	font->Draw(x, y + 4 * size + 64, "Level: %d", level + 1);

	// If next figure isn't present, nothing else to draw
	if (!next)
		return;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (next->GetData()[i + j * 4] == -1)
				continue;
			Framework::Rectangle r(Point(x + i*size, y + j*size), size, size);
			rectBatch->DrawRectangle(r, cup->ColorID(next->GetData()[i + j * 4]));
		}
}

void TetrisGame::DrawScores()
{
	int x = 10, y = GetHeight() / 2 - 32 * 4 - 16;
	for (int i = 0; i < 10; i++)
	{
		font->Draw(x, y + i * 32, "%s: %d", leaderboard->GetName(i), leaderboard->GetScore(i));
	}
}

TetrisGame::~TetrisGame()
{
	delete rectBatch;
	delete linesBatch;
	delete cup;
	delete figure;
	delete next;
	delete font;
	delete leaderboard;
}