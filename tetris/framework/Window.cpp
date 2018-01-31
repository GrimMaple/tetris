#include "Window.h"
namespace Framework
{
	/*
		Dummy WndProc just to handle window creation.

		Because of how C++ works, we can't have a non-static callback, which is sad.
		But this little trick helps getting actual class, so we can change it inside the
		"real" WndProc. And because this function is an actual member of Window class we
		can acces a private method.
		The trick is to put a pointer to Window class into lpCreateParams when creating a
		window and then put it into GWL_USERDATA section of the window so it can be accesed
		later on.
	*/
	LRESULT WINAPI Window::_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// If we need to create a window
		if (uMsg == WM_CREATE)
		{
			// Insert pointer to class into GWL_USERDATA
			Window *base = (Window*)((CREATESTRUCT*)(lParam))->lpCreateParams;
			SetWindowLong(hWnd, GWL_USERDATA, (long)base);
		}
		// Try getting our window
		Window* pWindow = (Window*)GetWindowLong(hWnd, GWL_USERDATA);
		if (pWindow == NULL)
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		return pWindow->WndProc(hWnd, uMsg, wParam, lParam);
	}


	/*
		Real WndProc for the window.

		This function is non-static, so we can freely acces any class data we want to
	*/
	LRESULT Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_SIZE:
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			Resize();
			return 0;
		case WM_KEYDOWN:
			KeyDown(wParam);
			return 0;
		case WM_KEYUP:
			KeyUp(wParam);
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	Window::Window(int w, int h)
	{
		width = w;
		height = h;
		shouldExit = fullscreen =false;

		InitGL();
	}


	/*
		Toggles fullscreen.

		The method used is "Fullscreen windowed" because it works better when you have two monitors, and I do.
	*/
	void Window::ToggleFullscreen()
	{
		if (fullscreen)
		{
			// When going to windowed mode, restore border
			fullscreen = false;
			SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
			SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);

			// Resize window so it will fit the screen. Using system commands
			SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			return;
		}

		// When going to fullscreen mode remove some styles to make the window borderless
		fullscreen = true;
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
		SetWindowLong(hWnd, GWL_EXSTYLE, 0);

		// And of course just maximize the window because getting actual display size is boring
		SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}

	/*
		This just updates window width and height
	*/
	void Window::UpdateRect()
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;

		// Prevent window from having 0 size, this may lead to division by zero
		if (!height)
			height = 1;
		if (!width)
			width = 1;
	}

	void Window::Resize()
	{
		UpdateRect();

		glViewport(0, 0, width, height);

		glClearColor(0, 0, 0, 1.0f);
		glClearDepth(0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, 0, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Don't forget to call OnResize so subclass can do something on resize
		OnResize();
	}

	// Gawd Grim this is just too long. Do something
	void Window::InitGL()
	{
		WNDCLASSEX            wc;
		RECT                  rc;
		DWORD                 exStyle;
		DWORD                 style;
		PIXELFORMATDESCRIPTOR pfd;
		UINT                  pixelFormat;

		hInstance = GetModuleHandle(NULL);

		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = _WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_HAND);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "OpenGLWND";
		if (!RegisterClassEx(&wc))
			return;

		style = WS_OVERLAPPEDWINDOW;
		exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

		rc.left = 0;
		rc.right = width;
		rc.top = 0;
		rc.bottom = height;
		AdjustWindowRectEx(&rc, style, 0, exStyle);

		hWnd = CreateWindow("OpenGLWND", "TREE",
			style,
			100, 100,
			rc.right - rc.left,
			rc.bottom - rc.top,
			NULL, NULL, hInstance, this);
		if (!hWnd)
		{
			MessageBox(NULL, "Some foolscreen happend", "Error", MB_ICONERROR);
			return;
		}

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cRedBits = 0;
		pfd.cRedShift = 0;
		pfd.cGreenBits = 0;
		pfd.cGreenShift = 0;
		pfd.cBlueBits = 0;
		pfd.cBlueShift = 0;
		pfd.cAlphaBits = 0;
		pfd.cAlphaShift = 0;
		pfd.cAccumBits = 0;
		pfd.cAccumRedBits = 0;
		pfd.cAccumGreenBits = 0;
		pfd.cAccumBlueBits = 0;
		pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 0;
		pfd.cAuxBuffers = 0;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.bReserved = 0;
		pfd.dwLayerMask = 0;
		pfd.dwVisibleMask = 0;
		pfd.dwDamageMask = 0;

		if (!(hDC = ::GetDC(hWnd)))
			return;

		if (!(pixelFormat = ChoosePixelFormat(hDC, &pfd)))
			return;

		if (!(SetPixelFormat(hDC, pixelFormat, &pfd)))
			return;

		if (!(hRC = wglCreateContext(hDC)))
			return;

		if (!wglMakeCurrent(hDC, hRC))
			return;

		ShowWindow(hWnd, SW_SHOWNORMAL);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);

		Resize();

		created = true;

		return;
	}

	/*
		Begin rendering process. Clear screen for example
	*/
	void Window::Begin()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
	}

	/*
		End rendering process by swapping buffers
	*/
	void Window::End()
	{
		SwapBuffers(hDC);
	}

	/*
		The main game loop. Handles messages, handles drawing and handles updating 
	*/
	void Window::Run()
	{
		lastProcessTime = timeGetTime();

		while (!shouldExit)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Count elapsed time and pass it to Draw and Update functions
				int currentTime = timeGetTime();
				Update(currentTime - lastProcessTime);
				Begin();
				Draw(currentTime - lastProcessTime);
				End();
				lastProcessTime = currentTime;
			}
		}
	}

	void Window::SetText(char *text)
	{
		SetWindowText(hWnd, text);
	}

	void Window::KeyDown(int code)
	{

	}

	void Window::KeyUp(int code)
	{

	}
}