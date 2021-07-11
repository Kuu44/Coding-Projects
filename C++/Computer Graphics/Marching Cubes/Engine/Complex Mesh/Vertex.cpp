/*
Vertex.cpp
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.  Vertex represents a vertex in a ComplexMesh.
*/

void Vertex::LoadVertices()
{
    _Vertices.FreeMemory();
    for(UINT i = 0; i < _Triangles.Length(); i++)
    {
        for(UINT i2 = 0; i2 < 3; i2++)
        {
            Vertex &VertexToConsider = _Triangles[i]->GetVertex(i2);
            if(VertexToConsider != *this)
            {
                bool Add = true;
                for(UINT i3 = 0; i3 < _Vertices.Length(); i3++)
                {
                    if(*(_Vertices[i3]) == VertexToConsider)
                    {
                        Add = false;
                    }
                }
                if(Add)
                {
                    _Vertices.PushEnd(&VertexToConsider);
                }
            }
        }
    }
}

FullEdge& Vertex::GetSharedEdge(const Vertex &OtherVertex) const
{
    for(UINT i = 0; i < _Triangles.Length(); i++)
    {
        if(_Triangles[i]->ContainsVertex(OtherVertex))
        {
            return _Triangles[i]->GetSharedEdge(*this, OtherVertex);
        }
    }
    SignalError("GetSharedEdge failed");
    return FullEdge::Invalid;
}

double Vertex::GaussianCurvature() const
{
    double AngleSum = 0.0f;
    for(UINT TriangleIndex = 0; TriangleIndex < Triangles().Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = *(_Triangles[TriangleIndex]);
        AngleSum += CurTriangle.GetAngle(*this);
    }
    return 2.0 * Math::PI - AngleSum;
}

double Vertex::ComputeTriangleArea()
{
    double TriangleArea = 0.0f;
    for(UINT TriangleIndex = 0; TriangleIndex < Triangles().Length(); TriangleIndex++)
    {
        TriangleArea += _Triangles[TriangleIndex]->Area();
    }
    return TriangleArea;
}

Vec3f Vertex::MeanCurvatureNormal()
{
    Vec3f MeanCurvature = Vec3f::Origin;
    float ConstantTerm = 0.0f;
    for(UINT EdgeIndex = 0; EdgeIndex < Vertices().Length(); EdgeIndex++)
    {
        Vertex &OtherVertex = *(_Vertices[EdgeIndex]);
        FullEdge &CurEdge = GetSharedEdge(OtherVertex);
        float ConstantFactor = float(CurEdge.GetCotanTerm());
        Assert(ConstantFactor == ConstantFactor, "ConstantFactor invalid");
        MeanCurvature += ConstantFactor * (_Pos - OtherVertex.Pos());
        ConstantTerm += ConstantFactor;
    }
    return MeanCurvature / ConstantTerm;
}

Vec3f Vertex::AreaWeightedNormal() const
{
    Vec3f Normal = Vec3f::Origin;
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = *(_Triangles[TriangleIndex]);
        Normal += CurTriangle.Area() * CurTriangle.Normal();
    }
    return Vec3f::Normalize(Normal);
}

Vec3f Vertex::EvaluateVField(const Vector<double> &OneForm) const
{
    Vec3f Result = Vec3f::Origin;
    float Magnitude = 0.0f;
    float AreaSum = 0.0f;
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = *(_Triangles[TriangleIndex]);
        float CurArea = float(CurTriangle.Area());
        AreaSum += CurArea;

        float Ratio1 = 0.0f;
        float Ratio2 = 0.0f;
        UINT Index = CurTriangle.GetVertexLocalIndex(*this);
        if(Index == 1)
        {
            Ratio1 = 1.0f;
        }
        else if(Index == 2)
        {
            Ratio2 = 1.0f;
        }

        Vec3f VField = CurTriangle.EvaluateVField(OneForm, Ratio1, Ratio2);
        Magnitude += CurArea * VField.Length();
        Result += CurArea * Vec3f::Normalize(VField);
    }
    return Vec3f::Normalize(Result) * Magnitude / AreaSum;
}

bool Vertex::LocallyManifold()
{
    if(!_Boundary)
    {
        return true;
    }
    UINT BoundaryEdgeCount = 0;
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex *CurVertex = _Vertices[VertexIndex];
        if(GetSharedEdge(*CurVertex).Boundary())
        {
            BoundaryEdgeCount++;
            if(BoundaryEdgeCount > 2)
            {
                return false;
            }
        }
    }
    return true;
}

Vec3f Vertex::ComputeLoopSubdivisionPos()
{
    Vec3f Result;
    UINT n = _Vertices.Length();
    if(Boundary())
    {
        Result = 0.75f * _Pos;
        for(UINT i = 0; i < _Triangles.Length(); i++)
        {
            Triangle &CurTriangle = *(_Triangles[i]);
            for(UINT i2 = 0; i2 < 3; i2++)
            {
                FullEdge &CurFullEdge = CurTriangle.GetFullEdge(i2);
                if(CurFullEdge.Boundary() && CurFullEdge.ContainsVertex(*this))
                {
                    Vertex &CurVertex = CurFullEdge.GetOtherVertex(*this);
                    Result += CurVertex.Pos() / 8.0f;
                }
            }
        }
    }
    else
    {
        float Beta;
        if(n == 3)
        {
            Beta = 3.0f / 16.0f;
        }
        else
        {
            Beta = 3.0f / (8.0f * n);
        }
        Result = (1.0f - n * Beta) * _Pos;
        for(UINT i = 0; i < n; i++)
        {
            Result += _Vertices[i]->Pos() * Beta;
        }
    }
    return Result;
}

