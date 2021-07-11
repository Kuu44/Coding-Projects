/*
D3D9Texture.cpp
Written by Matthew Fisher

DirectX implementation of BaseTexture.  See BaseTexture.h for a definiton of the base functions.
*/

#ifdef USE_D3D9

D3D9Texture::D3D9Texture()
{
    _SurfaceTopLevel = NULL;
    _Texture = NULL;
    _SurfacePlain = NULL;
    _Device = NULL;
    _Width = 0;
    _Height = 0;
    _RenderTarget = false;
}

D3D9Texture::~D3D9Texture()
{
    FreeMemory();
}

void D3D9Texture::FreeMemory()
{
    ReleaseMemory();
    if(_SurfacePlain != NULL)
    {
        D3DValidateRelease(_SurfacePlain);
        _SurfacePlain = NULL;
    }
    _RenderTarget = false;
}

void D3D9Texture::ReleaseMemory()
{
    if(_Texture != NULL)
    {
        ULONG References = _Texture->Release();
        //Assert(References == 0, "Non-zero reference count");
        _Texture = NULL;
    }
    if(_SurfaceTopLevel != NULL)
    {
        D3DValidateRelease(_SurfaceTopLevel);
        _SurfaceTopLevel = NULL;
    }
    _Width = 0;
    _Height = 0;
}

void D3D9Texture::Init(GraphicsDevice &graphics)
{
    _Device = graphics.CastD3D9().GetDevice();
}

void D3D9Texture::Reset(GraphicsDevice &graphics)
{
    _Device = graphics.CastD3D9().GetDevice();
}

void D3D9Texture::UpdateMipMapLevels()
{
    //D3DXFilterTexture(_Texture, NULL, 0, D3DX_DEFAULT);
}

void D3D9Texture::Allocate(D3DFORMAT Format, UINT Width, UINT Height, bool RenderTarget, UINT MipmapLevels)
{
    if(_Width != Width || _Height != Height || _Format != Format || _RenderTarget != RenderTarget)
    {
        FreeMemory();
        PersistentAssert(_Device != NULL, "D3D9Texture not associated");
        
        DWORD Usage = 0;

		if(MipmapLevels != 1)
		{
			Usage |= D3DUSAGE_AUTOGENMIPMAP;
		}
        
        D3DPOOL Pool = D3DPOOL_MANAGED;

        /*if(Format == D3DFMT_DXT1)
        {
            while((Width & 3) != 0)
            {
                Width--;
            }
            while((Height & 3) != 0)
            {
                Height--;
            }
            if(Width == 0) Width = 4;
            if(Height == 0) Height = 4;
        }*/

        if(RenderTarget)
        {
            Usage |= D3DUSAGE_RENDERTARGET;
            Pool = D3DPOOL_DEFAULT;
            D3DAlwaysValidate(_Device->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SYSTEMMEM, &_SurfacePlain, NULL), "CreateOffscreenPlainSurface");
        }
        
        D3DAlwaysValidate(_Device->CreateTexture(Width, Height, MipmapLevels, Usage, Format, Pool, &_Texture, NULL), "CreateTexture");
        D3DValidate(_Texture->GetSurfaceLevel(0, &_SurfaceTopLevel), "GetSurfaceLevel");
        _Width = Width;
        _Height = Height;
        _Format = Format;
        _RenderTarget = RenderTarget;
    }
}

void D3D9Texture::Clear()
{
    //
    // requires D3DPOOL_DEFAULT
    //
    _Device->ColorFill(_SurfaceTopLevel, NULL, D3DCOLOR_ARGB(0, 0, 0, 0));
}

void D3D9Texture::Load(const Bitmap &Bmp)
{
    Allocate(D3DFMT_A8R8G8B8, Bmp.Width(), Bmp.Height(), false, 0);
    D3DLOCKED_RECT Rect;
    D3DValidate(_Texture->LockRect(0, &Rect, NULL, 0), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        RGBColor *CurRow = (RGBColor *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            RGBColor Color = Bmp[y][x];
            CurRow[x] = RGBColor(Color.b, Color.g, Color.r, Color.a);
        }
    }
    D3DValidate(_Texture->UnlockRect(0), "UnlockRect");
    UpdateMipMapLevels();
}

void D3D9Texture::LoadFromFile(const String &filename, D3DFORMAT format)
{
    FreeMemory();
    D3DValidate(D3DXCreateTextureFromFileEx(_Device, filename.CString(), 0, 0, 0, 0, format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &_Texture), "D3DXCreateTextureFromFileEx");
    _Width = 1;
    _Height = 1;
    _Format = format;
    _RenderTarget = false;
}

void D3D9Texture::Load(const Grid<float> &Data)
{
    Allocate(D3DFMT_R32F, Data.Cols(), Data.Rows(), false, 0);
    D3DLOCKED_RECT Rect;
    D3DValidate(_Texture->LockRect(0, &Rect, NULL, 0), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        float *CurRow = (float *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            CurRow[x] = Data(y, x);
        }
    }
    D3DValidate(_Texture->UnlockRect(0), "UnlockRect");
}

void D3D9Texture::Load(const Grid<Vec2f> &Data)
{
    Allocate(D3DFMT_G32R32F, Data.Cols(), Data.Rows(), false, 0);
    D3DLOCKED_RECT Rect;
    D3DValidate(_Texture->LockRect(0, &Rect, NULL, 0), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec2f *CurRow = (Vec2f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            CurRow[x] = Data(y, x);
        }
    }
    D3DValidate(_Texture->UnlockRect(0), "UnlockRect");
}

void D3D9Texture::Load(const Grid<Vec3f> &Data)
{
    Allocate(D3DFMT_A32B32G32R32F, Data.Cols(), Data.Rows(), false, 0);
    D3DLOCKED_RECT Rect;
    D3DValidate(_Texture->LockRect(0, &Rect, NULL, 0), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec4f *CurRow = (Vec4f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            CurRow[x] = Vec4f(Data(y, x), 0.0f);
        }
    }
    D3DValidate(_Texture->UnlockRect(0), "UnlockRect");
}

void D3D9Texture::Load(const Grid<Vec4f> &Data)
{
    Allocate(D3DFMT_A32B32G32R32F, Data.Cols(), Data.Rows(), false, 0);
    D3DLOCKED_RECT Rect;
    D3DValidate(_Texture->LockRect(0, &Rect, NULL, 0), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec4f *CurRow = (Vec4f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            CurRow[x] = Data(y, x);
        }
    }
    D3DValidate(_Texture->UnlockRect(0), "UnlockRect");
}

void D3D9Texture::Load(D3D9Texture &Tex)
{
    D3DAlwaysValidate(_Device->StretchRect(Tex.SurfaceTopLevel(), NULL, _SurfaceTopLevel, NULL, D3DTEXF_POINT), "StretchRect");
}

void D3D9Texture::ReadData(Bitmap &Bmp)
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_A8R8G8B8 && _RenderTarget, "ReadData called on invalid surface");
    Bmp.Allocate(_Width, _Height);
    D3DLOCKED_RECT Rect;
    D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
    D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        RGBColor *CurRow = (RGBColor *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            Bmp[y][x] = CurRow[x];
        }
    }
    D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
}

void D3D9Texture::ReadData(Grid<float> &Data)
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_R32F, "ReadData called on invalid surface");
    Data.Allocate(_Height, _Width);
    D3DLOCKED_RECT Rect;
    if(_RenderTarget)
    {
        D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
        D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    }
    else
    {
        D3DAlwaysValidate(_SurfaceTopLevel->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    }
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        float *CurRow = (float *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            Data(y, x) = CurRow[x];
        }
    }
    if(_RenderTarget)
    {
        D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
    }
    else
    {
        D3DValidate(_SurfaceTopLevel->UnlockRect(), "UnlockRect");
    }
}

void D3D9Texture::ReadData(Grid<Vec2f> &Data)
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_G32R32F && _RenderTarget, "ReadData called on invalid surface");
    Data.Allocate(_Height, _Width);
    D3DLOCKED_RECT Rect;
    D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
    D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec2f *CurRow = (Vec2f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            Data(y, x) = CurRow[x];
        }
    }
    D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
}

void D3D9Texture::ReadData(Grid<Vec3f> &Data)
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_A32B32G32R32F && _RenderTarget, "ReadData called on invalid surface");
    Data.Allocate(_Height, _Width);
    D3DLOCKED_RECT Rect;
    D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
    D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec4f *CurRow = (Vec4f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            Data(y, x) = Vec3f(CurRow[x].x, CurRow[x].y, CurRow[x].z);
        }
    }
    D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
}

void D3D9Texture::ReadData(Grid<Vec4f> &Data)
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_A32B32G32R32F && _RenderTarget, "ReadData called on invalid surface");
    Data.Allocate(_Height, _Width);
    D3DLOCKED_RECT Rect;
    D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
    D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    BYTE *Bytes = (BYTE *)Rect.pBits;
    for(UINT y = 0; y < _Height; y++)
    {
        Vec4f *CurRow = (Vec4f *)(Bytes + y * Rect.Pitch);
        for(UINT x = 0; x < _Width; x++)
        {
            Data(y, x) = CurRow[x];
        }
    }
    D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
}

void D3D9Texture::Flush()
{
    PersistentAssert(_Width != 0 && _Height != 0 && _Format == D3DFMT_A32B32G32R32F && _RenderTarget, "ReadData called on invalid surface");
    D3DLOCKED_RECT Rect;
    D3DAlwaysValidate(_Device->GetRenderTargetData(_SurfaceTopLevel, _SurfacePlain), "GetRenderTargetData");
    D3DAlwaysValidate(_SurfacePlain->LockRect(&Rect, NULL, D3DLOCK_READONLY), "LockRect");
    D3DValidate(_SurfacePlain->UnlockRect(), "UnlockRect");
}

void D3D9Texture::Set(int Index)
{
    Assert(_Texture != NULL, "SetTexture called on empty texture");
    _Device->SetTexture(Index, _Texture);
}

void D3D9Texture::SetAsRenderTarget(int Index)
{
    Assert(_Texture != NULL && _RenderTarget, "SetAsRenderTarget on invalid texture");
    D3DValidate(_Device->SetRenderTarget(Index, _SurfaceTopLevel), "SetRenderTarget");
}

void D3D9Texture::SetNull(int Index)
{
    _Device->SetTexture(Index, NULL);
}

#endif