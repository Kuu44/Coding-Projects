/*
D3D9RenderTargetTexture.h
Written by Matthew Fisher

The D3D9ProtectRenderTarget class is used to simplify preserving a device's current render target and depth buffer
so new ones can easily be overlayed, and then the original render target and depth buffer restored.
D3D9RenderTargetTexture is a texture that can be used as a render target.  It has its own associated depth buffer.
*/

#ifdef USE_D3D9

class D3D9ProtectRenderTarget
{
public:

    D3D9ProtectRenderTarget(LPDIRECT3DDEVICE9 Device, bool ProtectDepthBuffer, bool Enabled)
    {
        _Enabled = Enabled;
        _RenderTarget = NULL;
        _DepthStencilSurface = NULL;
        if(_Enabled)
        {
            _ProtectDepthBuffer = ProtectDepthBuffer;
            Device->GetViewport(&_Viewport);
            Device->GetRenderTarget(0, &_RenderTarget);
            if(ProtectDepthBuffer)
            {
                Device->GetDepthStencilSurface(&_DepthStencilSurface);
            }
            _Device = Device;
        }
    }

    ~D3D9ProtectRenderTarget()
    {
        if(_Enabled)
        {
            if(_RenderTarget)
            {
                _Device->SetRenderTarget(0, _RenderTarget);
            }
            _Device->SetRenderTarget(1, NULL);
            _Device->SetRenderTarget(2, NULL);
            _Device->SetRenderTarget(3, NULL);
            if(_ProtectDepthBuffer && _DepthStencilSurface != NULL)
            {
                _Device->SetDepthStencilSurface(_DepthStencilSurface);
            }
            _Device->SetViewport(&_Viewport);

            if(_RenderTarget != NULL)
            {
                _RenderTarget->Release();
            }
            if(_ProtectDepthBuffer && _DepthStencilSurface != NULL)
            {
                _DepthStencilSurface->Release();
            }
        }
    }

private:
    LPDIRECT3DDEVICE9        _Device;
    LPDIRECT3DSURFACE9       _RenderTarget;
    LPDIRECT3DSURFACE9       _DepthStencilSurface;
    D3DVIEWPORT9             _Viewport;
    bool                     _Enabled;
    bool                     _ProtectDepthBuffer;
};

class D3D9RenderTargetTexture : public GraphicsAsset
{
public:
    D3D9RenderTargetTexture();
    ~D3D9RenderTargetTexture();
    void FreeMemory();
    void ReleaseMemory();

    void Reset(LPDIRECT3DDEVICE9 Device);
    void Init(LPDIRECT3DDEVICE9 Device, UINT Width, UINT Height, bool createDepthSurface);
    void SetAsRenderTarget();
    void SetAsTexture(UINT Stage);

    void SetData(const Bitmap &B);
    void GetData(Bitmap &B);
    void GetData(Bitmap &B, const Rectangle2i &Source, const Rectangle2i &Dest);

    void GetDepthData(Grid<float> &DepthMap);

    void RenderStringToBmp(const D3D9Font &Font, const String &Text, const Rectangle2i &Region, RGBColor FontColor, RGBColor BackgroundColor, Bitmap &Bmp);

private:
    Bitmap              _DataCopy;
    LPDIRECT3DSURFACE9  _DepthSurface;
    LPDIRECT3DSURFACE9  _Surface;
    LPDIRECT3DSURFACE9  _SurfacePlain;
    LPDIRECT3DSURFACE9  _SurfaceResizing;
    LPDIRECT3DTEXTURE9  _Texture;
    LPDIRECT3DDEVICE9   _Device;
    UINT                _Width;
    UINT                _Height;
};

#endif