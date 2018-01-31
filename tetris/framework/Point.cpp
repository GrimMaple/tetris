#include "Point.h"

namespace Framework
{
	Point::Point(float X, float Y) : x(X), y(Y)
	{

	}

	Point::Point(int X, int Y) : x((float)X), y((float)Y)
	{

	}
}