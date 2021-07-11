/*
Triangle.cpp
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  Triangle represents a triangle in a ComplexMesh.
*/

HalfEdge& Triangle::GetHalfEdge(const FullEdge &FullE) const
{
    for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
    {
        if(GetFullEdge(EdgeIndex) == FullE)
        {
            return *(_HalfEdges[EdgeIndex]);
        }
    }
    SignalError("Triangle::GetHalfEdge edge not found.");
    return HalfEdge::Invalid;
}

Vertex& Triangle::GetOtherVertex(const FullEdge &FullE) const
{
    for(UINT VertexIndex = 0; VertexIndex < 3; VertexIndex++)
    {
        Vertex &CurVertex = *(_Vertices[VertexIndex]);
        if(CurVertex != FullE.GetVertex(0) && CurVertex != FullE.GetVertex(1))
        {
            return CurVertex;
        }
    }
    SignalError("Triangle::GetOtherVertex vertex not found.");
    return Vertex::Invalid;
}

bool Triangle::ContainsEdge(const FullEdge &FullE) const
{
    for(UINT i = 0; i < 3; i++)
    {
        if(GetFullEdge(i) == FullE)
        {
            return true;
        }
    }
    return false;
}

bool Triangle::ContainsVertex(const Vertex &Vtx) const
{
    for(UINT VertexIndex = 0; VertexIndex < 3; VertexIndex++)
    {
        if(GetVertex(VertexIndex) == Vtx)
        {
            return true;
        }
    }
    return false;
}

bool Triangle::BordersTriangle(const Triangle &T) const
{
    for(UINT TriangleIndex = 0; TriangleIndex < 3; TriangleIndex++)
    {
        if(GetNeighboringTriangle(TriangleIndex) == T)
        {
            return true;
        }
    }
    return false;
}

FullEdge& Triangle::GetOtherEdge(const Vertex &Vtx) const
{
    for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
    {
        FullEdge &CurFullEdge = _HalfEdges[EdgeIndex]->AcrossEdge();
        if(!CurFullEdge.ContainsVertex(Vtx))
        {
            return CurFullEdge;
        }
    }
    SignalError("Triangle::GetOtherEdge duplicity error.");
    return FullEdge::Invalid;
}

FullEdge& Triangle::GetSharedEdge(const Triangle &T) const
{
    for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
    {
        FullEdge &CurFullEdge = _HalfEdges[EdgeIndex]->AcrossEdge();
        if(CurFullEdge.GetOtherTriangle(*this) == T)
        {
            return CurFullEdge;
        }
    }
    SignalError("Triangle::GetSharedEdge fatal error.");
    return FullEdge::Invalid;
}

FullEdge& Triangle::GetSharedEdge(const Vertex &V1, const Vertex &V2) const
{
    for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
    {
        FullEdge &CurFullEdge = _HalfEdges[EdgeIndex]->AcrossEdge();
        if(CurFullEdge.ContainsVertex(V1) && CurFullEdge.ContainsVertex(V2))
        {
            return CurFullEdge;
        }
    }
    SignalError("Triangle::GetSharedEdge fatal error.");
    return FullEdge::Invalid;
}

float Triangle::Area() const
{
    Vec3f V1 = GetVertex(1).Pos() - GetVertex(0).Pos();
    Vec3f V2 = GetVertex(2).Pos() - GetVertex(0).Pos();
    return 0.5f * Vec3f::Cross(V1, V2).Length();
}

Vec3f Triangle::Center() const
{
    return (GetVertex(0).Pos() + GetVertex(1).Pos() + GetVertex(2).Pos()) / 3.0f;
}

bool Triangle::IsBoundary() const
{
    return (GetFullEdge(0).Boundary() || 
            GetFullEdge(1).Boundary() || 
            GetFullEdge(2).Boundary());
}

bool Triangle::OrientedWith(const FullEdge &FullE) const
{
    UINT Index0 = GetVertexLocalIndex(FullE.GetVertex(0));
    UINT Index1 = GetVertexLocalIndex(FullE.GetVertex(1));
    return (Index1 == (Index0 + 1) % 3);
}

Vec3f Triangle::Normal() const
{
    Vec3f V1 = _Vertices[1]->Pos() - _Vertices[0]->Pos();
    Vec3f V2 = _Vertices[2]->Pos() - _Vertices[0]->Pos();
    return Vec3f::Normalize(Vec3f::Cross(V1, V2));
}

UINT Triangle::GetVertexLocalIndex(const Vertex &VCompare) const
{
    for(UINT i = 0; i < 3; i++)
    {
        if(GetVertex(i) == VCompare)
        {
            return i;
        }
    }
    SignalError("Triangle::GetVertexIndex Fatal Error.");
    return UINT(-1);
}

double Triangle::GetAngle(const Vertex &Vtx) const
{
    UINT BaseIndex = GetVertexLocalIndex(Vtx);
    Vec3f E1 = _Vertices[(BaseIndex + 1) % 3]->Pos() - Vtx.Pos();
    Vec3f E2 = _Vertices[(BaseIndex + 2) % 3]->Pos() - Vtx.Pos();
    return Vec3f::AngleBetween(E1, E2);
}

double Triangle::GetCotangent(const Vertex &Vtx) const
{
    UINT BaseIndex = GetVertexLocalIndex(Vtx);
    Vec3f E1 = _Vertices[(BaseIndex + 1) % 3]->Pos() - Vtx.Pos();
    Vec3f E2 = _Vertices[(BaseIndex + 2) % 3]->Pos() - Vtx.Pos();
    double Denominator = Vec3f::Dot(Vec3f::Cross(E1, E2), Normal());
    //Assert(Denominator != 0.0f && Denominator == Denominator, "invalid denominator");
    if(Denominator == 0.0f)
    {
        return 0.0f;
    }
    else
    {
        return Vec3f::Dot(E1, E2) / Denominator;
    }
}

float Triangle::ThetaFromTangent(const Vec3f &V) const
{
    Vec3f MyNormal = Normal(), Tangent1, Tangent2;
    Vec3f::CompleteOrthonormalBasis(MyNormal, Tangent1, Tangent2);
    float Theta = Vec3f::AngleBetween(V, Tangent1);
    if(Vec3f::Dot(Vec3f::Cross(Tangent1, V), MyNormal) > 0.0f)
    {
        return Theta;
    }
    else
    {
        return -Theta;
    }
}

Vec3f Triangle::TangentFromTheta(float Theta) const
{
    Vec3f MyNormal = Normal(), Tangent1, Tangent2;
    Vec3f::CompleteOrthonormalBasis(MyNormal, Tangent1, Tangent2);
    Matrix4 Rotation = Matrix4::Rotation(MyNormal, Theta);
    return Rotation.TransformNormal(Tangent1);
}

Vec3f Triangle::EvaluateVFieldGradient(const Vector<double> &OneForm, float v, float w) const
{
    Matrix4 Transform = Matrix4::Face(Normal(), Vec3f::eZ) * Matrix4::Translation(-Center());
    Vec3f V[3];
    for(UINT VertexIndex = 0; VertexIndex < 3; VertexIndex++)
    {
        V[VertexIndex] = Transform.TransformPoint(_Vertices[VertexIndex]->Pos());
    }

    float a = float(OneForm[_HalfEdges[0]->AcrossEdge().Index()]);
    float b = float(OneForm[_HalfEdges[1]->AcrossEdge().Index()]);
    float c = float(OneForm[_HalfEdges[2]->AcrossEdge().Index()]);
    if(!OrientedWith(_HalfEdges[0]->AcrossEdge()))
    {
        a = -a;
    }
    if(!OrientedWith(_HalfEdges[1]->AcrossEdge()))
    {
        b = -b;
    }
    if(!OrientedWith(_HalfEdges[2]->AcrossEdge()))
    {
        c = -c;
    }

    float NumX = V[0].y * a + V[1].y * b + V[2].y * c;
    float DenomX = (V[1].x*V[0].y - V[2].x*V[0].y - V[0].x*V[1].y + V[2].x*V[1].y + V[0].x*V[2].y - V[1].x*V[2].y);

    float NumY = V[0].x * a + V[1].x * b + V[2].x * c;
    float DenomY = (V[2].x*(V[0].y - V[1].y) + V[0].x*(V[1].y - V[2].y) + V[1].x*(-V[0].y + V[2].y));

    Vec3f Gradient = Vec3f::Origin;
    if(DenomX != 0.0f)
    {
        Gradient.x = NumX / DenomX;
    }
    if(DenomY != 0.0f)
    {
        Gradient.y = NumY / DenomY;
    }
    return Transform.Inverse().TransformNormal(Gradient);
}

Vec3f Triangle::EvaluateVField(const Vector<double> &OneForm, float v, float w) const
{
    Matrix4 Rotation = Matrix4::Rotation(Normal(), Math::PIf / 2.0f);
    Vec3f ab = _Vertices[1]->Pos() - _Vertices[0]->Pos();
    Vec3f ac = _Vertices[2]->Pos() - _Vertices[0]->Pos();

    ab = Rotation.TransformNormal(ab);
    ac = Rotation.TransformNormal(ac);
    
    float a = float(OneForm[_HalfEdges[0]->AcrossEdge().Index()]);
    float b = float(OneForm[_HalfEdges[1]->AcrossEdge().Index()]);
    float c = float(OneForm[_HalfEdges[2]->AcrossEdge().Index()]);
    if(!OrientedWith(_HalfEdges[0]->AcrossEdge()))
    {
        a = -a;
    }
    if(!OrientedWith(_HalfEdges[1]->AcrossEdge()))
    {
        b = -b;
    }
    if(!OrientedWith(_HalfEdges[2]->AcrossEdge()))
    {
        c = -c;
    }

    float abc = a + b + c;

    return ((v * abc - b) * ab + (w * abc - c) * ac) / (2.0f * Area());
}

/*float Triangle::GetAngle(Vertex *VBase)
{
    int VBaseIndex, VEdgeIndex[2];
    if(V[0] == VBase) VBaseIndex = 0;
    if(V[1] == VBase) VBaseIndex = 1;
    if(V[2] == VBase) VBaseIndex = 2;
    Vec3f Edge1, Edge2;
    Triplet(VBaseIndex, VEdgeIndex);

    float a = E[VEdgeIndex[0]]
    //Edge1 = V[VEdgeIndex[0]]->Pos - V[VBaseIndex]->Pos; Edge1.Normalize();
    //Edge2 = V[VEdgeIndex[1]]->Pos - V[VBaseIndex]->Pos; Edge2.Normalize();
    return acosf(Vec3f::Dot(Edge1,Edge2));
}*/
