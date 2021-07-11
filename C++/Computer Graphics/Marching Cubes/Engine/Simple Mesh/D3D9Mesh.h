/*
D3D9Mesh.h
Written by Matthew Fisher

D3D9Mesh is a D3D 9.0 instance of the BaseMesh class.
*/

#ifdef USE_D3D9

extern const DWORD D3DMeshFVF;
extern const DWORD D3DMeshOptions;

const DWORD AdjacencyBoundary = 0xffffffff;
class D3D9Mesh : public BaseMesh
{
public:
    D3D9Mesh();
    explicit D3D9Mesh(GraphicsDevice &_GD);
    explicit D3D9Mesh(const BaseMesh &o);
    explicit D3D9Mesh(const D3D9Mesh &o);
    ~D3D9Mesh();

    //
    // Memory
    //
    void Allocate(UINT NVertices, UINT NFaces);
    void CopyMesh(BaseMesh &Copy) const;
    D3D9Mesh& operator = (const BaseMesh &o);
    D3D9Mesh& operator = (const D3D9Mesh &o);
    void FreeMemory();

    //
    // Accessors
    //
    UINT IndexCount() const;
    UINT VertexCount() const;
    UINT FaceCount() const;
    MeshVertex* Vertices();
    DWORD* Indices();
    const MeshVertex* Vertices() const;
    const DWORD* Indices() const;
    LPD3DXMESH GetMesh() const;         //returns the LPD3DXMESH that is the D3D representation of a mesh
    void LoadMesh(LPD3DXMESH _mesh);    //sets this mesh equal to a given LPD3DXMESH
    LPDIRECT3DDEVICE9 GetD3DDevice();   //returns the D3DDevice this mesh was created with
    
    //
    // D3D9Mesh Unique Functions
    //
    void NPatchEnhance(float segs, bool quadratic);    //NPatchEnhance smooths a mesh by tesselating and curving it according to the NPatch algorithm
    void GenerateAdj(DWORD *& adj);                    //generates triangle adjacency information (expected by some DirectX functions)
    void GenerateAdj(Vector<DWORD> &Adjacency);
    bool QueryInside(const Vec3f &Pos, const Vec3f &Dir);
    void QueryHits(const Vec3f &Pos, const Vec3f &Dir, Vector<float> &Hits, DWORD &FirstHitFaceIndex, float &u, float &v) const;

    //
    // rendering functions
    //
    void Render() const;                //renders the whole mesh
    void Render(int Subset) const;      //renders a specific subset of the mesh
    
    //
    // Shape functions
    //
    void CreateTeapot(float radius);    //creates a DirectX teapot (which doesn't require an input file.)
    void CreateText(const char *string, char *FontName, int FontHeight,        //creates 3D text
                    float deviation, float depth, bool bold, bool italic);

    //
    // D3DX Simplification
    //
    void SimplifyToFaces(UINT Count);                    //simplifies the mesh to the given number of faces
    void SimplifyToPercentFaces(float NewPercent);        //simplifies the mesh to (Number of faces)*new_percent faces
    void SimplifyToVertices(UINT Count);                //simplifies the mesh to the given number of vertices
    void SimplifyToPercentVertices(float NewPercent);    //simplifies the mesh to (Number of vertices)*new_percent vertices

    //
    // XFiles
    //
    void LoadFromXFile(const String &Filename);            //loads this mesh from an XFile at filename
    void SaveToXFile(const String &Filename);                //saves this mesh from an XFile at filename

    //
    // Manipulation
    //
    void Clean(float Epsilon, DWORD* &AdjDataOut);
    void Optimize();

private:
    //
    // Buffer manipulation
    //
    void Lock() const;      //locks both the vertex and index buffers
    void LockVB() const;    //locks the vertex buffer
    void LockIB() const;    //locks the index buffer
    void Unlock() const;    //unlocks both buffers

    LPD3DXMESH            _Mesh;
    mutable MeshVertex    *_Vertices;
    mutable DWORD         *_Indices;
};

#endif