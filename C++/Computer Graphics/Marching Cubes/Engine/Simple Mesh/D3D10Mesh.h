/*
D3D10Mesh.h
Written by Matthew Fisher

D3D10Mesh is a DirectX 10 instance of the BaseMesh class.
*/

#ifdef USE_D3D10

extern const D3D10_INPUT_ELEMENT_DESC MeshVertexD3D10Declaration[];
extern const int MeshVertexD3D10DeclarationElements;

class D3D10Mesh : public BaseMesh
{
public:
    friend class D3D10GraphicsDevice;

    //Constructors
    D3D10Mesh();
    D3D10Mesh(GraphicsDevice &_GD);
    D3D10Mesh(const BaseMesh &O);
    D3D10Mesh(const D3D10Mesh &O);
    void Allocate(UINT NewVertexCount, UINT NewFaceCount);
    //void CopyMesh(BaseMesh &Copy) const;

    //Destructors
    ~D3D10Mesh();
    void FreeMemory();

    //Accessors
    UINT IndexCount() const;
    UINT VertexCount() const;
    UINT FaceCount() const;

    MeshVertex* Vertices();
    DWORD* Indices();
    const MeshVertex* Vertices() const;
    const DWORD* Indices() const;

    //Memory
    D3D10Mesh& operator = (const BaseMesh &O);
    D3D10Mesh& operator = (const D3D10Mesh &O);
    
    //D3DMesh Accessors
    ID3DX10Mesh* GetMesh() const;
    
    //rendering functions
    void Render(UINT Subset) const;
    void Render() const;
    
    void Optimize();

private:
    void Lock() const;
    void Commit() const;
    void LoadMesh(ID3DX10Mesh* M);

    ID3DX10Mesh*        _Mesh;
    ID3DX10MeshBuffer*    _StagingVertexBuffer;
    ID3DX10MeshBuffer*    _StagingIndexBuffer;
    mutable MeshVertex* _Vertices;
    mutable DWORD*        _Indices;
};

#endif
