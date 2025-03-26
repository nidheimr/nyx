#include "render.h"
#include "tools.h"

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <gl/GL.h>

struct _window
{
	int is_alive;

	HWND win32_handle;
	HDC device_context;
	HGLRC wgl_context;
};

//
//	private
//

LRESULT CALLBACK std_window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
		return 0;
	}

	return DefWindowProcA(hwnd, umsg, wparam, lparam);
}

HWND create_win32_window(const char* title, int width, int height)
{
	char* win32_class_name = "custom_window_prj";

	WNDCLASSEXA win32_class =
	{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = std_window_proc,
		.hInstance = GetModuleHandleA(NULL),
		.lpszClassName = win32_class_name
	};

	RegisterClassExA(&win32_class);

	HWND handle = CreateWindowExA(0, win32_class_name, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandleA(NULL), NULL);
	if (handle == NULL)
		return NULL;

	ShowWindow(handle, SW_NORMAL);

	return handle;
}

HGLRC create_wgl_context(HDC device_context)
{
	PIXELFORMATDESCRIPTOR desired_format =
	{
		.nSize = sizeof(PIXELFORMATDESCRIPTOR),
		.nVersion = 1,
		.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType = PFD_TYPE_RGBA,
		.cColorBits = 32,
		.cDepthBits = 24,
		.cStencilBits = 8,
		.iLayerType = PFD_MAIN_PLANE
	};

	int closest_format_index = ChoosePixelFormat(device_context, &desired_format);

	PIXELFORMATDESCRIPTOR acquired_format;
	DescribePixelFormat(device_context, closest_format_index, sizeof(acquired_format), &acquired_format);
	SetPixelFormat(device_context, closest_format_index, &acquired_format);

	HGLRC wgl_context = wglCreateContext(device_context);
	if (wgl_context == NULL)
		return NULL;

	wglMakeCurrent(device_context, wgl_context);

	return wgl_context;
}

//
//	public
//

window* window_new(const char* title, int width, int height)
{
	window* window = malloc(sizeof(struct _window));
	if (window == NULL)
	{
		error("failed to allocate a window");
		return NULL;
	}
	debug("allocated window");

	window->is_alive = 1;
	
	window->win32_handle = create_win32_window(title, width, height);
	if (window->win32_handle == NULL)
	{
		error("win32 failed to create a window");
		return NULL;
	}
	debug("created win32 window");

	window->device_context = GetDC(window->win32_handle);

	window->wgl_context = create_wgl_context(window->device_context);
	if (window->wgl_context == NULL)
	{
		error("wgl failed to create a context");
		return NULL;
	}
	debug("created wgl context");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, width, height);
		
	return window;
}

void window_destroy(window* window)
{
	wglMakeCurrent(window->device_context, NULL);
	wglDeleteContext(window->wgl_context);
	debug("destroyed wgl context");

	DestroyWindow(window->win32_handle);
	debug("destroyed win32 window");

	free(window);
	debug("deallocated window");
}

void window_update(window* window)
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			window->is_alive = 0;
			break;
		}

		DispatchMessageA(&msg);
	}

	glClear(GL_COLOR_BUFFER_BIT);
}

void window_render(window* window)
{
	SwapBuffers(window->device_context);
}

int window_should_close(window* window)
{
	return !window->is_alive;
}
