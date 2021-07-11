/*
FullEdge.cpp
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  FullEdge represents an edge in a ComplexMesh.
*/

HalfEdge::HalfEdge()
{
    _AcrossEdge = NULL;
    _NextEdge = NULL;
}

FullEdge::FullEdge()
{
    _Index = -1;
    for(UINT i = 0; i < 2; i++)
    {
        _Vertices[i] = NULL;
        _Triangles[i] = NULL;
    }
}

FullEdge::~FullEdge()
{

}

Vec3f FullEdge::ComputeLoopSubdivisionPos()
{
    if(Boundary())
    {
        return 0.5f * (GetVertex(0).Pos() + GetVertex(1).Pos());
    }
    else
    {
        Vertex &VOpposite0 = GetTriangle(0).GetOtherVertex(*this);
        Vertex &VOpposite1 = GetTriangle(1).GetOtherVertex(*this);

        return   (1.0f / 8.0f) * (VOpposite0.Pos() + VOpposite1.Pos())
               + (3.0f / 8.0f) * (GetVertex(0).Pos() + GetVertex(1).Pos());
    }
}

Vertex& FullEdge::GetOtherVertex(const FullEdge &FullE)
{
    if(FullE.ContainsVertex(GetVertex(0)))
    {
        return GetVertex(1);
    }
    if(FullE.ContainsVertex(GetVertex(1)))
    {
        return GetVertex(0);
    }
    SignalError("FullEdge::GetOtherVertex failed");
    return Vertex::Invalid;
}

Vertex& FullEdge::GetSharedVertex(const FullEdge &FullE)
{
    if(FullE.ContainsVertex(GetVertex(0)))
    {
        return GetVertex(0);
    }
    if(FullE.ContainsVertex(GetVertex(1)))
    {
        return GetVertex(1);
    }
    SignalError("FullEdge::GetSharedVertex failed");
    return Vertex::Invalid;
}

bool FullEdge::Boundary() const
{
    return (GetTriangle(1) == Triangle::Boundary);
}

void FullEdge::OrientMatchingBoundary()
{
    if(!_Triangles[0]->OrientedWith(*this))
    {
        Utility::Swap(_Vertices[0], _Vertices[1]);
    }
}

bool FullEdge::Oriented() const
{
    if(Boundary())
    {
        return _Triangles[0]->OrientedWith(*this);
    }
    else
    {
        bool Triangle0Oriented = _Triangles[0]->OrientedWith(*this);
        bool Triangle1Oriented = _Triangles[1]->OrientedWith(*this);
        return ((Triangle0Oriented && !Triangle1Oriented) ||
                (!Triangle0Oriented && Triangle1Oriented));
    }
}

double FullEdge::GetCotanTerm() const
{
    double Angle0 = 0.0, Angle1 = 0.0;
    if(_Triangles[0] != &(Triangle::Boundary))
    {
        Angle0 = fabs(_Triangles[0]->GetCotangent(_Triangles[0]->GetOtherVertex(*this)));
    }
    if(_Triangles[1] != &(Triangle::Boundary))
    {
        Angle1 = fabs(_Triangles[1]->GetCotangent(_Triangles[1]->GetOtherVertex(*this)));
    }
    Assert(Angle0 == Angle0 && Angle1 == Angle1, "Invalid cotangent");
    return (Angle0 + Angle1);
}

bool FullEdge::ContainsVertex(const Vertex &VCompare) const
{
    return (GetVertex(0) == VCompare || GetVertex(1) == VCompare);
}

Vertex& FullEdge::GetOtherVertex(const Vertex &VCompare)
{
    if(GetVertex(0) == VCompare)
    {
        return GetVertex(1);
    }
    if(GetVertex(1) == VCompare)
    {
        return GetVertex(0);
    }
    SignalError("FullEdge::GetOtherVertex failed");
    return Vertex::Invalid;
}

Triangle& FullEdge::GetOtherTriangle(const Triangle &TCompare)
{
    if(GetTriangle(0) == TCompare)
    {
        return GetTriangle(1);
    }
    if(GetTriangle(1) == TCompare)
    {
        return GetTriangle(0);
    }
    SignalError("FullEdge::GetOtherTriangle failed");
    return Triangle::Invalid;
}

const Triangle& FullEdge::GetOtherTriangle(const Triangle &TCompare) const
{
    if(GetTriangle(0) == TCompare)
    {
        return GetTriangle(1);
    }
    if(GetTriangle(1) == TCompare)
    {
        return GetTriangle(0);
    }
    SignalError("FullEdge::GetOtherTriangle failed");
    return Triangle::Invalid;
}
