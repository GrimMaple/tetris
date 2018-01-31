#ifndef _COLOR_H_
#define _COLOR_H_

namespace Framework
{
	/*
		Represents a 32-bit color.

		I dind't want to write this one, but then it made things little bit fancier than they were.

		Didn't go crazy on making it functional and left it with stuff I needed
	*/
	class Color
	{
	private:
		float r, g, b, a;

	public:
		Color();
		Color(int R, int G, int B, int A);
		Color(float R, float G, float B, float A);

		float R()
		{
			return r;
		}
		float G()
		{
			return g;
		}
		float B()
		{
			return b;
		}
		float A()
		{
			return a;
		}
	};
}

#endif