/*
MainControl.cpp
Written by Matthew Fisher

MainControl includes everything that changes often between applications, such as what meshes to load,
and also determines what is rendered each frame.
*/

#include "Main.h"

float SphereFunction(const Vec3f &Pos)
{
    return Pos.x * Pos.x + Pos.y * Pos.y + Pos.z * Pos.z - 1.0f;
}

float RandomFunction(const Vec3f &Pos)
{
    Vec3f P = Pos * 10.0f;
    return sinf(P.Length()) * P.x + sinf(P.Length()) * P.y;
}

float CrazyFunction(const Vec3f &Pos)
{
    Vec3f P = Pos * 3.0f;
    return sinf(P.x * P.y + P.x * P.z + P.y * P.z) + sinf(P.x * P.y) + sinf(P.y * P.z) + sinf(P.x * P.z) - 1.0f;
}

enum MenuEntryType
{
    MenuEntryFile,
    MenuEntryFileQuit,
};

void Controller::FreeMemory()
{
    ReleaseAssets();
}

void Controller::InitMenu()
{
    _menu.Init(_state->window);
    
    Menu &FileMenu = _menu.MenuBar().AddSubMenu(_state->window, MenuEntryFile, "File");
    FileMenu.AddString(_state->window, MenuEntryFileQuit, "Quit\tCtrl+Q");
}

void Controller::ProcessEvents()
{
    _menu.DispatchKeyboardShortcuts(_state->input);

    while(_state->input.EventPresent())
    {
        InputEvent CurEvent = _state->input.PopEvent();
        if(CurEvent.Type == InputEventMenu)
        {
            switch(CurEvent.Id)
            {
            case MenuEntryFileQuit:
                PostQuitMessage(0);
                break;
            }
        }
    }
}

void Controller::ResetCamera()
{
    _camera.Reset(Vec3f(2.0f, 0.0f, 5.0f), Vec3f::eZ, Vec3f::Origin);
}

void Controller::ReleaseAssets()
{
    for(UINT assetIndex = 0; assetIndex < _assetList.Length(); assetIndex++)
    {
        _assetList[assetIndex]->ReleaseMemory();
    }
}

void Controller::ResetAssets()
{
    for(UINT assetIndex = 0; assetIndex < _assetList.Length(); assetIndex++)
    {
        _assetList[assetIndex]->Reset(*_state->graphics);
    }

    ReloadTextures();
}

void Controller::ReSize()
{
    _projection = Matrix4::PerspectiveFov(
                60.0f * Math::PIf / 180.0f,
                _state->window.AspectRatio(),
                0.01f,
                200.0f);
}

void Controller::UpdateIsoSurface()
{
    IsoSurface surfaceGenerator;
    surfaceGenerator.IsoApproximate(1.25f, 0.025f, _assets.surface, _functions[_functionIndex]);
}

void Controller::Init(AppState &state)
{
    _state = &state;
    AllocConsole();

    InitMenu();
}

void Controller::Init3D()
{
    InitAssets();
    ResetCamera();

    _functionIndex = 2;
    _functions[0] = SphereFunction;
    _functions[1] = RandomFunction;
    _functions[2] = CrazyFunction;

    UpdateIsoSurface();
}

void Controller::InitAssets()
{
    _assets.surface.SetGD(*_state->graphics);
    
    _assets.font.Init(*_state->graphics, "Verdana", 20, FW_BOLD);
    _assets.psBase.Init(*_state->graphics, "Assets\\NormalColor.ps");
    _assets.vsBase.Init(*_state->graphics, "Assets\\NormalColor.vs");
    
    _assetList.PushEnd(&_assets.font);
    _assetList.PushEnd(&_assets.psBase);
    _assetList.PushEnd(&_assets.vsBase);

    ReloadTextures();
}

void Controller::ReloadTextures()
{
    Bitmap white(2, 2);
    white.Clear(RGBColor::White);
}

void Controller::UpdateCamera()
{
    _camera.KeyboardWASD  (_state->input, _state->timer.SPF() * 5.0f);
    _camera.KeyboardNumpad(_state->input, _state->timer.SPF());
    _camera.Update();
}

void Controller::ProcessKeyboardInput()
{
    if(_state->input.KeyCheckOnce(KEY_F))
    {
        _state->graphics->ToggleWireframe();
    }
    if(_state->input.KeyCheckOnce(KEY_1))
    {
        _functionIndex = 0;
        UpdateIsoSurface();
    }
    if(_state->input.KeyCheckOnce(KEY_2))
    {
        _functionIndex = 1;
        UpdateIsoSurface();
    }
    if(_state->input.KeyCheckOnce(KEY_3))
    {
        _functionIndex = 2;
        UpdateIsoSurface();
    }
}

void Controller::Status(const String &s, RGBColor c)
{
    _assets.font.DrawString(s, Vec2i(2, _consoleY), c);
    _consoleY += 20;
}

void Controller::StatusText()
{
    _consoleY = 2;
    Status(String("FPS: ") + String(_state->timer.FPS()), RGBColor::Red);
    Status(String("Function ") + String(_functionIndex + 1) + " / " + String(FunctionCount) + String(" (use number keys to switch functions)"), RGBColor::Yellow);
}

void Controller::Render()
{
    _assets.vsBase.Set();
    _assets.psBase.Set();

    Matrix4 viewProj = _camera.Matrix() * _projection;
    _assets.vsBase.SetMatrix("WorldViewProj", viewProj);
    _assets.vsBase.SetMatrix("World", Matrix4::Identity());

    _assets.surface.Render();
}

void Controller::Frame()
{
    ProcessKeyboardInput();
    ProcessEvents();

    UpdateCamera();

    Render();

    StatusText();
}
