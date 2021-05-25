#include <Windows.h>
#include <cmath>
#include <algorithm>

struct Vect2 {
	int x, y;
};
bool globalRunning = true;


struct Bitmap {
	BITMAPINFO info;
	int width, height;
	void* memory;
};

Bitmap globalBuffer;

int Clamp(int current, int min, int max) {
	return current < min ? min : current > max ? max : current;
}
void drawRect(Vect2 v1,Vect2 v2, unsigned int color) {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory + v1.y * globalBuffer.height + v1.x;
		
	for (int y = v1.y; y < v2.y; y++) {
		for (int x = v1.x; x < v2.x; x++) {
			*pixel++ = color;
		}
		pixel += globalBuffer.width-(v2.x-v1.x);
	}
}
void clrScr() {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory;

	for (int y = 0; y < globalBuffer.height; y++) {
		for (int x = 0; x <globalBuffer.width; x++) {
			*pixel++ = 0;
		}
	}
}
inline void drawPixel(int x, int y, unsigned int color) {
	*((unsigned int*)globalBuffer.memory + y * globalBuffer.width + x)= color;
}
void drawDDALine(Vect2 v1, Vect2 v2, unsigned int color)
{
	int dx, dy, steps;
	float xincr, yincr, x, y;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;

	if (abs(dx) >= abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	xincr = (float)dx / steps;
	yincr = (float)dy / steps;

	x = v1.x;
	y = v1.y;

	for (int k = 1; k <= steps; k++)
	{
		drawPixel((int)(x+0.5f),(int)(y+0.5f),color);
		x += xincr;
		y += yincr;
	}
}
void drawBresLine(Vect2 v1, Vect2 v2,unsigned int color) {
	
	//Bresengham's Algorithm
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = v2.x - v1.x;
	dy = v2.y - v1.y;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (v2.x < v1.x) incx = -1;
	incy = 1;
	if (v2.y< v1.y) incy = -1;
	x = v1.x; y = v1.y;
	if (dx > dy) {
		drawPixel(x, y, color);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			drawPixel(x, y,color);
		}

	}
	else {
		drawPixel(x, y,color);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			drawPixel(x, y,color);
		}
	}
}
LRESULT CALLBACK WindowProc(HWND window_handle, unsigned int message, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_DESTROY:
	case WM_QUIT:
	{
		globalRunning = false;
	}break;
	default:
		result = DefWindowProc(window_handle, message, w_param, l_param);
	}

	return result;
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {
	WNDCLASS wndclass = {};
	wndclass.style= CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance=hInstance;
	wndclass.lpszMenuName=L"HelloThere";
	wndclass.lpszClassName=L"ButGoodbye";

	globalBuffer.height = 720;
	globalBuffer.width = 1280;

	globalBuffer.info.bmiHeader = {};
	globalBuffer.info.bmiHeader.biSize=sizeof(globalBuffer.info.bmiHeader);
	globalBuffer.info.bmiHeader.biWidth=1280;
	globalBuffer.info.bmiHeader.biHeight=-720;
	globalBuffer.info.bmiHeader.biPlanes=1;
	globalBuffer.info.bmiHeader.biBitCount=32;
	globalBuffer.info.bmiHeader.biCompression=BI_RGB;

	globalBuffer.memory = VirtualAlloc(0, globalBuffer.width * globalBuffer.height * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (RegisterClass(&wndclass)) {
		HWND window_handle = CreateWindowEx(0, wndclass.lpszClassName, L"Hello69", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
			0, 0, hInstance, 0);
		if (window_handle) {
			globalRunning = true;
			MSG message;
			HDC deviceContext = GetDC(window_handle);

			while (globalRunning)
			{
				while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&message);
					DispatchMessageA(&message);
				}

				Vect2 v1 = { 50,100 };
				Vect2 v2 = { 500, 500 };

				POINT mousePoint;
				GetCursorPos(&mousePoint);
				ScreenToClient(window_handle, &mousePoint);

				Vect2 v3 = { Clamp(mousePoint.x,0,globalBuffer.width),Clamp(mousePoint.y,0,globalBuffer.height)};
				Vect2 v4 = { 500, 500 };

				clrScr();
				drawBresLine(v1, v2, 0xFF0000);
				drawDDALine(v4, v3, 0x00FF00);

				StretchDIBits(deviceContext, 0, 0, globalBuffer.width, globalBuffer.height,
					0, 0, globalBuffer.width, globalBuffer.height, globalBuffer.memory, &globalBuffer.info, DIB_RGB_COLORS, SRCCOPY);
			}
		}
	}
	return 0;
};