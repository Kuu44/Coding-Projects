/*
Mesh.cpp
Written by Matthew Fisher

Mesh is a standard C++ array instance of the BaseMesh class.  It's the only kind that can be used by OpenGL,
but it will run fine under DirectX as well (if not as quickly as a D3DMesh.)  Mesh gets all of its
functionality from BaseMesh and has no features not defined by BaseMesh.  None of the functions here are very suprising.
*/

void Mesh::Render() const
{
    GetGD().Render(*this);
}

Mesh::Mesh()
{
    _Vertices = 0;
    _Indices = 0;
    _VertexCount = 0;
    _IndexCount = 0;
    _GD = 0;
}

Mesh::Mesh(GraphicsDevice &GD)
{
    _Vertices = 0;
    _Indices = 0;
    _VertexCount = 0;
    _IndexCount = 0;
    SetGD(GD);
}

Mesh::Mesh(BaseMesh &O)
{
    _Vertices = 0;
    _Indices = 0;
    _VertexCount = 0;
    _IndexCount = 0;
    O.CopyMesh(*this);
}

Mesh::Mesh(const Mesh &O)
{
    _Vertices = 0;
    _Indices = 0;
    _VertexCount = 0;
    _IndexCount = 0;
    O.CopyMesh(*this);
}

Mesh& Mesh::operator = (const BaseMesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

Mesh& Mesh::operator = (const Mesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

Mesh::~Mesh()
{
    FreeMemory();
}

void Mesh::FreeMemory()
{
    _VertexCount = 0;
    _IndexCount = 0;
    if(_Vertices)
    {
        delete[] _Vertices;
        _Vertices = 0;
    }
    if(_Indices)
    {
        delete[] _Indices;
        _Indices = 0;
    }
}

void Mesh::Allocate(UINT NewVertexCount, UINT NewFaceCount)
{
    FreeMemory();
    if(NewVertexCount == 0 || NewFaceCount == 0)
    {
        return;
    }

    _VertexCount = NewVertexCount;
    _IndexCount = NewFaceCount * 3;
    _Vertices = new MeshVertex[_VertexCount];
    _Indices = new DWORD[_IndexCount];
}
