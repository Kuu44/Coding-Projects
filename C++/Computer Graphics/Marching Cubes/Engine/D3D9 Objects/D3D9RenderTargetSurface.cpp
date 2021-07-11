/*
D3D9RenderTargetSurface.cpp
Written by Matthew Fisher

D3D9RenderTargetSurface is a surface that can be used as a render target.
*/

#ifdef USE_D3D9

D3D9RenderTargetSurface::D3D9RenderTargetSurface()
{
    _Surface = NULL;
    _OffScreenPlainSurface = NULL;
    _DepthSurface = NULL;
    _Width = 0;
    _Height = 0;
}

D3D9RenderTargetSurface::~D3D9RenderTargetSurface()
{
    FreeMemory();
}

void D3D9RenderTargetSurface::ReleaseMemory()
{
    FreeMemory();
}

void D3D9RenderTargetSurface::FreeMemory()
{
    _Width = 0;
    _Height = 0;
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
    if(_OffScreenPlainSurface)
    {
        _OffScreenPlainSurface->Release();
        _OffScreenPlainSurface = NULL;
    }
}

void D3D9RenderTargetSurface::Reset(GraphicsDevice &graphics)
{
    FreeMemory();
}

void D3D9RenderTargetSurface::Init(D3D9GraphicsDevice &GD, D3DFORMAT format, UINT Width, UINT Height)
{
    FreeMemory();

    D3DAlwaysValidate(GD.GetDevice()->CreateRenderTarget(Width, Height, format, D3DMULTISAMPLE_NONE, 0, FALSE, &_Surface, NULL), "CreateRenderTarget");
    D3DAlwaysValidate(GD.GetDevice()->CreateOffscreenPlainSurface(Width, Height, format, D3DPOOL_SYSTEMMEM, &_OffScreenPlainSurface, NULL), "CreateOffscreenPlainSurface");
    D3DAlwaysValidate(GD.GetDevice()->CreateDepthStencilSurface(Width, Height, D3DFMT_D32F_LOCKABLE, D3DMULTISAMPLE_NONE, 0, FALSE, &_DepthSurface, NULL), "CreateDepthStencilSurface");

    _Width = Width;
    _Height = Height;
    _Format = format;
}

bool D3D9RenderTargetSurface::ReSizeToBackBuffer(D3D9GraphicsDevice &GD, D3DFORMAT format)
{
    IDirect3DSurface9 *BackBuffer;
    HRESULT hr = GD.GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
    if(FAILED(hr))
    {
        FreeMemory();
        return false;
    }
    D3DSURFACE_DESC Desc;
    D3DValidate(BackBuffer->GetDesc(&Desc), "GetDesc");
    BackBuffer->Release();

    if(_Width != Desc.Width || _Height != Desc.Height || _Format != format)
    {
        Init(GD, format, Desc.Width, Desc.Height);
        return true;
    }
    else
    {
        return false;
    }
}

void D3D9RenderTargetSurface::SetAsRenderTarget(D3D9GraphicsDevice &GD, UINT index)
{
    GD.GetDevice()->SetRenderTarget(index, _Surface);
    GD.GetDevice()->SetDepthStencilSurface(_DepthSurface);
}

void D3D9RenderTargetSurface::CopySurfaceToOffScreen(D3D9GraphicsDevice &GD)
{
    D3DAlwaysValidate(GD.GetDevice()->GetRenderTargetData(_Surface, _OffScreenPlainSurface), "GetRenderTargetData");
}

void D3D9RenderTargetSurface::CopyOffScreenToBackBuffer(D3D9GraphicsDevice &GD)
{
    IDirect3DSurface9 *BackBuffer;
    HRESULT hr = GD.GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer);
    if(FAILED(hr))
    {
        return;
    }
    hr = GD.GetDevice()->UpdateSurface(_OffScreenPlainSurface, NULL, BackBuffer, NULL);
    BackBuffer->Release();
}

#endif