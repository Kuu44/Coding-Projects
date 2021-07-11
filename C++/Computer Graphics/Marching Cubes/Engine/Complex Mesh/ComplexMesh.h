/*
ComplexMesh.h
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.
*/

#include "ComplexMesh.inl"

typedef Vector<UINT> ComplexMeshEdgeHash;    // An element in the hash structure for linking half-edges together
class ComplexMesh
{
public:
    ComplexMesh();
    ComplexMesh(const ComplexMesh &M);
    ~ComplexMesh();

    //
    // Memory
    //
    void FreeMemory();
    ComplexMesh& operator = (const ComplexMesh &M);
    void Dump(BaseMesh &Mesh) const;    //dumps all mesh data into a simple mesh class
    void Load(const BaseMesh &Mesh);    //loads all mesh data from a simple mesh class

    //
    // File Functions
    //
    void VerboseSave(const String &Filename);

    //
    // Manipulation
    //
    void Subdivision(BaseMesh &Mesh);   //loads mesh as one iteration of Loop subdivision on this mesh
    void Subdivision();                 //loads this mesh as one iteration of Loop subdivision on this mesh
    void ImplicitMeanCurvatureFlow(float TimeStep);
    void ExplicitMeanCurvatureFlow(float TimeStep);
    bool ComputeDiskParameterization(bool Natural);
    void ComputeConstrainedParameterization();

    //
    // Query
    //
    bool Oriented();
    void ValidateTopology();
    float AverageEdgeLength() const;
    float AverageTriangleArea() const;
    bool ShootRay(const D3D9Mesh &M, const Vec3f &Pos, const Vec3f &Dir, UINT &TriangleIndex, UINT &VertexIndex, UINT &EdgeIndex, Vec3f &WorldPos) const;
    bool ComputeDiskBoundary(Vector<FullEdge *> &Boundary);

    //
    // Accessors
    //
    __forceinline Vector<Vertex>& Vertices()
    {
        return _Vertices;
    }
    __forceinline Vector<Triangle>& Triangles()
    {
        return _Triangles;
    }
    __forceinline Vector<FullEdge*>& FullEdges()
    {
        return _FullEdges;
    }
    __forceinline Vector<HalfEdge>& HalfEdges()
    {
        return _HalfEdges;
    }
    __forceinline const Vector<Vertex>& Vertices() const
    {
        return _Vertices;
    }
    __forceinline const Vector<Triangle>& Triangles() const
    {
        return _Triangles;
    }
    __forceinline const Vector<FullEdge*>& FullEdges() const
    {
        return _FullEdges;
    }
    __forceinline const Vector<HalfEdge>& HalfEdges() const
    {
        return _HalfEdges;
    }

private:
    void PrepareTopology();  //accumulates topology in object lists
    void Orient();

    //
    // Hash Table Functions
    //
    void InitHashTable(UINT Size);
    void ClearHashTable();
    void HashEdge(const FullEdge &FullE);
    FullEdge& FindFullEdge(Vertex *SearchV[2]);

    Vector<ComplexMeshEdgeHash> _HashTable;
    Vector<Vertex> _Vertices;
    Vector<Triangle> _Triangles;
    Vector<FullEdge*> _FullEdges;
    Vector<HalfEdge> _HalfEdges;
};

void Subdivide(BaseMesh &M1, BaseMesh &M2);
void Subdivide(BaseMesh &M1, BaseMesh &M2, UINT Iterations);
