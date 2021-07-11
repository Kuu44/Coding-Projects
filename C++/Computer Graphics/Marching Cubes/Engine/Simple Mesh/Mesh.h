/*
Mesh.h
Written by Matthew Fisher

Mesh is a standard C++ array instance of the BaseMesh class.  It's the only kind that can be used by OpenGL,
but it will run fine under DirectX as well (if not as quickly as a D3DMesh.)  Mesh gets all of its
functionality from BaseMesh and has no features not defined by BaseMesh.
*/

class Mesh : public BaseMesh {
public:
    Mesh();
    Mesh(GraphicsDevice &_GD);
    Mesh(BaseMesh &o);
    Mesh(const Mesh &o);
    ~Mesh();

    //
    // Memory
    //
    void Allocate(UINT NewVertexCount, UINT NewFaceCount);
    void FreeMemory();
    Mesh& operator = (const BaseMesh &o);
    Mesh& operator = (const Mesh &o);

    //
    // Accessors
    //
    __forceinline UINT IndexCount() const            { return _IndexCount; }
    __forceinline UINT VertexCount() const           { return _VertexCount; }
    __forceinline UINT FaceCount() const             { return _IndexCount / 3; }
    __forceinline MeshVertex* Vertices()             { return _Vertices; }
    __forceinline DWORD* Indices()                   { return _Indices; }
    __forceinline const MeshVertex* Vertices() const { return _Vertices; }
    __forceinline const DWORD* Indices() const       { return _Indices; }


    //
    // Rendering functions
    //
    void Render() const;

private:
    UINT _VertexCount, _IndexCount;
    MeshVertex*   _Vertices;
    DWORD*        _Indices;
};