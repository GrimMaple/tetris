#include <Windows.h>
#include <gl\GL.h>

#include "Renderer.h"
namespace Framework
{
	/*
		Draws an array, becuase glBegin/glEnd is slow.

		Techincally, vertex arrays are 1.5 times faster on my PC, I counted that. This might
		be better / worse on other PCs, but it sure is faster.
	*/
	void Renderer::DrawArray(void *vertex, void *color, size_t size, unsigned int mode)
	{
		// Get an actual drawing mode in GLenums
		GLenum md;
		switch (mode)
		{
		case DrawModeSquares:
			md = GL_QUADS;
			break;
		case DrawModeLines:
			md = GL_LINES;
			break;
		}

		// Using 4 components for color just so I can make things transparent
		glVertexPointer(3, GL_FLOAT, 0, vertex);
		glColorPointer(4, GL_FLOAT, 0, color);
		glDrawArrays(md, 0, size);
	}
}