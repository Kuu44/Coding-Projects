/*
D3D9VertexShader.h
Written by Matthew Fisher

D3D9VertexShader wraps the IDirect3DVertexShader9 object and an associated ID3DXConstantTable.
*/

#ifdef USE_D3D9

class D3D9VertexShader : public GraphicsAsset
{
public:
    D3D9VertexShader();
    ~D3D9VertexShader();

    void FreeMemory();
    void ReleaseMemory();
    void Reset(GraphicsDevice &device);

    void Init(GraphicsDevice &graphics, const String &Filename);
    void Set();

    void SetMatrix(const char *Name, const Matrix4 &M)
    {
        D3DXMATRIX DM = M;
        D3DValidate( _constantTable->SetMatrix(_device, Name, &DM), "SetMatrix" );
    }
    void SetFloat(const char *Name, float Value)
    {
        D3DValidate( _constantTable->SetFloat(_device, Name, Value), "SetFloat" );
    }
    void SetVec2(const char *Name, const Vec2f &V)
    {
        const float V2[2] = {V.x, V.y};
        D3DValidate( _constantTable->SetFloatArray(_device, Name, V2, 2), "SetFloatArray" );
    }
    void SetVec3(const char *Name, const Vec3f &V)
    {
        const float V3[3] = {V.x, V.y, V.z};
        D3DValidate( _constantTable->SetFloatArray(_device, Name, V3, 3), "SetFloatArray" );
    }
    void SetVec4(const char *Name, const Vec4f &V)
    {
        const float V4[4] = {V.x, V.y, V.z, V.w};
        D3DValidate( _constantTable->SetFloatArray(_device, Name, V4, 4), "SetFloatArray" );
    }
    LPDIRECT3DDEVICE9 Device()
    {
        return _device;
    }

private:
    String                  _shaderFile;
    D3D9VertexDeclaration   _declaration;
    LPDIRECT3DVERTEXSHADER9 _Shader;
    LPDIRECT3DDEVICE9       _device;
    LPD3DXCONSTANTTABLE     _constantTable;
};

#endif