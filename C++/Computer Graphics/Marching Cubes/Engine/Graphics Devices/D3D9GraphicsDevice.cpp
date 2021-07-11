/*
D3D9GraphicsDevice.cpp
Written by Matthew Fisher

a _D3D instance of GraphicsDevice.  The only new functionality is GetDevice() which returns
the D3DDevice associated with this graphics device.
*/

#ifdef USE_D3D9

D3D9GraphicsDevice::D3D9GraphicsDevice()
{
    _type = GD_D3D9;
    _assetsReleased = false;
    _d3d = NULL;
    _device = NULL;
    _windowSurface = NULL;
    _desktopSurface = NULL;
}

D3D9GraphicsDevice::~D3D9GraphicsDevice()
{
    FreeMemory();
}

void D3D9GraphicsDevice::FreeMemory()
{
    if(_device)
    {
        _device->Release();
        _device = 0;
    }
    if(_d3d)
    {
        _d3d->Release();
        _d3d = 0;
    }
}

void D3D9GraphicsDevice::LoadPresentParameters(D3DPRESENT_PARAMETERS &PresentParameters, HWND Window, UINT Width, UINT Height)
{
    ZeroMemory( &PresentParameters, sizeof(PresentParameters) );
    PresentParameters.BackBufferWidth = Width;
    PresentParameters.BackBufferHeight = Height;
    PresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    PresentParameters.BackBufferCount = 1;
    PresentParameters.MultiSampleQuality = 0;
    PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    PresentParameters.hDeviceWindow = Window;
    
    if(_parameters.MultisampleCount <= 1)
    {
        PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
        PresentParameters.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    }
    else
    {
        PresentParameters.MultiSampleType = D3DMULTISAMPLE_TYPE(_parameters.MultisampleCount);
    }

    PresentParameters.Windowed = TRUE;
    
    PresentParameters.EnableAutoDepthStencil = TRUE;
    PresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
    PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

    if(_parameters.WaitForVSync)
    {
        PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    }
    else
    {
        PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    }
}

void D3D9GraphicsDevice::InitializeStateMachine()
{
    D3DXMATRIXA16 matIdentity;
    D3DXMatrixIdentity(&matIdentity);

    _device->SetTransform(D3DTS_WORLD, &matIdentity);
    _device->SetTransform(D3DTS_VIEW, &matIdentity);
    _device->SetTransform(D3DTS_PROJECTION, &matIdentity);

    _device->SetRenderState(D3DRS_LIGHTING, FALSE);
    _device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    _device->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    _device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
    _device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
    _device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    _device->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    _device->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    _device->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    _device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    _device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    _device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
}

void D3D9GraphicsDevice::Init(const GraphicsDeviceParameters &parameters, ApplicationWindow &window)
{
    Init(parameters, window.Handle(), window.Width(), window.Height());
}

void D3D9GraphicsDevice::Init(const GraphicsDeviceParameters &parameters, HWND window, UINT width, UINT height)
{
    FreeMemory();
    
    _parameters = parameters;
    if(_parameters.MainFontName.Length() == 0)
    {
        _parameters.MainFontName = "Verdana";
    }

    _d3d = Direct3DCreate9( D3D_SDK_VERSION );

    Assert(_d3d != NULL, "Direct3DCreate9 failed");
    
    D3DPRESENT_PARAMETERS d3dpp;
    LoadPresentParameters(d3dpp, window, width, height);    //get the paramaters

    //D3DCREATE_FPU_PRESERVE
    HRESULT hr = _d3d->CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL,
                                     window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp,
                                     &_device );
    if(_device == NULL)
    {
        _parameters.MultisampleCount = 1;
        LoadPresentParameters(d3dpp, window, width, height);

        hr = _d3d->CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL,
                                 window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp,
                                 &_device );
    }
    if(_device == NULL)
    {
        hr = _d3d->CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL,
                                 window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp,
                                 &_device );
    }
    PersistentAssert(_device != NULL, "CreateDevice failed.  This application requires a DirectX 9.0c or better graphics card.");

    _assetsReleased = false;
    InitializeStateMachine();
}

bool D3D9GraphicsDevice::StartRender()
{
    if(!_device)
    {
        return false;
    }

    RGBColor ScreenColor = _parameters.ScreenColor;
    _device->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_ARGB(ScreenColor.a, ScreenColor.r, ScreenColor.g, ScreenColor.b), 1.0f, 0 );
    
    HRESULT CoopLevel = _device->TestCooperativeLevel();
    if(CoopLevel == D3D_OK)
    {
        _device->BeginScene();
        return true;
    }
    else
    {
        return false;
    }
}

void D3D9GraphicsDevice::FinishRender(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks)
{
    if(!_device)
    {
        return;
    }

    HRESULT CoopLevel = _device->TestCooperativeLevel();
    if(CoopLevel == D3D_OK)
    {
        _device->EndScene();
        CoopLevel = _device->Present( NULL, NULL, NULL, NULL );
    }
    if(CoopLevel == D3DERR_DEVICELOST || CoopLevel == D3DERR_DEVICENOTRESET)
    {
        if(!_assetsReleased)
        {
            callbacks.ReleaseAssets();
            _assetsReleased = true;
        }
        else
        {
            HRESULT CoopLevel = _device->TestCooperativeLevel();
            if(CoopLevel == D3DERR_DEVICENOTRESET || CoopLevel == D3D_OK)
            {
                D3DPRESENT_PARAMETERS d3dpp;
                LoadPresentParameters(d3dpp, window.Handle(), window.Width(), window.Height());

                if(_device->Reset(&d3dpp) == D3D_OK)
                {
                    InitializeStateMachine();
                    _assetsReleased = false;
                    callbacks.ResetAssets();
                }
            }
        }
    }
}

void D3D9GraphicsDevice::ReSize(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks)
{
    callbacks.ReleaseAssets();
    _assetsReleased = true;

    D3DPRESENT_PARAMETERS d3dpp;
    LoadPresentParameters(d3dpp, window.Handle(), window.Width(), window.Height());
    if(_device->Reset(&d3dpp) == D3D_OK)
    {
        InitializeStateMachine();
        _assetsReleased = false;
        callbacks.ResetAssets();
    }
}

void D3D9GraphicsDevice::ClearTexture(UINT index)
{
    _device->SetTexture(index, NULL);
}

void D3D9GraphicsDevice::ToggleWireframe()
{
    DWORD value = 0;
    _device->GetRenderState(D3DRS_FILLMODE, &value);
    if(value == D3DFILL_SOLID)
    {
        _device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    }
    else
    {
        _device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    }
}

void D3D9GraphicsDevice::Render(const Mesh &m)
{
    _device->SetFVF(D3DMeshFVF);
    _device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m.VertexCount(), m.FaceCount(), m.Indices(), D3DFMT_INDEX32, m.Vertices(), sizeof(MeshVertex));
}

LPDIRECT3DDEVICE9 D3D9GraphicsDevice::GetDevice()
{
    return _device;
}

void D3D9GraphicsDevice::CaptureDesktop(ApplicationWindow &window, Bitmap &bmp)
{
    //
    // see http://www.codeproject.com/KB/system/snapshot.aspx for an alternate way
    //

    RECT DesktopRect;
    GetClientRect(GetDesktopWindow(), &DesktopRect);

    if(_desktopSurface == NULL)
    {
        HRESULT hr = _device->CreateOffscreenPlainSurface(DesktopRect.right, DesktopRect.bottom, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &_desktopSurface, NULL);
        PersistentAssert(!FAILED(hr) && _desktopSurface != NULL, "CreateOffscreenPlainSurface failed");
    }

    //HRESULT hr = _device->GetFrontBufferData(0, _DesktopSurface);
    //PersistentAssert(!FAILED(hr), "GetFrontBufferData failed");

    HDC DesktopSurfaceDC;
    _desktopSurface->GetDC(&DesktopSurfaceDC);
    BitBlt(DesktopSurfaceDC, 0, 0, DesktopRect.right, DesktopRect.bottom, GetDC(GetDesktopWindow()), 0, 0, SRCCOPY);
    _desktopSurface->ReleaseDC(DesktopSurfaceDC);

    bmp.LoadFromSurface(_desktopSurface);
}

void D3D9GraphicsDevice::CaptureScreen(ApplicationWindow &window, Bitmap &bmp)
{
    const bool CaptureFrontBuffer = true;
    if(CaptureFrontBuffer)
    {
        RECT DesktopRect;
        GetWindowRect(GetDesktopWindow(), &DesktopRect);

        LPDIRECT3DSURFACE9 Surface;
        HRESULT hr = _device->CreateOffscreenPlainSurface(DesktopRect.right - DesktopRect.left, DesktopRect.bottom - DesktopRect.top, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &Surface, NULL);
        PersistentAssert(!FAILED(hr), "CreateOffscreenPlainSurface failed");
        PersistentAssert(Surface != NULL, "Invalid surface handle from CreateOffscreenPlainSurface");

        hr = _device->GetFrontBufferData(0, Surface);
        PersistentAssert(!FAILED(hr), "GetFrontBufferData failed");

        Bitmap DesktopBmp;
        DesktopBmp.LoadFromSurface(Surface);
        DesktopBmp.FlipVertical();
        Surface->Release();
        
        RECT WindowCoord;
        GetClientRect(window.Handle(), &WindowCoord);
        MapWindowPoints(window.Handle(), GetDesktopWindow(), (LPPOINT)&WindowCoord, 2);

        UINT Width = WindowCoord.right - WindowCoord.left;
        UINT Height = WindowCoord.bottom - WindowCoord.top;

        bmp.Allocate(Width, Height);
        DesktopBmp.BltTo(bmp, 0, 0, WindowCoord.left, WindowCoord.top, Width, Height);
        bmp.FlipBlueAndRed();
        bmp.FlipVertical();
    }
    else
    {
        LPDIRECT3DSURFACE9 RenderTarget = NULL;
        D3DAlwaysValidate(_device->GetRenderTarget(0, &RenderTarget), "GetRenderTarget");

        D3DSURFACE_DESC RenderTargetDesc;
        D3DAlwaysValidate(RenderTarget->GetDesc(&RenderTargetDesc), "GetDesc");

        bool WindowSurfaceValid = (_windowSurface != NULL);
        if(WindowSurfaceValid)
        {
            D3DSURFACE_DESC WindowSurfaceDesc;
            D3DAlwaysValidate(_windowSurface->GetDesc(&WindowSurfaceDesc), "GetDesc");
            if(WindowSurfaceDesc.Width != RenderTargetDesc.Width || WindowSurfaceDesc.Height != RenderTargetDesc.Height)
            {
                WindowSurfaceValid = false;
            }
        }
        if(!WindowSurfaceValid)
        {
            if(_windowSurface != NULL)
            {
                _windowSurface->Release();
            }
            D3DAlwaysValidate(_device->CreateOffscreenPlainSurface(RenderTargetDesc.Width, RenderTargetDesc.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &_windowSurface, NULL), "CreateOffscreenPlainSurface");
        }

        D3DAlwaysValidate(_device->GetRenderTargetData(RenderTarget, _windowSurface), "GetRenderTargetData");
        RenderTarget->Release();

        bmp.LoadFromSurface(_windowSurface);

        /*LPDIRECT3DSURFACE9 BackBufferSurface = NULL;
        D3DSURFACE_DESC Desc;
        D3DAlwaysValidate(_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBufferSurface), "GetBackBuffer");
        D3DAlwaysValidate(BackBufferSurface->GetDesc(&Desc), "GetDesc");
        
        D3DLOCKED_RECT Rect;
        D3DAlwaysValidate(BackBufferSurface->LockRect(&Rect, NULL, NULL), "LockRect");

        RECT WindowCoord;
        WindowCoord.top = 0;
        WindowCoord.left = 0;
        WindowCoord.bottom = Desc.Height;
        WindowCoord.right = Desc.Width;

        B.Allocate(Desc.Width, Desc.Height);
        RGBColor *Bits = (RGBColor*)Rect.pBits;
        
        UINT Pitch = Rect.Pitch / 4;
        for(int i2 = WindowCoord.top; i2 < WindowCoord.bottom; i2++)
        {
            for(int i = WindowCoord.left; i < WindowCoord.right; i++)
            {
                {
                    B[B.Height() - (i2 - WindowCoord.top) - 1][i - WindowCoord.left] = Bits[i2 * Pitch + i];
                }
            }
        }
        BackBufferSurface->UnlockRect();
        BackBufferSurface->Release();*/
    }
}

#endif