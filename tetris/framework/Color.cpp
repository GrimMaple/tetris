#include "Color.h"

namespace Framework
{
	Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{

	}

	Color::Color(int R, int G, int B, int A) : r((float)R/255.0f), g((float)G/255.0f), b((float)B/255.0f), a((float)A/255.0f)
	{

	}

	Color::Color(float R, float G, float B, float A) : r(R), g(G), b(B), a(A)
	{

	}
}