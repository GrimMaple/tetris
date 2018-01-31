#ifndef _RENDERER_H_
#define _RENDERER_H_

namespace Framework
{
	/* 
		To pick a better way of drawing stuff. Should contain two more things, but I don't need them
		in this simple OGL game.
		The main idea of this is to not force other classes including GL.h
	 */
	enum DrawModes
	{
		DrawModeSquares,
		DrawModeLines
	};


	/*
		Just a static class to help render things. The idea is taken from my C# engine and I believe
		there might be a better way of doing this
	*/
	class Renderer
	{
	public:
		static void DrawArray(void *vertex, void *color, size_t size, unsigned int mode);
	};
}
#endif