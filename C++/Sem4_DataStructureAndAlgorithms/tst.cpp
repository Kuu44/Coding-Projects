#include <Windows.h>
#include <cmath>
#include <algorithm>
#include<iostream>
#include<string>

#define PI 3.14159265
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
void drawRect(Vect2 v1, Vect2 v2, unsigned int color) {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory + v1.y * globalBuffer.height + v1.x;

	for (int y = v1.y; y < v2.y; y++) {
		for (int x = v1.x; x < v2.x; x++) {
			*pixel++ = color;
		}
		pixel += globalBuffer.width - (v2.x - v1.x);
	}
}
void clrScr() {
	unsigned int* pixel = (unsigned int*)globalBuffer.memory;

	for (int y = 0; y < globalBuffer.height; y++) {
		for (int x = 0; x < globalBuffer.width; x++) {
			*pixel++ = 0;
		}
	}
}
inline void drawPixel(int x, int y, unsigned int color) {
	*((unsigned int*)globalBuffer.memory + y * globalBuffer.width + x) = color;
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
#pragma region Initializer

	WNDCLASS wndclass = {};
	wndclass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = L"HelloThere";
	wndclass.lpszClassName = L"ButGoodbye";

	globalBuffer.height = 720;
	globalBuffer.width = 1280;

	globalBuffer.info.bmiHeader = {};
	globalBuffer.info.bmiHeader.biSize = sizeof(globalBuffer.info.bmiHeader);
	globalBuffer.info.bmiHeader.biWidth = 1280;
	globalBuffer.info.bmiHeader.biHeight = -720;
	globalBuffer.info.bmiHeader.biPlanes = 1;
	globalBuffer.info.bmiHeader.biBitCount = 32;
	globalBuffer.info.bmiHeader.biCompression = BI_RGB;

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
#pragma endregion
				//Basically this is the code that runs
				Vect2 v1 = { 50,100 };
				Vect2 v2 = { 500, 500 };

				POINT mousePoint;
				GetCursorPos(&mousePoint);
				ScreenToClient(window_handle, &mousePoint);

				Vect2 v3 = { Clamp(mousePoint.x,0,globalBuffer.width),Clamp(mousePoint.y,0,globalBuffer.height) };
				Vect2 v4 = { 500, 500 };

				clrScr();
				
				DDA(v4.x,v4.y,v3.x,v3.y, 0x00FF00);

				float coordinate[3][3] = { 200,600,400,200,200,400,1,1,1 };
				drawTriangle(coordinate, 2);//green
				// shearing_x_axis(0.5,coordinate);
				// translation(50,100,coordinate);

				scaling(0.5, 0.5, coordinate);

				// fixed_point_scaling(400,266.67,0.8,0.8,coordinate);

				// pivot_point_rotation(400,266.67,90,coordinate);

				// rotation(-90,coordinate);

				// rotation(-10,coordinate);

				StretchDIBits(deviceContext, 0, 0, globalBuffer.width, globalBuffer.height,
					0, 0, globalBuffer.width, globalBuffer.height, globalBuffer.memory, &globalBuffer.info, DIB_RGB_COLORS, SRCCOPY);
			}
		}
	}
	return 0;
};

void DDA(float x0, float y0, float xn, float yn, unsigned int color)
{
    int dx, dy, step;
    dx = xn - x0;//change in x
    dy = yn - y0;//change in y
    if (abs(dx) > abs(dy))//to check if slope is less than 1
    {
        step = abs(dx);//set step as absolute value of change in x
    }
    else
    {
        step = abs(dy);//set step as absolute value of change in y
    }
    float xinc{ dx / float(step) }, yinc{ dy / float(step) };//calculate xinc as 1 or 1/m or calculate yinc as 1 or m
    float x{ x0 }, y{ y0 };
    drawPixel(int(x), int(y), color);
    for (int i = 0; i < step; i++)
    {
        x += xinc;//x=x+1/m or x=x+1
        y += yinc;//y=y+m or y=y+1
        drawPixel(int(x), int(y), color);
    }
}
void multiply(float x[3][3], float y[3][3], float result[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += x[i][k] * y[k][j];
            }
        }
    }
}
void drawTriangle(float coordinate[3][3], unsigned int color)
{
    DDA(coordinate[0][0], coordinate[1][0], coordinate[0][1], coordinate[1][1], color);
    DDA(coordinate[0][0], coordinate[1][0], coordinate[0][2], coordinate[1][2], color);
    DDA(coordinate[0][1], coordinate[1][1], coordinate[0][2], coordinate[1][2], color);
}
void translation(float tx, float ty, float coordinate[3][3])
{

    float x[3][3] = { 1,0,tx,0,1,ty,0,0,1 };
    float ans[3][3];
    multiply(x, coordinate, ans);
    drawTriangle(ans, 4);//red
}
void rotation(float angle,float coordinate[3][3])
{
     float x[3][3]={cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1};
     angle=angle*PI/180;
     float ans[3][3];
     multiply(x,coordinate,ans);
     drawTriangle(ans, 0x00FF00);
}
 void pivot_point_rotation(float xf,float yf,float angle,float coordinate[3][3])
 {
     float x[3][3]={1,0,xf,0,1,yf,0,0,1};
     angle=angle*PI/180;
     float y[3][3]={cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1};
     float ans[3][3];
     multiply(x,y,ans);
     float z[3][3]={1,0,-xf,0,1,-yf,0,0,1};
     multiply(ans,z,x);
     multiply(x,coordinate,ans);
     drawTriangle(ans,7);//white
 }
void scaling(float sx, float sy, float coordinate[3][3])
{
    float x[3][3] = { sx,0,0,0,sy,0,0,0,1 };
    float ans[3][3];
    multiply(x, coordinate, ans);
    drawTriangle(ans, 15);//white
}
void fixed_point_scaling(float xf, float yf, float sx, float sy, float coordinate[3][3])
{
    float x[3][3] = { 1,0,xf,0,1,yf,0,0,1 };
    float y[3][3] = { sx,0,0,0,sy,0,0,0,1 };
    float ans[3][3];
    multiply(x, y, ans);
    float z[3][3] = { 1,0,-xf,0,1,-yf,0,0,1 };
    multiply(ans, z, x);
    multiply(x, coordinate, ans);
    drawTriangle(ans, 7);//white
}
void shearing_x_axis(float shx, float coordinate[3][3])
{
    float x[3][3] = { 1,shx,0,0,1,0,0,0,1 };
    float ans[3][3];
    multiply(x, coordinate, ans);
    drawTriangle(ans, 14);
}
