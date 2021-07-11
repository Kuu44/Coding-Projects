/*
D3D9Font.h
Written by Matthew Fisher

D3D9Font wraps the ID3DXFont object.
*/

#ifdef USE_D3D9

class D3D9Font : public GraphicsAsset
{
public:
    D3D9Font();
    ~D3D9Font();

    void ReleaseMemory();
    void FreeMemory();
    void Reset(GraphicsDevice &graphics);

    void Init(GraphicsDevice &graphics, const String &FontName, int FontHeight, int FontWeight);
    void DrawString(const String &Text, const Vec2i &TopLeft, RGBColor Color) const;
    void DrawString(const String &Text, const Vec2i &TopLeft, UINT Width, RGBColor Color) const;
    void DrawString(const String &Text, const Rectangle2i &Rect, RGBColor Color) const;
    
private:
    LPDIRECT3DDEVICE9 _Device;
    LPD3DXFONT _Font;
    int _FontHeight;
    int _FontWeight;
    String _FontName;
};

#endif