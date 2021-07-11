/*
Triangle.h
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  Triangle represents a triangle in a ComplexMesh.
*/

class Triangle
{
public:
    //
    // Query
    //
    Vertex&   GetOtherVertex(const FullEdge &FullE) const;
    FullEdge& GetOtherEdge(const Vertex &Vtx) const;
    void      GetOtherEdges(const FullEdge &EIn, FullEdge *EOut[2]) const;
    FullEdge& GetSharedEdge(const Triangle &Tri) const;
    FullEdge& GetSharedEdge(const Vertex &Vtx1, const Vertex &Vtx2) const;
    HalfEdge& GetHalfEdge(const FullEdge &FullE) const;
    bool      ContainsEdge(const FullEdge &FullE) const;
    bool      ContainsVertex(const Vertex &Vtx) const;
    bool      BordersTriangle(const Triangle &T) const;
    Vec3f     AveragedNormal() const;
    Vec3f     Normal() const;
    UINT      GetVertexLocalIndex(const Vertex &Vtx) const;
    float     Area() const;
    Vec3f     Center() const;
    bool      OrientedWith(const FullEdge &FullE) const;
    bool      IsBoundary() const;
    double    GetCotangent(const Vertex &Vtx) const;
    double    GetAngle(const Vertex &Vtx) const;
    Vec3f     EvaluateVField(const Vector<double> &OneForm, float v, float w) const;
    Vec3f     EvaluateVFieldGradient(const Vector<double> &OneForm, float v, float w) const;
    float     ThetaFromTangent(const Vec3f &V) const;
    Vec3f     TangentFromTheta(float Theta) const;

    //
    // Accessors
    //
    __forceinline Vertex& GetVertex(UINT VertexIndex);
    __forceinline const Vertex& GetVertex(UINT VertexIndex) const;
    __forceinline HalfEdge& GetHalfEdge(UINT EdgeIndex);
    __forceinline const HalfEdge& GetHalfEdge(UINT EdgeIndex) const;
    __forceinline FullEdge& GetFullEdge(UINT EdgeIndex);
    __forceinline const FullEdge& GetFullEdge(UINT EdgeIndex) const;
    __forceinline Triangle& GetNeighboringTriangle(UINT TriangleIndex);
    __forceinline const Triangle& GetNeighboringTriangle(UINT TriangleIndex) const;
    __forceinline UINT Index() const;
    
    static Triangle Invalid;
    static Triangle Boundary;

private:
    Vertex* _Vertices[3];
    HalfEdge* _HalfEdges[3];
    UINT _Index;

    friend class ComplexMesh;
};

__forceinline bool operator == (const Triangle &A, const Triangle &B)
{
    return ((&A) == (&B));
}

__forceinline bool operator != (const Triangle &A, const Triangle &B)
{
    return ((&A) != (&B));
}
