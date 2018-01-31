#include "LinesBatch.h"
#include "Point.h"
#include "Color.h"
#include "Renderer.h"

namespace Framework
{
	LinesBatch::LinesBatch() : Batch(2000)
	{
		mode = DrawModeLines;
	}

	void LinesBatch::AddLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
	{
		AddPoint(x1, y1, r, g, b, a);
		AddPoint(x2, y2, r, g, b, a);
	}

	void LinesBatch::AddLine(Point pt1, Point pt2, float r, float g, float b, float a)
	{
		AddLine(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY(), r, g, b, a);
	}

	void LinesBatch::AddLine(Point pt1, Point pt2, Color color)
	{
		AddLine(pt1, pt2, color.R(), color.G(), color.B(), color.A());
	}
}