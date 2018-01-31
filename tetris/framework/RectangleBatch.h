#ifndef _SQUARES_BATCH_H_
#define _SQUARES_BATCH_H_

#include "Batch.h"

namespace Framework
{
	class Rectangle;
	class Color;

	/*
		A batch of rectangles.

		Handles drawing rectangles, obvious
	*/
	class RectangleBatch : public Batch
	{
	public:
		RectangleBatch();
		void DrawRectangle(float x, float y, float w, float h, float r, float g, float b, float a);
		void DrawRectangle(Rectangle rect, float r, float g, float b, float a);
		void DrawRectangle(Rectangle rect, Color color);
	};
}
#endif 