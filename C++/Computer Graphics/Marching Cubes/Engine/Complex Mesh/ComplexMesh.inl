/*
ComplexMesh.inl
Written by Matthew Fisher

Inline file for complex-mesh related objects.
*/

//
// Triangle inline functions
//
Vertex& Triangle::GetVertex(UINT VertexIndex)
{
    Assert(VertexIndex < 3, "Triangle::GetVertex invalid vertex index.");
    return *(_Vertices[VertexIndex]);
}

const Vertex& Triangle::GetVertex(UINT VertexIndex) const
{
    Assert(VertexIndex < 3, "Triangle::GetVertex invalid vertex index.");
    return *(_Vertices[VertexIndex]);
}

HalfEdge& Triangle::GetHalfEdge(UINT EdgeIndex)
{
    Assert(EdgeIndex < 3, "Triangle::GetHalfEdge invalid vertex index.");
    return *(_HalfEdges[EdgeIndex]);
}

const HalfEdge& Triangle::GetHalfEdge(UINT EdgeIndex) const
{
    Assert(EdgeIndex < 3, "Triangle::GetHalfEdge invalid vertex index.");
    return *(_HalfEdges[EdgeIndex]);
}

FullEdge& Triangle::GetFullEdge(UINT EdgeIndex)
{
    Assert(EdgeIndex < 3, "Triangle::GetHalfEdge invalid edge index.");
    return _HalfEdges[EdgeIndex]->AcrossEdge();
}

const FullEdge& Triangle::GetFullEdge(UINT EdgeIndex) const
{
    Assert(EdgeIndex < 3, "Triangle::GetHalfEdge invalid edge index.");
    return _HalfEdges[EdgeIndex]->AcrossEdge();
}

Triangle& Triangle::GetNeighboringTriangle(UINT TriangleIndex)
{
    Assert(TriangleIndex < 3, "Triangle::GetNeighboringTriangle invalid triangle index.");
    return _HalfEdges[TriangleIndex]->AcrossEdge().GetOtherTriangle(*this);
}

const Triangle& Triangle::GetNeighboringTriangle(UINT TriangleIndex) const
{
    Assert(TriangleIndex < 3, "Triangle::GetNeighboringTriangle invalid triangle index.");
    return _HalfEdges[TriangleIndex]->AcrossEdge().GetOtherTriangle(*this);
}

UINT Triangle::Index() const
{
    return _Index;
}
