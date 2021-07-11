/*
App.cpp
Written by Matthew Fisher

The App class glues the operating system, the graphics device, the application interface,
and the window manager together.  It is essentially the first and the last code that is executed.
See App.h for a description of the class and member functions.
*/

//All source files include Main.h
#include "Main.h"

const int GraphicsDeviceType = GD_D3D9;

const UINT WindowWidth = 720;
const UINT WindowHeight = 640;

const bool VSync = true;            //true to wait for the monitor to finish the entire display (vertical retracing) before
                                    //the front buffer is flipped.  Setting this to false results in higher frame rate, but may
                                    //induce flickering.

const String FontName = "Verdana";

void App::Init(HINSTANCE hInstance, int nCmdShow)
{
    _state.graphics = NULL;

    const String &windowName = "BaseCode";

    //
    // Create a new GraphicsDevice object based upon the type of graphics device requested in GraphicsDeviceType
    //
#ifdef USE_D3D9
    if(GraphicsDeviceType == GD_D3D9)
    {
        _state.graphics = new D3D9GraphicsDevice;
    }
#endif
    else
    {
        Assert(NULL, "Invalid graphics device type");
    }
    Assert(_state.graphics != NULL, "Failed to allocate graphics device");
    
    g_WndProcContext = &_state.input;
    _state.window.InitAll(hInstance, nCmdShow, false, WindowWidth, WindowHeight, windowName);

    _controller = new Controller;
    _controller->Init(_state);
    
    GraphicsDeviceParameters parameters;
    parameters.WaitForVSync = VSync;
    parameters.MainFontName = FontName;
    _state.graphics->Init(parameters, _state.window);
    
    _state.timer.Start(60.0f);
    _state.timer.Pause();

    _controller->Init3D();
}

void App::RenderFrame()
{
    _state.input.Frame();

    Vec2i curDimensions = _state.window.Dimensions();
    if(curDimensions != _state.dimensions)
    {
        _state.dimensions = curDimensions;
        _state.graphics->ReSize(_state.window, *_controller);
        _controller->ReSize();
        return;
    }

    bool active = _state.graphics->StartRender();

    if(active)
    {
        _state.timer.Frame();
        _controller->Frame();
    }
    else
    {
        _state.timer.Pause();
    }

    _state.graphics->FinishRender(_state.window, *_controller);
}

void App::MessageLoop(HINSTANCE hInstance, int nCmdShow)
{
    MSG msg;
    BOOL bGotMsg;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );    //get a new message

    while( WM_QUIT != msg.message  )    //while we don't have the quit message
    {
        bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );    //get a new message
        if( bGotMsg )                    //if we have a message
        {
            TranslateMessage( &msg );    //send it out
            DispatchMessage( &msg );
        }
        else
        {
            //
            // If we have no messages then it's a good time to render 
            //
            RenderFrame();
        }
    }
}

void App::FreeMemory()
{
    _controller->FreeMemory();
    _state.graphics->FreeMemory();
    _state.window.FreeMemory();
}
