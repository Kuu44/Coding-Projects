/*
FullEdge.h
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  FullEdge represents an edge in a ComplexMesh.
HalfEdge represents one side of an edge (an edge associated with a specific triangle.)
*/

class FullEdge
{
public:
    FullEdge();
    ~FullEdge();

    //
    // Query
    //
    Vertex& GetOtherVertex(const Vertex &Vtx);            //assuming V points to one vertex on this edge, return the other vertex
    Vertex& GetOtherVertex(const FullEdge &FullE);        //assuming E shares one vertex with this edge, return the vertex E does not share.
    Vertex& GetSharedVertex(const FullEdge &FullE);        //assuming E shares one vertex with this edge, return the vertex E does share.
    Triangle& GetOtherTriangle(const Triangle &Tri);    //assuming T is adjacent to this edge, return the other triangle
    const Triangle& GetOtherTriangle(const Triangle &Tri) const;
    bool ContainsVertex(const Vertex &Vtx) const;        //true if this edge contains V, false otherwise
    bool Boundary() const;                                //true if a boundary edge
    bool Oriented() const;
    void OrientMatchingBoundary();
    double GetCotanTerm() const;
    Vec3f ComputeLoopSubdivisionPos();

    //
    // Accessors
    //
    __forceinline HalfEdge& GetHalfEdge(UINT EdgeIndex)
    {
        Assert(EdgeIndex <= 1, "Invalid index on FullEdge::GetHalfEdge");
        return _Triangles[EdgeIndex]->GetHalfEdge(*this);
    }
    __forceinline const HalfEdge& GetHalfEdge(UINT EdgeIndex) const
    {
        Assert(EdgeIndex <= 1, "Invalid index on FullEdge::GetHalfEdge");
        return _Triangles[EdgeIndex]->GetHalfEdge(*this);
    }
    __forceinline Vertex& GetVertex(UINT VertexIndex)
    {
        Assert(VertexIndex <= 1, "Invalid index on FullEdge::GetVertex");
        return *(_Vertices[VertexIndex]);
    }
    __forceinline const Vertex& GetVertex(UINT VertexIndex) const
    {
        Assert(VertexIndex <= 1, "Invalid index on FullEdge::GetVertex");
        return *(_Vertices[VertexIndex]);
    }
    __forceinline Triangle& GetTriangle(UINT TriangleIndex)
    {
        Assert(TriangleIndex <= 1, "Invalid index on FullEdge::GetTriangle");
        return *(_Triangles[TriangleIndex]);
    }
    __forceinline const Triangle& GetTriangle(UINT TriangleIndex) const
    {
        Assert(TriangleIndex <= 1, "Invalid index on FullEdge::GetTriangle");
        return *(_Triangles[TriangleIndex]);
    }
    __forceinline UINT Index() const
    {
        return _Index;
    }
    __forceinline Vec3f Vector() const
    {
        return (_Vertices[1]->Pos() - _Vertices[0]->Pos());
    }
    __forceinline Vec3f Center() const
    {
        return (_Vertices[0]->Pos() + _Vertices[1]->Pos()) * 0.5f;
    }
    
    static FullEdge Invalid;
    static FullEdge NotFound;

private:
    Vertex *_Vertices[2];
    Triangle *_Triangles[2];
    UINT _Index;

    friend class ComplexMesh;
};

class HalfEdge
{
public:
    HalfEdge();

    __forceinline FullEdge& AcrossEdge()
    {
        return *_AcrossEdge;
    }
    __forceinline const FullEdge& AcrossEdge() const
    {
        return *_AcrossEdge;
    }

    __forceinline HalfEdge& NextEdge()
    {
        return *_NextEdge;
    }
    __forceinline const HalfEdge& NextEdge() const
    {
        return *_NextEdge;
    }

    static HalfEdge Invalid;

private:
    FullEdge *_AcrossEdge;    //pointer to the full edge structure this HalfEdge is associated with
    HalfEdge *_NextEdge;      //pointer to the next half edge

    friend class ComplexMesh;
};

__forceinline bool operator == (const HalfEdge &A, const HalfEdge &B)
{
    return ((&A) == (&B));
}

__forceinline bool operator != (const HalfEdge &A, const HalfEdge &B)
{
    return ((&A) != (&B));
}

__forceinline bool operator == (const FullEdge &A, const FullEdge &B)
{
    return ((&A) == (&B));
}

__forceinline bool operator != (const FullEdge &A, const FullEdge &B)
{
    return ((&A) != (&B));
}