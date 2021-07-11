/*
BaseMeshMemory.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshMemory.cpp contains functions surrounding memory management and AppendVertices
*/

BaseMesh::BaseMesh()
{
    _GD = NULL;
}

UINT BaseMesh::Hash32() const
{
    return Utility::Hash32((const BYTE *)Vertices(), VertexCount() * sizeof(MeshVertex)) +
           Utility::Hash32((const BYTE *)Indices(), IndexCount() * sizeof(DWORD));
}

UINT64 BaseMesh::Hash64() const
{
    return Utility::Hash64((const BYTE *)Vertices(), VertexCount() * sizeof(MeshVertex)) +
           Utility::Hash64((const BYTE *)Indices(), IndexCount() * sizeof(DWORD));
}

GraphicsDevice& BaseMesh::GetGD() const
{
    PersistentAssert(_GD != NULL, "Graphics device requested from a mesh that was not associated");
    return *_GD;
}

void BaseMesh::SetGD(GraphicsDevice &GD)
{
    _GD = &GD;
}

void BaseMesh::CopyMesh(BaseMesh &Copy) const
{
    Copy._GD = _GD;
    Copy.Allocate(VertexCount(), FaceCount());
    memcpy(Copy.Vertices(), Vertices(), sizeof(MeshVertex) * VertexCount());
    memcpy(Copy.Indices(), Indices(), sizeof(DWORD) * IndexCount());
}

BaseMesh& BaseMesh::operator = (const BaseMesh &O)
{
    O.CopyMesh(*this);
    return *this;
}

void BaseMesh::operator += (const BaseMesh &O)
{
    AppendVertices(O);
}

void BaseMesh::AppendVertices(const BaseMesh &O)
{
    int vc = VertexCount(), ic = IndexCount();
    MeshVertex *V = Vertices(), *OldV = new MeshVertex[vc];
    DWORD *I = Indices(), *OldI = new DWORD[ic];

    memcpy(OldV, V, vc * sizeof(MeshVertex));
    memcpy(OldI, I, ic * sizeof(DWORD));            //store all the old vertices/indices

    Allocate(vc + O.VertexCount(), ic/3 + O.FaceCount());    //allocate space for the current vertices/indices and o's vertices/indices

    V = Vertices();
    I = Indices();

    memcpy(V, OldV, vc * sizeof(MeshVertex));
    memcpy(I, OldI, ic * sizeof(DWORD));        //copy the old vertices/indices back into the mesh,

    memcpy(&(V[vc]), O.Vertices(), O.VertexCount() * sizeof(MeshVertex));    //copy the new vertices after the current ones,

    UINT oic = O.IndexCount();
    const DWORD *oI = O.Indices();
    for(UINT i = 0; i < oic; i++)
    {
        I[ic+i] = oI[i] + vc;    //copy o's indices as well, except increasing the index by vc (since o's vertices start at vc, not 0)
    }

    delete[] OldV;
    delete[] OldI;
}

void BaseMesh::LoadMeshList(const Vector<BaseMesh*> &Meshes)
{
    UINT NewVertexCount = 0, NewFaceCount = 0;
    for(UINT MeshIndex = 0; MeshIndex < Meshes.Length(); MeshIndex++)
    {
        const BaseMesh &CurMesh = *(Meshes[MeshIndex]);
        NewVertexCount += CurMesh.VertexCount();
        NewFaceCount += CurMesh.FaceCount();
    }
    Allocate(NewVertexCount, NewFaceCount);
    UINT VertexBaseIndex = 0, IndexBaseIndex = 0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    for(UINT MeshIndex = 0; MeshIndex < Meshes.Length(); MeshIndex++)
    {
        const BaseMesh &CurMesh = *(Meshes[MeshIndex]);
        
        const MeshVertex *CurV = CurMesh.Vertices();
        const UINT CurVertexCount = CurMesh.VertexCount();
        const DWORD *CurI = CurMesh.Indices();
        const UINT CurFaceCount = CurMesh.FaceCount();

        for(UINT VertexIndex = 0; VertexIndex < CurVertexCount; VertexIndex++)
        {
            V[VertexBaseIndex + VertexIndex] = CurV[VertexIndex];
        }
        
        for(UINT FaceIndex = 0; FaceIndex < CurFaceCount; FaceIndex++)
        {
            for(UINT LocalVertexIndex = 0; LocalVertexIndex < 3; LocalVertexIndex++)
            {
                I[IndexBaseIndex + FaceIndex * 3 + LocalVertexIndex] = CurI[FaceIndex * 3 + LocalVertexIndex] + VertexBaseIndex;
            }
        }
        VertexBaseIndex += CurMesh.VertexCount();
        IndexBaseIndex += CurMesh.FaceCount() * 3;
    }
}

void BaseMesh::LoadMeshList(const Vector< pair<const BaseMesh *, Matrix4> > &Meshes)
{
    UINT NewVertexCount = 0, NewFaceCount = 0;
    for(UINT MeshIndex = 0; MeshIndex < Meshes.Length(); MeshIndex++)
    {
        const BaseMesh &CurMesh = *(Meshes[MeshIndex].first);
        NewVertexCount += CurMesh.VertexCount();
        NewFaceCount += CurMesh.FaceCount();
    }
    Allocate(NewVertexCount, NewFaceCount);
    UINT VertexBaseIndex = 0, IndexBaseIndex = 0;
    for(UINT MeshIndex = 0; MeshIndex < Meshes.Length(); MeshIndex++)
    {
        const BaseMesh &CurMesh = *(Meshes[MeshIndex].first);
        Matrix4 Transform = Meshes[MeshIndex].second;
        for(UINT VertexIndex = 0; VertexIndex < CurMesh.VertexCount(); VertexIndex++)
        {
            Vertices()[VertexBaseIndex + VertexIndex] = CurMesh.Vertices()[VertexIndex];
            Vertices()[VertexBaseIndex + VertexIndex].Pos = Transform.TransformPoint(Vertices()[VertexBaseIndex + VertexIndex].Pos);
        }
        for(UINT FaceIndex = 0; FaceIndex < CurMesh.FaceCount(); FaceIndex++)
        {
            for(UINT LocalVertexIndex = 0; LocalVertexIndex < 3; LocalVertexIndex++)
            {
                Indices()[IndexBaseIndex + FaceIndex * 3 + LocalVertexIndex] = CurMesh.Indices()[FaceIndex * 3 + LocalVertexIndex] + VertexBaseIndex;
            }
        }
        VertexBaseIndex += CurMesh.VertexCount();
        IndexBaseIndex += CurMesh.FaceCount() * 3;
    }
}
