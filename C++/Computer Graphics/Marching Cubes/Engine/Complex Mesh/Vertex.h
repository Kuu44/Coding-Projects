/*
Vertex.h
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  Vertex represents a vertex in a ComplexMesh.
*/

typedef Vector<Triangle*> TriangleList;
typedef Vector<Vertex*> VertexList;

class Vertex
{
public:
    //
    // Connectivity
    //
    void LoadVertices();
    FullEdge& GetSharedEdge(const Vertex &OtherVertex) const;

    //
    // Query
    //
    double ComputeTriangleArea();
    double GaussianCurvature() const;
    Vec3f MeanCurvatureNormal();
    Vec3f AreaWeightedNormal() const;
    Vec3f EvaluateVField(const Vector<double> &OneForm) const;
    Vec3f ComputeLoopSubdivisionPos();

    //
    // Topology check
    //
    bool LocallyManifold();

    //
    // Accessors
    //
    __forceinline Vec3f& Pos()
    {
        return _Pos;
    }
    __forceinline const Vec3f& Pos() const
    {
        return _Pos;
    }
    __forceinline Vec2f& TexCoords()
    {
        return _TexCoords;
    }
    __forceinline const Vec2f& TexCoords() const
    {
        return _TexCoords;
    }
    __forceinline TriangleList& Triangles()
    {
        return _Triangles;
    }
    __forceinline const TriangleList& Triangles() const
    {
        return _Triangles;
    }
    __forceinline VertexList& Vertices()
    {
        return _Vertices;
    }
    __forceinline const VertexList& Vertices() const
    {
        return _Vertices;
    }
    __forceinline bool Boundary() const
    {
        return _Boundary;
    }
    __forceinline bool& Boundary()
    {
        return _Boundary;
    }
    __forceinline UINT Index() const
    {
        return _Index;
    }

    static Vertex Invalid;

private:
    Vec3f _Pos;                   //Position in R3
    Vec2f _TexCoords;             //texture coordinates
    TriangleList _Triangles;      //Pointer to every triangle in the mesh that is incident on this Vertex.
    VertexList _Vertices;         //Pointer to every vertex in the mesh that in the one ring neighboorhood of this Vertex
    UINT _Index;                  //Index in the mesh's vertex array
    bool _Boundary;               //true if an edge incident on this vertex is a boundary edge

    friend class ComplexMesh;
};

__forceinline bool operator == (const Vertex &A, const Vertex &B)
{
    return ((&A) == (&B));
}

__forceinline bool operator != (const Vertex &A, const Vertex &B)
{
    return ((&A) != (&B));
}
