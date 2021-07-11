/*
D3DGraphicsDevice.h
Written by Matthew Fisher

a D3D instance of GraphicsDevice.  The only new functionality is GetDevice() which returns
the D3DDevice associated with this graphics device.
*/

#ifdef USE_D3D9

class D3D9GraphicsDevice : public GraphicsDevice
{
public:
    D3D9GraphicsDevice();
    ~D3D9GraphicsDevice();

    void FreeMemory();
    void Init(const GraphicsDeviceParameters &parameters, ApplicationWindow &window);
    void Init(const GraphicsDeviceParameters &Parameters, HWND Window, UINT Width, UINT Height);

    void ReSize(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks);

    bool StartRender();
    void FinishRender(ApplicationWindow &window, GraphicsDeviceCallbacks &callbacks);

    void CaptureDesktop(ApplicationWindow &window, Bitmap &bmp);
    void CaptureScreen(ApplicationWindow &window, Bitmap &bmp);

    LPDIRECT3DDEVICE9 GetDevice();
    
    void ClearTexture(UINT index);
    void ToggleWireframe();

    void Render(const Mesh &m);

private:
    void LoadPresentParameters(D3DPRESENT_PARAMETERS &PresentParameters, HWND Window, UINT Width, UINT Height);
    void InitializeStateMachine();

    LPDIRECT3D9        _d3d;
    LPDIRECT3DDEVICE9  _device;
    LPDIRECT3DSURFACE9 _desktopSurface;
    LPDIRECT3DSURFACE9 _windowSurface;
    bool               _assetsReleased;
};

#endif