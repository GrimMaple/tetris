#include "Rectangle.h"
#include "Color.h"
#include "RectangleBatch.h"

#include "Renderer.h"

namespace Framework
{

	RectangleBatch::RectangleBatch() : Batch(2000)
	{
		mode = DrawModeSquares;
	}

	void RectangleBatch::DrawRectangle(float x, float y, float w, float h, float r, float g, float b, float a)
	{
		AddPoint(x, y, r, g, b, a);
		AddPoint(x, y + h, r, g, b, a);
		AddPoint(x + w, y + h, r, g, b, a);
		AddPoint(x + w, y, r, g, b, a);
	}

	void RectangleBatch::DrawRectangle(Rectangle rect, float r, float g, float b, float a)
	{
		DrawRectangle(rect.GetTopLeftX(), rect.GetTopLeftY(), rect.GetWidth(), rect.GetHeight(), r, g, b, a);
	}

	void RectangleBatch::DrawRectangle(Rectangle rect, Color color)
	{
		DrawRectangle(rect, color.R(), color.G(), color.B(), color.A());
	}
}