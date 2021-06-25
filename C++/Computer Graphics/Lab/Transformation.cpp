#include <Windows.h>
#include <cmath>
#include <algorithm>

struct Vect2 {
	float x, y;
};
struct Bect2 {
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
void drawRect(Bect2 v1, Bect2 v2, unsigned int color) {
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
void drawDDALine(Bect2 v1, Bect2 v2, unsigned int color)
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
		drawPixel((int)(x + 0.5f), (int)(y + 0.5f), color);
		x += xincr;
		y += yincr;
	}
}
void drawBresLine(Bect2 v1, Bect2 v2, unsigned int color) {
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
	if (v2.y < v1.y) incy = -1;
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
			drawPixel(x, y, color);
		}

	}
	else {
		drawPixel(x, y, color);
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
			drawPixel(x, y, color);
		}
	}
}
void matMul(float mat1[][3], float mat2[][3], float ans[][3]){
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			ans[i][j] = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				ans[i][j] += mat1[i][k] * mat2[k][j];
}
void translation(float point[][3], float newPoint[][3], Vect2 translationFactor) {
	float composite[3][3] = { {1,0,translationFactor.x},{0,1,translationFactor.y},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotation(float point[][3], float newPoint[][3], int angle) {
	float rad = 3.14 * angle / 180;
	float composite[3][3] = { {cos(rad),-sin(rad),0},{sin(rad),cos(rad),0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotate(float point[][3], float newPoint[][3], float rad) {
	float composite[3][3] = { {cos(rad),-sin(rad),0},{sin(rad),cos(rad),0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scaling(float point[][3], float newPoint[][3], Vect2 scalingFactor) {
	float composite[3][3] = { {scalingFactor.x,0,0},{0,scalingFactor.y,0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scale(float point[][3], float newPoint[][3], float sx, float sy) {
	float composite[3][3] = { {sx,0,0},{0,sy,0},{0,0,1} };
	matMul(composite, point, newPoint);
}
void rotationPivot(float point[][3], float newPoint[][3], int angle, Bect2 pivot) {
	float rad = 3.14 * angle / 180;
	float composite[3][3] = { {cos(rad),-sin(rad),pivot.x * (1 -cos(rad)) + pivot.y * sin(rad)},
		{sin(rad),cos(rad),pivot.y * (1 - cos(rad)) - pivot.x * sin(rad)},{0,0,1} };
	matMul(composite, point, newPoint);
}
void scalingFixed(float point[][3], float newPoint[][3], Bect2 fixedPoint, Vect2 scalingFactor) {
	float composite[3][3] = { {scalingFactor.x,0,fixedPoint.x * (1 - fixedPoint.x)},
		{0,scalingFactor.y,fixedPoint.y * (1 - scalingFactor.y)},{0,0,1} };  
	matMul(composite, point, newPoint);	
}
void scalingWithAngle(float point[][3], float newPoint[][3], int angle, Vect2 scalingFactor) {
	float rad = 3.14 * angle / 180;
	rotate(point, newPoint, -rad);
	scale(newPoint, newPoint, scalingFactor.x, scalingFactor.y);
	rotate(newPoint, newPoint, rad);
}
//1.y=0 2.x=0 3.y=x 4.y=-x
void reflection(float point[][3], float newPoint[][3], int choice) {
		switch (choice)
		{
		case 1: {
			float composite1[3][3] = { {1,0,0},{0,-1,0},{0,0,1} };
			matMul(composite1, point, newPoint);
			break;
		}
		case 2: {
			float composite2[3][3] = { {-1,0,0},{0,1,0},{0,0,1} };
			matMul(composite2, point, newPoint);
			break;
		}
		case 3: {
			float composite3[3][3] = { {0,1,0},{1,0,0},{0,0,1} };
			matMul(composite3, point, newPoint);
			break;
		}
		case 4: {
			float composite4[3][3] = { {0,-1,0},{-1,0,0},{0,0,1} };
			matMul(composite4, point, newPoint);
			break;
		}
	}
}
void shearing(float point[][3], float newPoint[][3], int choice, Vect2 shearingParams) {
	//1.x-direction relative to x-axis(y=0) 2.y-direction relative to yaxis(x=0) 3.In both direction
	switch (choice){
	case 1: {
		float composite2[3][3] = { {1,shearingParams.x,0},{0,1,0},{0,0,1} };
		matMul(composite2, point, newPoint);
		break;
	}
	case 2: {
		float composite3[3][3] = { {1,0,0},{shearingParams.y,1,0},{0,0,1} };
		matMul(composite3, point, newPoint);
		break;
	}
	case 3: {
		float composite1[3][3] = { {1,shearingParams.x,0},{shearingParams.y,1,0},{0,0,1} };
		matMul(composite1, point, newPoint);
	}
	default:
		break;
	}
}
void shearigRef(float point[][3], float newPoint[][3], int choice, float shearingParameter, float referenceParameter)
{
	//1.x-direction relative to y=yref 2.y-direction relative to x=xref
	switch (choice)	{
	case 1: {
		float composite1[3][3] = { {1,shearingParameter,-shearingParameter * referenceParameter},{0,1,0},{0,0,1} };
		matMul(composite1, point, newPoint);
		break;
	}
	case 2: {
		float composite2[3][3] = { {1,0,0},{shearingParameter,1,-shearingParameter * referenceParameter},{0,0,1} };
		matMul(composite2, point, newPoint);
		break;
	}
	default: 
		break;
	}
}
void drawTriangle(float newPoint[][3],unsigned color) {
	int nx1 = newPoint[0][0];
	int ny1 = newPoint[1][0];
	int nx2 = newPoint[0][1];
	int ny2 = newPoint[1][1];
	int nx3 = newPoint[0][2];
	int ny3 = newPoint[1][2];

	//Draw Output
	drawBresLine(Bect2{ nx1 + 500, ny1 + 400 }, Bect2{ nx2 + 500, ny2 + 400 }, color);
	drawBresLine(Bect2{ nx2 + 500, ny2 + 400 }, Bect2{ nx3 + 500, ny3 + 400 }, color);
	drawBresLine(Bect2{ nx3 + 500, ny3 + 400 }, Bect2{ nx1 + 500, ny1 + 400 }, color);
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
) 
{
#pragma region Initializer
	WNDCLASS wndclass = {};
	wndclass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = L"HelloThere";
	wndclass.lpszClassName = L"ButGoodbye";

	globalBuffer.width = 1000;
	globalBuffer.height = 800;

	globalBuffer.info.bmiHeader = {};
	globalBuffer.info.bmiHeader.biSize = sizeof(globalBuffer.info.bmiHeader);
	globalBuffer.info.bmiHeader.biWidth = globalBuffer.width;
	globalBuffer.info.bmiHeader.biHeight = -globalBuffer.height;
	globalBuffer.info.bmiHeader.biPlanes = 1;
	globalBuffer.info.bmiHeader.biBitCount = 32;
	globalBuffer.info.bmiHeader.biCompression = BI_RGB;

	globalBuffer.memory = VirtualAlloc(0, globalBuffer.width * globalBuffer.height * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (RegisterClass(&wndclass)) {
		HWND window_handle = CreateWindowEx(0, wndclass.lpszClassName, L"Hello69", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, globalBuffer.width, globalBuffer.height,
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
				clrScr();

				int x1=80, x2=60, x3=55, y1=90, y2=105, y3=90;
				int nx1, nx2, nx3, ny1, ny2, ny3;
				drawBresLine(Bect2{ 500, 0 }, Bect2{ 500, 800 },0x90ee90);
				drawBresLine(Bect2{ 0, 400 }, Bect2{ 1000, 400 },0x90ee90);
				float point[3][3] = { {x1,x2,x3},{y1,y2,y3},{1,1,1} };
				float newPoint[3][3] = {};
				drawBresLine(Bect2{ x1 + 500, y1 + 400 }, Bect2{ x2 + 500, y2 + 400 }, 0x90ee99);
				drawBresLine(Bect2{ x2 + 500, y2 + 400 }, Bect2{ x3 + 500, y3 + 400 }, 0x90ee99);
				drawBresLine(Bect2{ x3 + 500 , y3 + 400 }, Bect2{ x1 + 500, y1 + 400 }, 0x90ee99);				
					
				//1.Translation with specified parameters
					translation(point, newPoint, Vect2{ 25,30 }); drawTriangle(newPoint,0xffadad);
				//2.Rotation with specified parameters
					rotation(point, newPoint, 150); drawTriangle(newPoint,0xffd6a5);
				//3.Scaling with specified parameters
					scaling(point, newPoint, Vect2{ 2.6, 1.3 }); drawTriangle(newPoint,0xfdffb6);
				//4.Rotation about a pivot point
					rotationPivot(point, newPoint, 45, Bect2{ -100,50 }); drawTriangle(newPoint,0xcaffbf);
				//5.Scaling about a fixed point
					scalingFixed(point, newPoint, Bect2{ 35, -80 }, Vect2{ 2.6, 1.3 }); drawTriangle(newPoint,0x9bf6ff);
				//6.Scaling with orthogonal axis at certain	angle from x - axis
					scalingWithAngle(point, newPoint, 60, Vect2{ 1.6, 2.1 }); drawTriangle(newPoint,0x9bf6ff);
				//7.Reflection with specified axis
					reflection(point, newPoint, 1); drawTriangle(newPoint,0xa0c4ff);
					//reflection(point, newPoint,2); drawTriangle(newPoint);
					//reflection(point, newPoint,3); drawTriangle(newPoint);
					//reflection(point, newPoint,4); drawTriangle(newPoint);

				//8.Shearing with specified parameter
					shearing(point, newPoint, 3, Vect2{ -1.2, 0.5 }); drawTriangle(newPoint,0xbdb2ff);
					//shearing(point, newPoint, 2, Vect2{ -1.2, 0.5 }); drawTriangle(newPoint);
					//shearing(point, newPoint, 1, Vect2{ -1.2, 0.5 }); drawTriangle(newPoint);

				//9.Shearing with specified reference line
					shearigRef(point, newPoint, 1, 2, 2); drawTriangle(newPoint,0xffc6ff);

#pragma region Initializer
				StretchDIBits(deviceContext, 0, 0, globalBuffer.width, globalBuffer.height,
					0, 0, globalBuffer.width, globalBuffer.height, globalBuffer.memory, &globalBuffer.info, DIB_RGB_COLORS, SRCCOPY);
			}
		}
	}
	return 0;
#pragma endregion
};