#include <windows.h>
#include <cassert>

//Function declarartion
void f(void);

//Function definition
void f(void)
{
	OutputDebugStringA("This is the first thing we have actually printed.\n");
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	f();
	return 0;
}
int main()
{
	assert(!"Unimplemented thing");

	f();
	return 0;
}