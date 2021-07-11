/*
D3D9PixelShader.cpp
Written by Matthew Fisher

D3D9PixelShader wraps the IDirect3DPixelShader9 object and an associated ID3DXConstantTable.
*/

#ifdef USE_D3D9

D3D9PixelShader::D3D9PixelShader()
{
    _shader = NULL;
    _device = NULL;
    _constantTable = NULL;
}
D3D9PixelShader::~D3D9PixelShader()
{
    FreeMemory();
}

void D3D9PixelShader::FreeMemory()
{
    if(_shader)
    {
        _shader->Release();
        _shader = NULL;
    }
    if(_constantTable)
    {
        _constantTable->Release();
        _constantTable = NULL;
    }
}

void D3D9PixelShader::ReleaseMemory()
{
    FreeMemory();
}

void D3D9PixelShader::Reset(GraphicsDevice &graphics)
{
    FreeMemory();

    HRESULT hr;

    _device = graphics.CastD3D9().GetDevice();
    Assert(_device != NULL, "_device == NULL");

    DWORD dwShaderFlags = 0;
    #ifdef DEBUG_PS
        dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION | D3DXSHADER_DEBUG;
    #endif

    LPD3DXBUFFER pCode = NULL;
    LPD3DXBUFFER pErrors = NULL;

    PersistentAssert(Utility::FileExists(_shaderFile), String("Shader file not found: ") + _shaderFile);

    // Assemble the vertex shader from the file
    hr = D3DXCompileShaderFromFile( _shaderFile.CString(), NULL, NULL, "PShaderEntry",
                                    "ps_3_0", dwShaderFlags, &pCode,
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

    hr = _device->CreatePixelShader( (DWORD*)pCode->GetBufferPointer(),
                                            &_shader );

    if(pErrors)
    {
        pErrors->Release();
    }
    if(pCode)
    {
        pCode->Release();
    }
    PersistentAssert(!FAILED(hr), "CreatePixelShader failed");
}

void D3D9PixelShader::Init(GraphicsDevice &graphics, const String &filename)
{
    _shaderFile = filename;
    Reset(graphics);
}

void D3D9PixelShader::Set()
{
    D3DValidate( _device->SetPixelShader(_shader), "SetPixelShader");
}

#endif