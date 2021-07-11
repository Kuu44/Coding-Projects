/*
Controller.h
Written by Matthew Fisher

MainControl includes everything that changes often between applications, such as what meshes to load,
and also determines what is rendered each frame.
*/

struct AppState;

struct AppAssets
{
    D3D9Font         font;
    D3D9VertexShader vsBase;
    D3D9PixelShader  psBase;
    D3D9Mesh         surface;
};

class Controller : public GraphicsDeviceCallbacks
{
public:
    void Init(AppState &state);
    void Init3D();
    
    void FreeMemory();

    void ReSize();
    
    void ReleaseAssets();
    void ResetAssets();
    
    void Frame();

private:
    void InitMenu();
    
    void InitAssets();
    void ReloadTextures();
    
    void ProcessEvents();
    void ProcessKeyboardInput();
    
    void ResetCamera();
    void UpdateCamera();

    void StatusText();
    void Status(const String &s, RGBColor c);

    void UpdateIsoSurface();
    
    void Render();
    
    AppState*     _state;

    MenuInterface _menu;

    Matrix4       _projection;
    Camera        _camera;

    UINT          _consoleY;

    AppAssets              _assets;
    Vector<GraphicsAsset*> _assetList;

    static const UINT FunctionCount = 3;
    float (*_functions[FunctionCount])(const Vec3f &Pos);
    UINT _functionIndex;
};
