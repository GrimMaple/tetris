#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <Windows.h>
#include <gl\GL.h>

namespace Framework
{
	/*
		This is the very base component of the entire "engine".
		This class contains some virtual methods, thus it's meant to be inherited and used in a subclass

		This class creates a window, sets it up and sets rendering context. Rendering context might or should
		be moved to another class, but there were no need for that.
	*/
	class Window
	{
	private:
		// Some variables needed to initialaze window and OGL context
		HINSTANCE hInstance;
		HWND hWnd;
		HDC hDC;
		HGLRC hRC;
		MSG msg;

		// Window variables
		int width, height;
		bool created;
		int lastProcessTime;

		void UpdateRect();
		void Resize();
		void InitGL();

		void Begin();
		void End();

		// See cpp file for more detail
		static LRESULT WINAPI _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		// When this is set to false, the game loop will break
		bool shouldExit;

		// Indicates if fullscreen mode is on
		bool fullscreen;

		Window(int w, int h);
		void ToggleFullscreen();

		// Some virtual methods. They are called when needed.
		// Some of them do have empty body just to not make me override something I don't need
		virtual void Draw(int elapsed) = 0;
		virtual void Update(int elapsed) = 0;
		virtual void KeyDown(int code);
		virtual void KeyUp(int code);
		virtual void OnResize()
		{

		}

	public:
		// Getters I needed. There should be more of them, but I left only the ones I really need
		HDC GetDC()
		{
			return hDC;
		}

		bool IsCreated()
		{
			return created;
		}

		int GetWidth()
		{
			return width;
		}

		int GetHeight()
		{
			return height;
		}

		void SetText(char *text);
		void Run();
	};
}

#endif