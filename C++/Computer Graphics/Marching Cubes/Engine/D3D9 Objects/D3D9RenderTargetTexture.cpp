/*
D3D9RenderTargetTexture.cpp
Written by Matthew Fisher

The D3D9ProtectRenderTarget class is used to simplify preserving a device's current render target and depth buffer
so new ones can easily be overlayed, and then the original render target and depth buffer restored.
D3D9RenderTargetTexture is a texture that can be used as a render target.  It has its own associated depth buffer.
*/

#ifdef USE_D3D9

D3D9RenderTargetTexture::D3D9RenderTargetTexture()
{
    _Texture = NULL;
    _Surface = NULL;
    _SurfacePlain = NULL;
    _SurfaceResizing = NULL;
    _DepthSurface = NULL;
}

D3D9RenderTargetTexture::~D3D9RenderTargetTexture()
{
    FreeMemory();
}

void D3D9RenderTargetTexture::ReleaseMemory()
{
    FreeMemory();
}

void D3D9RenderTargetTexture::FreeMemory()
{
    if(_Texture)
    {
        _Texture->Release();
        _Texture = NULL;
    }
    if(_Surface)
    {
        _Surface->Release();
        _Surface = NULL;
    }
    if(_DepthSurface)
    {
        _DepthSurface->Release();
        _DepthSurface = NULL;
    }
    if(_SurfacePlain)
    {
        _SurfacePlain->Release();
        _SurfacePlain = NULL;
    }
    if(_SurfaceResizing)
    {
        _SurfaceResizing->Release();
        _SurfaceResizing = NULL;
    }
}

void D3D9RenderTargetTexture::Reset(LPDIRECT3DDEVICE9 Device)
{
    bool createDepthSurface = (_DepthSurface != NULL);
    Init(Device, _Width, _Height, createDepthSurface);
    SetData(_DataCopy);
}

void D3D9RenderTargetTexture::Init(LPDIRECT3DDEVICE9 Device, UINT Width, UINT Height, bool CreateDepthSurface)
{
    FreeMemory();

    PersistentAssert(Device != NULL, "Device == NULL");
    _Device = Device;
    _Width = Width;
    _Height = Height;
    //FullValidate(_Device->CreateRenderTarget(_Width, _Height, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, TRUE, &_Surface, NULL));
    D3DAlwaysValidate(_Device->CreateTexture(_Width, _Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_Texture, NULL), "CreateTexture");
    D3DAlwaysValidate(_Device->CreateOffscreenPlainSurface(_Width, _Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &_SurfacePlain, NULL), "CreateOffscreenPlainSurface");
    D3DAlwaysValidate(_Texture->GetSurfaceLevel(0, &_Surface), "GetSurfaceLevel");

    if(CreateDepthSurface)
    {
        D3DAlwaysValidate(_Device->CreateDepthStencilSurface(_Width, _Height, D3DFMT_D32F_LOCKABLE, D3DMULTISAMPLE_NONE, 0, FALSE, &_DepthSurface, NULL), "CreateDepthStencilSurface");
    }

    _DataCopy.Allocate(_Width, _Height);
}

void D3D9RenderTargetTexture::SetAsRenderTarget()
{
    _Device->SetRenderTarget(0, _Surface);
    _Device->SetDepthStencilSurface(_DepthSurface);
}

void D3D9RenderTargetTexture::SetAsTexture(UINT Stage)
{
    _Device->SetTexture(Stage, _Texture);
}

void D3D9RenderTargetTexture::GetData(Bitmap &B, const Rectangle2i &Source, const Rectangle2i &Dest)
{
    D3DAlwaysValidate(_Device->GetRenderTargetData(_Surface, _SurfacePlain), "GetRenderTargetData");

    if(_SurfaceResizing == NULL)
    {
        D3DAlwaysValidate(_Device->CreateOffscreenPlainSurface(_Width, _Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_SurfaceResizing, NULL), "CreateOffscreenPlainSurface");
    }
    D3DAlwaysValidate(_Device->UpdateSurface(_SurfacePlain, NULL, _SurfaceResizing, NULL), "UpdateSurface");

    RECT SourceRect = Source.ToRect();
    RECT DestRect = Rectangle2i(Vec2i::Origin, Dest.Dimensions()).ToRect();
    D3DAlwaysValidate(_Device->StretchRect(_SurfaceResizing, &SourceRect, _Surface, &DestRect, D3DTEXF_LINEAR), "StretchRect");

    D3DAlwaysValidate(_Device->GetRenderTargetData(_Surface, _SurfacePlain), "GetRenderTargetData");

    D3DLOCKED_RECT LockedRect;
    D3DAlwaysValidate(_SurfacePlain->LockRect(&LockedRect, NULL, 0), "LockRect");

    Assert(int(B.Width()) >= Dest.Max.x && int(B.Height()) >= Dest.Max.y, "Bitmap too small");

    RGBColor *SurfData = (RGBColor*)LockedRect.pBits;
    for(int y = Dest.Min.y; y < Dest.Max.y; y++)
    {
        //memcpy(B[_Height - 1 - y], &SurfData[y * LockedRect.Pitch / 4], _Width * 4);
        memcpy(B[y] + Dest.Min.x, &SurfData[(y - Dest.Min.y) * LockedRect.Pitch / 4], Dest.Dimensions().x * 4);
    }

    _SurfacePlain->UnlockRect();
}

void D3D9RenderTargetTexture::GetData(Bitmap &B)
{
    D3DAlwaysValidate(_Device->GetRenderTargetData(_Surface, _SurfacePlain), "GetRenderTargetData");
    D3DLOCKED_RECT LockedRect;
    D3DAlwaysValidate(_SurfacePlain->LockRect(&LockedRect, NULL, 0), "LockRect");

    B.Allocate(_Width, _Height);
    RGBColor *SurfData = (RGBColor*)LockedRect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        //memcpy(B[_Height - 1 - y], &SurfData[y * LockedRect.Pitch / 4], _Width * 4);
        memcpy(B[y], &SurfData[y * LockedRect.Pitch / 4], _Width * 4);
    }

    _SurfacePlain->UnlockRect();
}

void D3D9RenderTargetTexture::GetDepthData(Grid<float> &DepthMap)
{
    PersistentAssert(_DepthSurface != NULL, "_DepthSurface == NULL unexpected");
    D3DLOCKED_RECT LockedRect;
    D3DAlwaysValidate(_DepthSurface->LockRect(&LockedRect, NULL, 0), "LockRect");
    BYTE *Data = (BYTE *)LockedRect.pBits;
    
    DepthMap.Allocate(_Height, _Width);
    
    for(UINT y = 0; y < _Height; y++)
    {
        float *RowStart = (float *)(Data + y * LockedRect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            DepthMap(y, x) = RowStart[x];
        }
    }
    D3DAlwaysValidate(_DepthSurface->UnlockRect(), "UnlockRect");
}

void D3D9RenderTargetTexture::SetData(const Bitmap &B)
{
    D3DLOCKED_RECT LockedRect;
    D3DAlwaysValidate(_SurfacePlain->LockRect(&LockedRect, NULL, 0), "LockRect");

    Assert(B.Width() == _Width && B.Height() == _Height, "Invalid bitmap dimensions.");
    RGBColor *SurfData = (RGBColor*)LockedRect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        memcpy(&SurfData[y * LockedRect.Pitch / 4], B[_Height - 1 - y], _Width * 4);
    }

    _SurfacePlain->UnlockRect();
    D3DAlwaysValidate(_Device->UpdateSurface(_SurfacePlain, NULL, _Surface, NULL), "UpdateSurface");

    _DataCopy = B;
}

/*void DXRenderSurface::SetData(DXRenderSurface &S)
{
    FullValidate(_Device->GetRenderTargetData(S._Surface, _SurfacePlain));
    FullValidate(_Device->UpdateSurface(_SurfacePlain, NULL, _Surface, NULL));
}*/

void D3D9RenderTargetTexture::RenderStringToBmp(const D3D9Font &Font, const String &Text, const Rectangle2i &Region, RGBColor FontColor, RGBColor BackgroundColor, Bitmap &Bmp)
{
    D3D9ProtectRenderTarget Protection(_Device, true, true);

    SetAsRenderTarget();
    _Device->Clear(0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_ARGB(BackgroundColor.a, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b), 1.0f, 0 );
    Font.DrawString(Text, Region.Min, Region.Width(), FontColor);
    GetData(Bmp);
}

#endif