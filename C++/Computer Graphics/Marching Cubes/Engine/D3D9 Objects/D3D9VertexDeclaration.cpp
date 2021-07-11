/*
D3D9VertexDeclaration.cpp
Written by Matthew Fisher

D3D9VertexDeclaration is a wrapper around the D3D9 IDirect3DVertexDeclaration9 object.
*/

#ifdef USE_D3D9

D3DVERTEXELEMENT9 VertexDecleration[] =
{
    { 0, FIELD_OFFSET(MeshVertex, Pos),            D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, FIELD_OFFSET(MeshVertex, Normal),        D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
    { 0, FIELD_OFFSET(MeshVertex, TexCoord),    D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
};

D3D9VertexDeclaration::D3D9VertexDeclaration()
{
    Decleration = NULL;
    Device = NULL;
}

void D3D9VertexDeclaration::Init(LPDIRECT3DDEVICE9 _Device)
{
    Device = _Device;
    HRESULT hr = Device->CreateVertexDeclaration(VertexDecleration, &Decleration);
    Assert(!FAILED(hr), "CreateVertexDecleration failed.");
}

void D3D9VertexDeclaration::Set()
{
    HRESULT hr = Device->SetVertexDeclaration(Decleration);
}

#endif