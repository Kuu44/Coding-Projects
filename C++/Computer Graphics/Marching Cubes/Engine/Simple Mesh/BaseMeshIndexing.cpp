/*
BaseMeshIndexing.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshIndexing.cpp contains the WeldVertices, UnIndex, and TwoPatch functions.
*/

//MeshTwoPatchEdge stores the index of the two vertices that define an edge
struct MeshTwoPatchEdge {
    DWORD v1, v2;
};

//SearchTwoPatchEdge is a local function that searches List for a vertex that matches v2.
bool SearchTwoPatchEdge(Vector<MeshTwoPatchEdge> &List, DWORD &v1, DWORD v2)
{
    for(UINT i = 0; i < List.Length(); i++)
    {
        if(List[i].v2 == v2)        //if we have a match
        {
            v1 = List[i].v1;
            return true;            //return the match
        }
    }
    return false;
}

void BaseMesh::TwoPatch()
{
    Vector<MeshVertex> NewVertices;    //list of new vertices in the mesh
    Vector<TriMeshFace> NewFaces;      //list of new faces in the mesh

    UINT vc = VertexCount(), ic = IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    Vector<MeshTwoPatchEdge>* HashVertices = new Vector<MeshTwoPatchEdge>[vc];
    //HashVertices is a hash table that stores all edges incident on an edge.
    //a given edge's location in the hash table is HashVertices[Q], where Q is the index
    //of the smallest of the edge's two indices.
    
    DWORD LocalTIndices[6];     //we take each face and add 3 new vertices in the middle of each edge.
                                //LocalTIndices represents these 6 vertices (the 3 new ones and the 3 origional ones.)
                                //these 6 vertices then become 4 triangles that exactly match the origional triangle.

    DWORD VertexIndex;           //the index of the vertex we're looking for
    MeshVertex NewVertex;        //the new vertex we're going to add to the mesh
    TriMeshFace NewTriangle;     //the new triangle we're going to add to the mesh
    MeshTwoPatchEdge NewEdge;    //the edge we're going to add to the hash table

    for(UINT i = 0; i < vc; i++)
    {
        NewVertices.PushEnd(V[i]);    //all old vertices will be in the new mesh
    }

    for(UINT i = 0; i < ic; i+=3)
    {
        LocalTIndices[0] = I[i+0];
        LocalTIndices[1] = I[i+1];
        LocalTIndices[2] = I[i+2];    //the origional 3 triangles are always in LocalTIndices

        //now it remains to get the vertices at the middle of each edge
        //if these aren't already in the mesh we just add a new vertex to the final mesh, otherwise we need to use our hash table to find
        //their position in the mesh and use those indices.

        for(UINT i2=0;i2<3;i2++)
        {
            int EdgeVtx1, EdgeVtx2;    //the indices we're looking for
            if(i2 == 0)
            {
                EdgeVtx1 = I[i+0];
                EdgeVtx2 = I[i+1];
            }
            if(i2 == 1)
            {
                EdgeVtx1 = I[i+1];
                EdgeVtx2 = I[i+2];
            }
            if(i2 == 2)
            {
                EdgeVtx1 = I[i+0];
                EdgeVtx2 = I[i+2];
            }
            if(EdgeVtx2 < EdgeVtx1) Utility::Swap(EdgeVtx1, EdgeVtx2);    //we want EdgeVtx1 to be the smallest
            if(SearchTwoPatchEdge(HashVertices[EdgeVtx1], VertexIndex, EdgeVtx2))    //search for the corresponding edge to see if it's already in the mesh
            {
                LocalTIndices[3+i2] = VertexIndex;    //if it is we just choose the found index as our entry in LocalTIndices.  No need to add another vertex to the mesh; it's already there
            } else 
            {
                Interpolate(V[EdgeVtx1],V[EdgeVtx2],NewVertex,0.5f);    //otherwise make a new vertex at the middle of the edge,
                NewEdge.v2 = EdgeVtx2;
                NewEdge.v1 = NewVertices.Length();
                LocalTIndices[3+i2] = NewVertices.Length();        //this new vertex is our LocalTIndices entry
                HashVertices[EdgeVtx1].PushEnd(NewEdge);           //we need to add it to the hash table...
                NewVertices.PushEnd(NewVertex);                       //and add it to the new mesh
            }
        }

        //Now we have all 6 of our LocalTIndices.  This was one triangle in the origional mesh and is now 4 triangles in the new mesh.
        //we add those 4 new triangles now.

        NewTriangle.I[0] = LocalTIndices[0];
        NewTriangle.I[1] = LocalTIndices[3];
        NewTriangle.I[2] = LocalTIndices[5];
        NewFaces.PushEnd(NewTriangle);

        NewTriangle.I[0] = LocalTIndices[3];
        NewTriangle.I[1] = LocalTIndices[1];
        NewTriangle.I[2] = LocalTIndices[4];
        NewFaces.PushEnd(NewTriangle);

        NewTriangle.I[0] = LocalTIndices[5];
        NewTriangle.I[1] = LocalTIndices[4];
        NewTriangle.I[2] = LocalTIndices[2];
        NewFaces.PushEnd(NewTriangle);

        NewTriangle.I[0] = LocalTIndices[5];
        NewTriangle.I[1] = LocalTIndices[3];
        NewTriangle.I[2] = LocalTIndices[4];
        NewFaces.PushEnd(NewTriangle);
    }

    for(UINT i = 0; i <vc; i++)
    {
        HashVertices[i].FreeMemory();
    }

    delete[] HashVertices;                //free the hash table up

    Allocate(NewVertices.Length(), NewFaces.Length());    //allocate space for the new mesh (deleting the old mesh)

    MeshVertex *VNew = Vertices();
    DWORD *INew = Indices();
    vc = VertexCount();
    ic = IndexCount();

    for(UINT i = 0; i < vc; i++)
    {
        VNew[i] = NewVertices[i];
    }

    for(UINT i = 0; i < ic / 3; i++)
    {
        INew[i * 3 + 0] = NewFaces[i].I[0];
        INew[i * 3 + 1] = NewFaces[i].I[1];
        INew[i * 3 + 2] = NewFaces[i].I[2];
    }
}

void BaseMesh::CleanVerticesAndTriangles()
{
    Vector<UINT> OldToNewMapping;
    CleanVerticesAndTriangles(OldToNewMapping);
}

void BaseMesh::CleanVerticesAndTriangles(Vector<UINT> &OldToNewMapping)
{
    UINT NumFaces = FaceCount(), NumVertices = VertexCount();
    DWORD *I = Indices();
    MeshVertex *V = Vertices();

    Vector<DWORD> NewIndices;
    Vector<MeshVertex> NewVertices;
    OldToNewMapping.ReSize(NumVertices);
    OldToNewMapping.Clear(NumVertices);
    
    for(UINT FaceIndex = 0; FaceIndex < NumFaces; FaceIndex++)
    {
        if(I[FaceIndex * 3 + 0] != I[FaceIndex * 3 + 1] &&
           I[FaceIndex * 3 + 1] != I[FaceIndex * 3 + 2] &&
           I[FaceIndex * 3 + 2] != I[FaceIndex * 3 + 0])
        {
            for(UINT i = 0; i < 3; i++)
            {
                UINT SourceIndex = I[FaceIndex * 3 + i];
                if(OldToNewMapping[SourceIndex] == NumVertices)
                {
                    OldToNewMapping[SourceIndex] = NewVertices.Length();
                    NewVertices.PushEnd(V[SourceIndex]);
                }
                NewIndices.PushEnd(OldToNewMapping[SourceIndex]);
            }
        }
    }
    Allocate(NewVertices.Length(), NewIndices.Length() / 3);
    NumFaces = FaceCount();
    NumVertices = VertexCount();
    I = Indices();
    V = Vertices();
    for(UINT VertexIndex = 0; VertexIndex < NumVertices; VertexIndex++)
    {
        V[VertexIndex] = NewVertices[VertexIndex];
    }
    for(UINT FaceIndex = 0; FaceIndex < NumFaces; FaceIndex++)
    {
        for(UINT i = 0; i < 3; i++)
        {
            I[FaceIndex * 3 + i] = NewIndices[FaceIndex * 3 + i];
        }
    }
}

void BaseMesh::UnIndex()
{
    int i,vc=VertexCount(),ic=IndexCount();
    MeshVertex *V = Vertices(),*OldV = new MeshVertex[vc];
    DWORD *I = Indices(),*OldI = new DWORD[ic];                //create space for all the old vertices and indices

    memcpy(OldV, V, vc * sizeof(MeshVertex));
    memcpy(OldI, I, ic * sizeof(DWORD));        //copy all the old verticse and indices for storage

    Allocate(ic, ic/3);        //allocate space for the new vertices/indices
    vc=VertexCount();
    ic=IndexCount();
    V = Vertices();
    I = Indices();

    for(i=0;i<vc;i++)
    {
        V[i] = OldV[OldI[i]];    //load the new vertex array
        I[i] = i;                //the new indices are trivial; we just take every triplet in the vertex array directly.
    }

    delete[] OldV;
    delete[] OldI;    //free up the storage
}

#ifdef USE_POINT_SET
void BaseMesh::WeldVertices(float Epsilon)
{
    Vector<UINT> OldToNewMapping;
    WeldVertices(Epsilon, OldToNewMapping);
    CleanVerticesAndTriangles();
}

void BaseMesh::WeldVertices(float Epsilon, Vector<UINT> &OldToNewMapping)
{
    PointSet MyPoints;
    MyPoints.LoadFromMesh(*this);
    KDTree3 &Tree = MyPoints.KDTree();
    
    UINT VC = VertexCount(), IC = IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    OldToNewMapping.ReSize(VC);
    OldToNewMapping.Clear(VC);
    Vector<UINT> NNResult;
    //MeshVertex *VStorage = new MeshVertex[VC];
    
    for(UINT VertexIndex = 0; VertexIndex < VC; VertexIndex++)
    {
        Vec3f Pos = V[VertexIndex].Pos;
        Tree.WithinDistance(Pos, Epsilon, NNResult);
        bool MatchFound = false;
        //VStorage[VertexIndex] = V[VertexIndex];
        for(UINT ResultIndex = 0; ResultIndex < NNResult.Length() && !MatchFound; ResultIndex++)
        {
            UINT CurIndex = NNResult[ResultIndex];
            if(OldToNewMapping[CurIndex] != VC)
            {
                MatchFound = true;
                OldToNewMapping[VertexIndex] = CurIndex;
            }
        }
        if(!MatchFound)
        {
            OldToNewMapping[VertexIndex] = VertexIndex;
        }
    }

    //DWORD *IStorage = new DWORD[IC];
    for(UINT IndexIndex = 0; IndexIndex < IC; IndexIndex++)
    {
        I[IndexIndex] = OldToNewMapping[UINT(I[IndexIndex])];
    }

    //Allocate(
    //delete[] VStorage;
    
    Vector<UINT> SecondMapping, SplitToUnsplit = OldToNewMapping;
    CleanVerticesAndTriangles(SecondMapping);
    for(UINT VertexIndex = 0; VertexIndex < VC; VertexIndex++)
    {
        OldToNewMapping[VertexIndex] = SecondMapping[SplitToUnsplit[VertexIndex]];
    }
}
#endif

void BaseMesh::Subdivide()
{
    ComplexMesh EM;
    EM.Load(*this);
    EM.Subdivision(*this);
}

void BaseMesh::Subdivide(UINT Iterations)
{
    for(UINT i = 0; i < Iterations; i++)
    {
        Subdivide();
    }
}