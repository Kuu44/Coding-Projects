/*
D3D10Mesh.cpp
Written by Matthew Fisher

D3D10Mesh is a D3D 10 instance of the BaseMesh class.
In general all these functions just call DirectX equivalents.
Most of the functionality is gained through the BaseMesh functions.
*/

#ifdef USE_D3D10

const D3D10_INPUT_ELEMENT_DESC MeshVertexD3D10Declaration[] =
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(Vec3f), D3D10_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, sizeof(Vec3f) + sizeof(Vec3f), D3D10_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vec3f) + sizeof(Vec3f) + sizeof(RGBColor), D3D10_INPUT_PER_VERTEX_DATA, 0 },
};

const int MeshVertexD3D10DeclarationElements = sizeof( MeshVertexD3D10Declaration ) / sizeof( MeshVertexD3D10Declaration[0] );


D3D10Mesh::D3D10Mesh()
{
    _Mesh = NULL;
    _GD = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    _StagingVertexBuffer = NULL;
    _StagingIndexBuffer = NULL;
}

D3D10Mesh::D3D10Mesh(GraphicsDevice &_GD)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    _StagingVertexBuffer = NULL;
    _StagingIndexBuffer = NULL;
    SetGD(_GD);
}

D3D10Mesh::D3D10Mesh(const BaseMesh &O)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    _StagingVertexBuffer = NULL;
    _StagingIndexBuffer = NULL;
    O.CopyMesh(*this);
}

D3D10Mesh::D3D10Mesh(const D3D10Mesh &O)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    _StagingVertexBuffer = NULL;
    _StagingIndexBuffer = NULL;
    O.CopyMesh(*this);
}

D3D10Mesh::~D3D10Mesh()
{
    FreeMemory();
}

void D3D10Mesh::FreeMemory()
{
    Commit();
    if(_StagingVertexBuffer)
    {
        _StagingVertexBuffer->Release();
        _StagingVertexBuffer = NULL;
    }
    if(_StagingIndexBuffer)
    {
        _StagingIndexBuffer->Release();
        _StagingIndexBuffer = NULL;
    }
    if(_Mesh)
    {
        _Mesh->Discard(D3DX10_MESH_DISCARD_DEVICE_BUFFERS);
        _Mesh->Release();
        _Mesh = NULL;
    }
    _Vertices = NULL;
    _Indices = NULL;
}


void D3D10Mesh::Allocate(UINT NewVertexCount, UINT NewFaceCount)
{
    FreeMemory();
    if(NewVertexCount == 0 || NewFaceCount == 0)
    {
        return;
    }

    D3DX10CreateMesh(GetGD().CastD3D10().GetDevice(), MeshVertexD3D10Declaration, MeshVertexD3D10DeclarationElements, 0, NewVertexCount, NewFaceCount, D3DX10_MESH_32_BIT, &_Mesh);
    PersistentAssert(_Mesh != NULL, "D3DX10CreateMesh failed");

    _Mesh->GetVertexBuffer(0, &_StagingVertexBuffer);
    _Mesh->GetIndexBuffer(&_StagingIndexBuffer);
    Lock();
    Commit();
}

D3D10Mesh& D3D10Mesh::operator = (const BaseMesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

D3D10Mesh& D3D10Mesh::operator = (const D3D10Mesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

ID3DX10Mesh* D3D10Mesh::GetMesh() const
{
    return _Mesh;
}

UINT D3D10Mesh::VertexCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetVertexCount();
    }
}

UINT D3D10Mesh::FaceCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetFaceCount();
    }
}

UINT D3D10Mesh::IndexCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetFaceCount() * 3;
    }
}

void D3D10Mesh::Lock() const
{
    if(_Mesh != NULL && _Vertices == NULL)
    {
        SIZE_T Size;
        _StagingVertexBuffer->Map((void **)&_Vertices, &Size);
        _StagingIndexBuffer->Map((void **)&_Indices, &Size);
    }
}

void D3D10Mesh::Commit() const
{
    if(_Vertices != NULL)
    {
        _StagingVertexBuffer->Unmap();
        _StagingIndexBuffer->Unmap();
        _Mesh->CommitToDevice();
        _Vertices = NULL;
        _Indices = NULL;
    }
}

MeshVertex* D3D10Mesh::Vertices()
{
    if(_Vertices == NULL)
    {
        Lock();
    }
    return _Vertices;
}

DWORD* D3D10Mesh::Indices()
{
    if(_Indices == NULL)
    {
        Lock();
    }
    return _Indices;
}

const MeshVertex* D3D10Mesh::Vertices() const
{
    if(_Vertices == NULL)
    {
        Lock();
    }
    return _Vertices;
}

const DWORD* D3D10Mesh::Indices() const
{
    if(_Indices == NULL)
    {
        Lock();
    }
    return _Indices;
}

/*void D3D10Mesh::LoadMesh(LPD3DXMESH _mesh)
{
    FreeMemory();
    _mesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFlags, GetD3DDevice(), &Mesh);
}*/

void D3D10Mesh::Render(UINT Subset) const
{
    Commit();
    if(_Mesh)
    {
        _Mesh->DrawSubset(Subset);
        ID3D10Buffer *NullBuffer = NULL;
        UINT Zero = 0;
        GetGD().CastD3D10().GetDevice()->IASetVertexBuffers(0, 1, &NullBuffer, &Zero, &Zero);
        GetGD().CastD3D10().GetDevice()->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
    }
}

void D3D10Mesh::Render() const
{
    Render(0);
}

void D3D10Mesh::Optimize()
{
    //Commit();
    //_Mesh->GenerateGSAdjacency();

    //ID3D10InfoQueue *DebugQueue = NULL;
    //GetGD().CastD3D10().GetDevice()->QueryInterface( __uuidof(ID3D10InfoQueue), (void **)&DebugQueue);
    //Assert(DebugQueue != NULL, "QueryInterface failed");
    //UINT StartCount = DebugQueue->GetNumStoredMessages();
    //UINT EndCount = DebugQueue->GetNumStoredMessages();

    HRESULT hr = _Mesh->GenerateAdjacencyAndPointReps(1e-5f);
    Assert(SUCCEEDED(hr), "_Mesh->GenerateAdjacencyAndPointReps failed");

    _Mesh->Optimize(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_STRIPREORDER, NULL, NULL);
}

#endif