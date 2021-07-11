/*
App.h
Written by Matthew Fisher

The App class glues the operating system, the graphics device, the application interface,
and the window manager together.  It is essentially the first and the last code that is executed.
*/

struct AppState
{
    GraphicsDevice*    graphics;
    FrameTimer         timer;
    Vec2i              dimensions;
    ApplicationWindow  window;
    InputManager       input;
};

class App
{
public:
    void FreeMemory();
    void Init(HINSTANCE hInstance, int nCmdShow);
    void MessageLoop(HINSTANCE hInstance, int nCmdShow);

    void RenderFrame();

private:
    AppState    _state;

    Controller* _controller;
};
