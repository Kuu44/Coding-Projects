/*
BaseMeshBounding.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshBounding.cpp contains functions about bounding and determining the size of the mesh.
*/

Rectangle3f BaseMesh::BoundingBox() const
{
    UINT VC = VertexCount();
    const MeshVertex *V = Vertices();

    if(VC == 0)
    {
        return Rectangle3f(Vec3f::Origin, Vec3f::Origin);
    }

    Vec3f Min = V[0].Pos, Max = V[0].Pos;
    for(UINT i = 1; i < VC; i++)
    {
        Min = Vec3f::Minimize(Min, V[i].Pos);
        Max = Vec3f::Maximize(Max, V[i].Pos);
    }
    return Rectangle3f(Min, Max);
}

Rectangle3f BaseMesh::BoundingBox(const Matrix4 &transform) const
{
    UINT vertexCount = VertexCount();
    const MeshVertex *vertices = Vertices();

    if(vertexCount == 0)
    {
        return Rectangle3f(Vec3f::Origin, Vec3f::Origin);
    }

    Vec3f pos0 = transform.TransformPoint(vertices[0].Pos);
    Vec3f Min = pos0, Max = pos0;
    for(UINT i = 1; i < vertexCount; i++)
    {
        Vec3f pos = transform.TransformPoint(vertices[i].Pos);
        Min = Vec3f::Minimize(Min, pos);
        Max = Vec3f::Maximize(Max, pos);
    }
    return Rectangle3f(Min, Max);
}

float BaseMesh::SurfaceArea() const
{
    UINT TriangleCount = FaceCount();
    const DWORD *MyIndices = Indices();
    const MeshVertex *MyVertices = Vertices();
    float Result = 0.0f;
    for(UINT TriangleIndex = 0; TriangleIndex < TriangleCount; TriangleIndex++)
    {
        Vec3f V[3];
        for(UINT LocalVertexIndex = 0; LocalVertexIndex < 3; LocalVertexIndex++)
        {
            V[LocalVertexIndex] = MyVertices[MyIndices[TriangleIndex * 3 + LocalVertexIndex]].Pos;
        }
        Result += Math::TriangleArea(V[0], V[1], V[2]);
    }
    return Result;
}

float BaseMesh::Radius()
{
    UINT VC = VertexCount();
    MeshVertex *V = Vertices();

    if(VC == 0)
    {
        return 0.0f;
    }

    float LargestDistance = V[0].Pos.Length();
    for(UINT i = 1; i < VC; i++)
    {
        float Result = V[i].Pos.Length();
        LargestDistance = Math::Max(Result, LargestDistance);
    }
    return LargestDistance;
}

float BaseMesh::Radius(const Vec3f &Center)
{
    UINT VC = VertexCount();
    MeshVertex *V = Vertices();

    if(VC == 0)
    {
        return 0.0f;
    }

    float LargestDistance = (V[0].Pos - Center).Length();
    for(UINT i = 1; i < VC; i++)
    {
        float Result = (V[i].Pos - Center).Length();
        LargestDistance = Math::Max(Result, LargestDistance);
    }
    return LargestDistance;
}

Matrix4 BaseMesh::UnitSphereTransform()
{
    Vec3f Center = BoundingBox().Center();
    float Scale = 1.0f / Radius(Center);
    return Matrix4::Translation(-Center) * Matrix4::Scaling(Scale);
}