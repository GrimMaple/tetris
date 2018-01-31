#include "Rectangle.h"
#include "Point.h"
namespace Framework
{
	Rectangle::Rectangle(float topLeftX, float topLeftY, float bottomRightX, float bottomRightY)
	{
		tly = topLeftY;
		tlx = topLeftX;
		bry = bottomRightY;
		brx = bottomRightX;
	}

	Rectangle::Rectangle(Point pt, float width, float height)
	{
		tly = pt.GetY();
		tlx = pt.GetX();
		bry = pt.GetY() + height;
		brx = pt.GetX() + width;
	}

	Rectangle::Rectangle(Point pt, int width, int height) : Rectangle(pt, (float)width, (float)height)
	{

	}
}