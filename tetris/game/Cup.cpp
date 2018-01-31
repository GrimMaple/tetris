#include "Cup.h"

#include "..\framework\Color.h"
#include "..\framework\Point.h"
#include "..\framework\Rectangle.h"

#include "Figure.h"

using namespace Framework;

// Static data about score added byu removing lines
const int scores[] = {0, 100, 300, 700, 1500};

Cup::Cup(Window *wnd)
{
	window = wnd;
	CalculateSize();

	// Color has a default ctor that makes it white, so no need to fill colors[0]
	colors[1] = Color(255, 0, 0, 255);
	colors[2] = Color(0, 255, 0, 255);
	colors[3] = Color(0, 0, 255, 255);
	colors[4] = Color(0, 255, 255, 255);
	colors[5] = Color(255, 100, 0, 255);
	colors[6] = Color(255, 255, 0, 255);
	Reset();
}

int Cup::MaxColors()
{
	return sizeof(colors) / sizeof(Color);
}

void Cup::Reset()
{
	// This works because -1 is 0xFF and 0xFFFFFFFF is -1 in int
	memset(field, -1, sizeof(field));
}


/*
	Calculate appropriate square size so the cup can be automatically placed in the middle of the window
*/
void Cup::CalculateSize()
{
	squareSize = (window->GetHeight() - 1) / 20;
	if (squareSize > maxSize)
		squareSize = maxSize;
}

/*
	Draws self
*/
void Cup::Draw(Framework::LinesBatch *lines, Framework::RectangleBatch *rectangles)
{
	// Those are coordinates of top-left corner of the cup
	int x = window->GetWidth() / 2 - squareSize * 4 - squareSize / 2;
	int y = window->GetHeight() / 2 - 10 * squareSize;


	// Abit hardcoded, using constants is a better way.
	// Also, I know that color[0] is white, so I'm exploiting that
	// Adding / subtracting 1 from coordinate makes it look better so squares wont be drawn in front of lines
	lines->AddLine(Point(x, y-1), Point(x, y + squareSize * 20), colors[0]);
	lines->AddLine(Point(x, y + squareSize * 20), Point(x + squareSize * 10 + 1, y + squareSize * 20), colors[0]);
	lines->AddLine(Point(x + squareSize * 10 + 1, y + squareSize * 20), Point(x + squareSize * 10 + 1, y-1), colors[0]);
	lines->AddLine(Point(x + squareSize * 10 + 1, y-1), Point(x, y), colors[0]);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
		{
			// Don't want to draw nothing
			if (field[i][j]/* + j * 10]*/ == -1)
				continue;
			Framework::Rectangle r(Point(x + i*squareSize, y + j*squareSize), squareSize, squareSize);
			rectangles->DrawRectangle(r, colors[field[i][j]]);
		}
}

void Cup::DrawFigure(RectangleBatch *rectangles, Figure *figure, int x, int y)
{
	// Those are coordinates of top-left corner of the cup
	int sx = window->GetWidth() / 2 - squareSize * 4 - squareSize / 2;
	int sy = window->GetHeight() / 2 - 10 * squareSize;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			// Do not draw outside of cup
			if ((x + i) < 0 || (y + j) < 0)
				continue;
			// Do not draw nothing
			if (figure->GetData()[i + j * 4] == -1)
				continue;
			Framework::Rectangle r(Point(sx + (x + i)*squareSize, sy + (y + j)*squareSize), squareSize, squareSize);
			rectangles->DrawRectangle(r, colors[figure->GetData()[i + j * 4]]);
		}
}


/*
	Checks if figure can be moved to (x; y) coordinates in cup metrics
*/
bool Cup::MoveFigure(Figure *figure, int x, int y)
{
	// Fool-check
	if (y > 16 || x < 0 || x > 9)
		return false;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			// Ignore non-visible tiles
			if (figure->GetData()[i + j * 4] == -1)
				continue;
			// Do net check outside of cup
			if ((y + j) < 0)
				continue;
			// If figure is outside of the cup, return false
			if ((x + i) > 9 && figure->GetData()[i + j * 4] != -1)
				return false;
			// If figure would intersect any of the already placed squares, return false
			if (field[x + i][y+j] != -1 && figure->GetData()[i + j * 4] != -1)
				return false;
		}

	return true;
}

/*
	Checks if figure can be rotated in given coordinates
*/
bool Cup::CanRotate(Figure *figure, int x, int y)
{
	// Make a clone, rotate it and see if that works
	Figure *temp = new Figure(figure->CurrentType(), figure->CurrentColor(), figure->CurrentRotation());
	temp->Rotate();
	bool result = MoveFigure(temp, x, y);
	delete temp;
	return result;
}

/*
	Places figure at given coordinates.

	Returns ammount of points gained by this move
*/
int Cup::PlaceFigure(Figure *figure, int x, int y)
{

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			// DO NOT PLACE IN THE MIDDLE OF NOWHERE
			if (y + j < 0)
				continue;
			// Do not rewrite already occupied tiles with nothing
			if (figure->GetData()[i + j * 4] == -1)
				continue;
			field[x + i][y + j] = figure->GetData()[i + j * 4];
		}

	return Update();
}

/*
	Checks for completed lines and returns total score for them
*/
int Cup::Update()
{
	int times = 0;

	for (int i = 0; i < 20; i++)
	{
		// Check if i-th line is completed
		bool res = true;
		for (int j = 0; j < 10; j++)
		{
			if (field[j][i] == -1)
			{
				res = false;
				break;
			}
		}
		// Shift stuff down if completed
		if (res)
		{
			times++;
			for (int t = i; t >0; t--)
				for (int j = 0; j < 10; j++)
				{
					field[j][t] = field[j][t - 1];
					//field[t * 10 + j] = -1;
				}
		}
	}

	return scores[times];
}