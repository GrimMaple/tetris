#ifndef _POINT_H_
#define _POINT_H_

namespace Framework
{
	/*
		Another helper class just to make some things better.

		It also lacks functionality, but I don't really need that functionality
	*/
	class Point
	{
	private:
		float x, y;
	public:
		Point(float X, float Y);
		Point(int X, int Y);
		
		float GetX()
		{
			return x;
		}

		float GetY()
		{
			return y;
		}
	};
}

#endif