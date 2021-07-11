/*
D3D9VertexShader.cpp
Written by Matthew Fisher

D3D9VertexShader wraps the IDirect3DVertexShader9 object and an associated ID3DXConstantTable.
*/

#ifdef USE_D3D9

D3D9VertexShader::D3D9VertexShader()
{
    _Shader = NULL;
    _device = NULL;
    _constantTable = NULL;
}

D3D9VertexShader::~D3D9VertexShader()
{
    FreeMemory();
}

void D3D9VertexShader::FreeMemory()
{
    if(_Shader)
    {
        _Shader->Release();
        _Shader = NULL;
    }
    if(_constantTable)
    {
        _constantTable->Release();
        _constantTable = NULL;
    }
}

void D3D9VertexShader::ReleaseMemory()
{
    FreeMemory();
}

void D3D9VertexShader::Reset(GraphicsDevice &graphics)
{
    FreeMemory();

    HRESULT hr;

    _device = graphics.CastD3D9().GetDevice();
    Assert(_device != NULL, "_device == NULL");

    _declaration.Init(_device);

    // Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
    // shader debugger. Debugging vertex shaders requires either REF or software vertex 
    // processing, and debugging pixel shaders requires REF.  The 
    // D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
    // shader debugger.  It enables source level debugging, prevents instruction 
    // reordering, prevents dead code elimination, and forces the compiler to compile 
    // against the next higher available software target, which ensures that the 
    // unoptimized shaders do not exceed the shader model limitations.  Setting these 
    // flags will cause slower rendering since the shaders will be unoptimized and 
    // forced into software.  See the DirectX documentation for more information about 
    // using the shader debugger.
    DWORD dwShaderFlags = 0;
    #ifdef DEBUG_VS
        dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION|D3DXSHADER_DEBUG;
    #endif

    LPD3DXBUFFER pCode = NULL;
    LPD3DXBUFFER pErrors = NULL;

    PersistentAssert(Utility::FileExists(_shaderFile), String(_shaderFile) + String(" not found."));

    // Assemble the vertex shader from the file
    hr = D3DXCompileShaderFromFile( _shaderFile.CString(), NULL, NULL, "VShaderEntry",
                                    "vs_3_0", dwShaderFlags, &pCode,
                                    &pErrors, &_constantTable );
    
    String ErrorString;
    if(pErrors)
    {
        char *ErrorMessage = (char *)pErrors->GetBufferPointer();
        DWORD ErrorLength = pErrors->GetBufferSize();

        ofstream file("ShaderDebug.txt");
        for(UINT i = 0; i < ErrorLength; i++)
        {
            file << ErrorMessage[i];
            ErrorString += String(ErrorMessage[i]);
        }
        file.close();
    }

    PersistentAssert(!FAILED(hr), String("D3DXCompileShaderFromFile failed: ") + ErrorString);

    // Create the vertex shader
    hr = _device->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                            &_Shader );

    if(pErrors)
    {
        pErrors->Release();
    }
    if(pCode)
    {
        pCode->Release();
    }
    Assert(!FAILED(hr), "CreateVertexShader failed");
}

void D3D9VertexShader::Init(GraphicsDevice &graphics, const String &filename)
{
    _shaderFile = filename;
    Reset(graphics);
}

void D3D9VertexShader::Set()
{
    _declaration.Set();
    //
    // SetVertexShader will fail when device is lost
    //
    //D3DValidate( _device->SetVertexShader(_Shader), "SetVertexShader");
    _device->SetVertexShader(_Shader);
}

#endif