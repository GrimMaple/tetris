#include "Font.h"
#include "Window.h"
#include <stdio.h>

namespace Framework
{
	/*
		What this does is create a font using WinApi functions and then raster them into a call list.
	*/
	Font::Font(const char *name, Window *w)
	{
		HFONT font;
		base = glGenLists(96);
		font = CreateFont(-24, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, name);
		SelectObject(w->GetDC(), font);
		wglUseFontBitmaps(w->GetDC(), 32, 96, base);
	}

	/*
		This function draws formatted text onto screen at given position
	*/
	void Font::Draw(int x, int y, const char *fmt, ...)
	{
		// Unsafe as we can easily get out of bounds, but that won't happens as all the strings are limited in this project
		char text[256];
		va_list ap;
		if (!fmt)
			return;

		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);

		// Note that for this one we use glRasterPos2f instead of glTranslatef
		glRasterPos2f((GLfloat)x, (GLfloat)y);
		glColor3f(1.0f, 1.0f, 1.0f);
		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
		glPopAttrib();
		glLoadIdentity();
	}
}