/*
D3D9RenderTargetSurface.h
Written by Matthew Fisher

D3D9RenderTargetSurface is a surface that can be used as a render target.
*/

#ifdef USE_D3D9
class D3D9RenderTargetSurface : public GraphicsAsset
{
public:
    D3D9RenderTargetSurface();
    ~D3D9RenderTargetSurface();

    void FreeMemory();
    void ReleaseMemory();
    void Reset(GraphicsDevice &graphics);

    void Init(D3D9GraphicsDevice &GD, D3DFORMAT format, UINT width, UINT height);
    bool ReSizeToBackBuffer(D3D9GraphicsDevice &GD, D3DFORMAT format);
    void SetAsRenderTarget(D3D9GraphicsDevice &GD, UINT index = 0);
    void CopySurfaceToOffScreen(D3D9GraphicsDevice &GD);
    void CopyOffScreenToBackBuffer(D3D9GraphicsDevice &GD);

    __forceinline UINT Width()
    {
        return _Width;
    }
    __forceinline UINT Height()
    {
        return _Height;
    }

    __forceinline LPDIRECT3DSURFACE9 OffScreenPlainSurface()
    {
        return _OffScreenPlainSurface;
    }

private:
    LPDIRECT3DSURFACE9 _Surface;
    LPDIRECT3DSURFACE9 _DepthSurface;
    LPDIRECT3DSURFACE9 _OffScreenPlainSurface;
    UINT _Width, _Height;
    D3DFORMAT _Format;
};

#endif