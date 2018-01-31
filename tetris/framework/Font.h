#ifndef _FONT_H_
#define _FONT_H_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <stdarg.h>

namespace Framework
{

	class Window;

	/*
		A font class to draw text.

		Some of the stuff should be moved to another class just to not make this one include GL.h directly,
		but this was a faster way of doing it, so I went with this
	*/
	class Font
	{
	private:
		GLuint base;

	public:
		Font(const char *name, Window *w);
		void Draw(int x, int y, const char *fmt, ...);
	};
}

#endif