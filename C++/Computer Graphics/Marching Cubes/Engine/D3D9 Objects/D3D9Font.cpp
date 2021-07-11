/*
D3D9Font.cpp
Written by Matthew Fisher

D3D9Font wraps the ID3DXFont object.
*/

#ifdef USE_D3D9

D3D9Font::D3D9Font()
{
    _Font = NULL;
    _Device = NULL;
}

D3D9Font::~D3D9Font()
{
    FreeMemory();
}

void D3D9Font::FreeMemory()
{
    if(_Font)
    {
        _Font->Release();
        _Font = NULL;
    }
    _Device = NULL;
}

void D3D9Font::ReleaseMemory()
{
    FreeMemory();
}

void D3D9Font::Reset(GraphicsDevice &graphics)
{
    FreeMemory();

    _Device = graphics.CastD3D9().GetDevice();
    Assert(_Device != NULL, "Device == NULL");

    HRESULT hr;
    hr = D3DXCreateFont(
            _Device,
            _FontHeight,                 // Height
            0,                           // Width
            _FontWeight,                 // Weight
            1,                           // MipLevels, 0 = autogen mipmaps
            FALSE,                       // Italic
            DEFAULT_CHARSET,             // CharSet
            OUT_DEFAULT_PRECIS,          // OutputPrecision
            DEFAULT_QUALITY,             // Quality
            DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
            _FontName.CString(),         // pFaceName
            &_Font);                     // ppFont
    Assert(SUCCEEDED(hr) && _Font != NULL, "D3DXCreateFont failed");
}

void D3D9Font::Init(GraphicsDevice &graphics, const String &FontName, int FontHeight, int FontWeight)
{
    _FontName = FontName;
    _FontHeight = FontHeight;
    _FontWeight = FontWeight;
    Reset(graphics);
}

void D3D9Font::DrawString(const String &Text, const Vec2i &TopLeft, RGBColor Color) const
{
    Rectangle2i Rect(Rectangle2i(TopLeft, Vec2i(TopLeft.x + 2048, TopLeft.y)));
    DrawString(Text, Rect, Color);
}

void D3D9Font::DrawString(const String &Text, const Vec2i &TopLeft, UINT Width, RGBColor Color) const
{
    Rectangle2i Rect(Rectangle2i(TopLeft, Vec2i(TopLeft.x + Width, TopLeft.y)));
    DrawString(Text, Rect, Color);
}

void D3D9Font::DrawString(const String &Text, const Rectangle2i &Rect, RGBColor Color) const
{
    RECT CurRect = Rect.ToRect();
    HRESULT CoopLevel = _Device->TestCooperativeLevel();
    if(CoopLevel == D3D_OK)
    {
        _Font->DrawText( NULL, Text.CString(), Text.Length(), &CurRect, DT_WORDBREAK | DT_CALCRECT, 0 );
        _Font->DrawText( NULL, Text.CString(), Text.Length(), &CurRect, DT_WORDBREAK | DT_NOCLIP, D3DXCOLOR(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, 1.0f ));
    }
}

#endif