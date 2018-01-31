#ifndef _CUP_H_
#define _CUP_H_

#include "..\framework\LinesBatch.h"
#include "..\framework\RectangleBatch.h"
#include "..\framework\Window.h"
#include "..\framework\Color.h"

class Figure;

/*
	Represents a 10*20 cup.

	Handels self-draw, drawing a tetramino figure inside itself and "physics"
*/
class Cup
{
private:
	Framework::Window *window;
	// Current square size and maximum square size to draw
	int squareSize;
	const int maxSize = 64;

	// Cup "field". -1 is free, anything else is not free
	int field[10][20];

	// All possible figure colors
	Framework::Color colors[7];

public:
	int MaxColors();
	Cup(Framework::Window *wnd);
	void CalculateSize();
	void Draw(Framework::LinesBatch *lines, Framework::RectangleBatch *rectangles);
	void DrawFigure(Framework::RectangleBatch *rectangles, Figure *f, int x, int y);
	bool MoveFigure(Figure *figure, int x, int y);
	int PlaceFigure(Figure *figure, int x, int y);
	bool CanRotate(Figure *figure, int x, int y);
	int Update();
	void Reset();

	Framework::Color ColorID(int id)
	{
		return colors[id];
	}

	int SquareSize()
	{
		return squareSize;
	}
};

#endif 