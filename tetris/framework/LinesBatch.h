#ifndef _LINES_BATCH_H_
#define _LINES_BATCH_H_

#include "Batch.h"

namespace Framework
{
	class Point;
	class Color;

	/*
		A lines batch.

		Handles drawing lines, obviously
	*/
	class LinesBatch : public Batch
	{
	public:
		LinesBatch();

		void AddLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
		void AddLine(Point pt1, Point pt2, float r, float g, float b, float a);
		void AddLine(Point pt1, Point pt2, Color color);
	};
}

#endif