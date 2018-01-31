#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

namespace Framework
{
	class Point;
	/*	
		That might or even should be templated to make something matter, but I'm leaving it this 
		way for now.

		At first I didn't want to have it, but then it made the code more readable.

		I also tried to keep this as simple as I can, so some useful things are missing, like getting
		corner points (top-left, top-right etc)
	*/
	class Rectangle
	{
	private:
		// Acronyms
		float tlx, tly, brx, bry;
	public:
		Rectangle(float topLeftX, float topLeftY, float bottomRightX, float bottomRightY);
		Rectangle(Point pt, float width, float height);
		Rectangle(Point pt, int width, int height);

		// I wrote getters only for things I really needed
		float GetWidth()
		{
			return brx - tlx;
		}

		float GetHeight()
		{
			return bry - tly;
		}

		float GetTopLeftX()
		{
			return tlx;
		}

		float GetTopLeftY()
		{
			return tly;
		}
	};
}

#endif