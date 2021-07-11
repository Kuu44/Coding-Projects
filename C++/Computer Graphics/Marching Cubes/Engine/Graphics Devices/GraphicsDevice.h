/*
GraphicsDevice.h
Written by Matthew Fisher

GraphicsDevice is the abstract class that contains functionality that all graphics devices must expose.
any GraphicsDevice can do simple things like render meshes into the main rendering window and handle
the world, view and projection transforms.
*/

//
// Allowed graphics device types
//
enum GraphicsDeviceType
{
    GD_D3D9 = 1,
};

struct GraphicsDeviceParameters
{
    GraphicsDeviceParameters()
    {
        MultisampleCount = 0;
        ScreenColor = RGBColor::Black;
        WaitForVSync = false;
    }
    String MainFontName;
    UINT MultisampleCount;
    RGBColor ScreenColor;
    bool WaitForVSync;
};

class GraphicsDeviceCallbacks
{
public:
    virtual void ReleaseAssets() = 0;
    virtual void ResetAssets() = 0;
};

class GraphicsDevice
{
public:
    virtual void FreeMemory() = 0;
    virtual void Init(const GraphicsDeviceParameters &parameters, ApplicationWindow &window) = 0;

    virtual void ReSize(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks) = 0;

    virtual bool StartRender() = 0;
    virtual void FinishRender(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks) = 0;
    
    virtual void Render(const Mesh &m) = 0;
    virtual void CaptureScreen(ApplicationWindow &window, Bitmap &bmp) = 0;

    //
    // State modifiers
    //
    virtual void ClearTexture(UINT Index) = 0;
    virtual void ToggleWireframe() = 0;

    //
    // Accessors
    //
    GraphicsDeviceType Type() const
    {
        return _type;
    }
    __forceinline const GraphicsDeviceParameters& Parameters() const
    {
        return _parameters;
    }
    __forceinline GraphicsDeviceParameters& Parameters()
    {
        return _parameters;
    }

    //
    // Cast
    //
    D3D9GraphicsDevice& CastD3D9()
    {
        Assert(_type == GD_D3D9, "Invalid graphics device cast");
        return *((D3D9GraphicsDevice*)this);
    }

protected:
    GraphicsDeviceType _type;
    GraphicsDeviceParameters _parameters;
};
