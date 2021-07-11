/*
BaseMeshSplitting.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshSplitting.cpp contains all the Split and PerfectSplit functions.
*/

struct SplitVMapper {
    unsigned char Side;
    int NVMap1,NVMap2;
};

Plane BaseMeshPlane;
float BaseMeshPlaneFunction(Vec3f &V)
{
    return V.x * BaseMeshPlane.a + V.y * BaseMeshPlane.b + V.z * BaseMeshPlane.c + BaseMeshPlane.d;
}

void BaseMesh::Split(Plane &p, BaseMesh &M1, BaseMesh &M2)
{
    BaseMeshPlane = p;
    Split(BaseMeshPlaneFunction, M1, M2);
}

void BaseMesh::Split(float (*PositionFunction) (Vec3f &), BaseMesh &M1, BaseMesh &M2)
{
    int i,vc=VertexCount(),ic=IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    Vector<MeshVertex> NV1,NV2;
    Vector<TriMeshFace> NT1,NT2;

    SplitVMapper *VMap = new SplitVMapper[vc];
    float Value;

    for(i=0;i<vc;i++)
    {
        Value = PositionFunction(V[i].Pos);
        if(Value < 0.0f)
        {
            VMap[i].Side = 0;
            VMap[i].NVMap1 = NV1.Length();
            VMap[i].NVMap2 = -1;
            NV1.PushEnd(V[i]);
        } else {
            VMap[i].Side = 1;
            VMap[i].NVMap1 = -1;
            VMap[i].NVMap2 = NV2.Length();
            NV2.PushEnd(V[i]);
        }
    }

    int TSide[3];
    TriMeshFace Tri;
    int Oddball,State;

    for(i=0;i<ic;i+=3)
    {
        TSide[0] = VMap[I[i]].Side;
        TSide[1] = VMap[I[i+1]].Side;
        TSide[2] = VMap[I[i+2]].Side;

        if(TSide[0] && TSide[1] && TSide[2]) //all O2
        {            
            Tri.I[0] = VMap[I[i]].NVMap2;
            Tri.I[1] = VMap[I[i+1]].NVMap2;
            Tri.I[2] = VMap[I[i+2]].NVMap2;
            NT2.PushEnd(Tri);
        } else if(!(TSide[0] || TSide[1] || TSide[2])) //all O1
        {
            Tri.I[0] = VMap[I[i]].NVMap1;
            Tri.I[1] = VMap[I[i+1]].NVMap1;
            Tri.I[2] = VMap[I[i+2]].NVMap1;
            NT1.PushEnd(Tri);
        } else {
            if(TSide[0] && TSide[1]) {Oddball = 2; State = 1;}
            if(TSide[0] && TSide[2]) {Oddball = 1; State = 1;}
            if(TSide[1] && TSide[2]) {Oddball = 0; State = 1;}
            if(!(TSide[0] || TSide[1])) {Oddball = 2; State = 2;}
            if(!(TSide[0] || TSide[2])) {Oddball = 1; State = 2;}
            if(!(TSide[1] || TSide[2])) {Oddball = 0; State = 2;}

            if(State == 1)    //Add to Obj2
            {
                if(VMap[I[i+Oddball]].NVMap2 == -1)
                {
                    VMap[I[i+Oddball]].NVMap2 = NV2.Length();
                    NV2.PushEnd(V[I[i+Oddball]]);
                }
                Tri.I[0] = VMap[I[i]].NVMap2;
                Tri.I[1] = VMap[I[i+1]].NVMap2;
                Tri.I[2] = VMap[I[i+2]].NVMap2;
                NT2.PushEnd(Tri);
            } else {        //Add to Obj1
                if(VMap[I[i+Oddball]].NVMap1 == -1)
                {
                    VMap[I[i+Oddball]].NVMap1 = NV1.Length();
                    NV1.PushEnd(V[I[i+Oddball]]);
                }
                Tri.I[0] = VMap[I[i]].NVMap1;
                Tri.I[1] = VMap[I[i+1]].NVMap1;
                Tri.I[2] = VMap[I[i+2]].NVMap1;
                NT1.PushEnd(Tri);
            }
        }
    }

    delete[] VMap;

    M1.Allocate(NV1.Length(),NT1.Length());
    M2.Allocate(NV2.Length(),NT2.Length());
    
    memcpy(M1.Vertices(), NV1.CArray(), M1.VertexCount() * sizeof(MeshVertex));
    memcpy(M2.Vertices(), NV2.CArray(), M2.VertexCount() * sizeof(MeshVertex));
    memcpy(M1.Indices(), NT1.CArray(), M1.IndexCount() * sizeof(DWORD));
    memcpy(M2.Indices(), NT2.CArray(), M2.IndexCount() * sizeof(DWORD));
}

float (*PerfectSplitPositionFunction) (Vec3f &);
Vec3f PerfectSplitV1, PerfectSplitV2;

float PerfectSplitZeroSearch(float s)
{
    return PerfectSplitPositionFunction(PerfectSplitV1 + s * (PerfectSplitV2 - PerfectSplitV1));
}

//0 = M1
//1 = M2
const int M1Indices[8][6] = {
    {0,1,2,        -1,-1,-1},
    {0,1,4,        0,4,5    },
    {0,3,4,        0,4,2    },
    {0,3,5,        -1,-1,-1},
    {5,3,2,        3,1,2    },
    {3, 1, 4,    -1,-1,-1},
    {5, 4, 2,    -1,-1,-1},
    {-1,-1,-1,    -1,-1,-1}};

const int M2Indices[8][6] = {
    {-1,-1,-1,    -1,-1,-1},
    {5,4,2,        -1,-1,-1},
    {3,1,4,        -1,-1,-1},
    {5,3,2,        3,1,2    },
    {0,3,5,        -1,-1,-1},
    {0,3,4,        0,4,2    },
    {0,1,4,        0,4,5    },
    {0,1,2,        -1,-1,-1}};

const bool PerfectEdges[8][3] = {
    {false, false, false},
    {false, true, true},
    {true, true, false},
    {true, false, true},
    {true, false, true},
    {true, true, false},
    {false, true, true},
    {false, false, false}};

const int PerfectEdgeList[3][2] = {
    {0, 1},
    {1, 2},
    {2, 0}};

struct PerfectSplitVMapper {
    int Side;
    int NVMap;
};

void BaseMesh::RotateFaces()
{
    DWORD *_Indices = Indices();
    UINT _FaceCount = FaceCount();
    for(UINT FaceIndex = 0; FaceIndex < _FaceCount; FaceIndex++)
    {
        Utility::Swap(_Indices[FaceIndex * 3 + 0], _Indices[FaceIndex * 3 + 1]);
    }
    GenerateNormals();
}

float BaseMesh::SidedSurfaceArea(const Plane &P)
{
    float Result = 0.0f;
    DWORD *MyIndices = Indices();
    MeshVertex *MyVertices = Vertices();
    UINT TriangleCount = FaceCount();
    for(UINT TriangleIndex = 0; TriangleIndex < TriangleCount; TriangleIndex++)
    {
        Vec3f LocalTriangle[6];
        UINT TSide[3];
        for(UINT LocalVertexIndex = 0; LocalVertexIndex < 3; LocalVertexIndex++)
        {
            LocalTriangle[LocalVertexIndex] = MyVertices[MyIndices[TriangleIndex * 3 + LocalVertexIndex]].Pos;
            if(Plane::DotCoord(P, LocalTriangle[LocalVertexIndex]) < 0.0f)
            {
                TSide[LocalVertexIndex] = 0;
            }
            else
            {
                TSide[LocalVertexIndex] = 1;
            }
        }
        UINT TriangleType = TSide[0] * 4 + TSide[1] * 2 + TSide[2] * 1;

        for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
        {
            if(PerfectEdges[TriangleType][EdgeIndex])
            {
                Vec3f Vtx1 = MyVertices[MyIndices[TriangleIndex * 3 + PerfectEdgeList[EdgeIndex][0]]].Pos;
                Vec3f Vtx2 = MyVertices[MyIndices[TriangleIndex * 3 + PerfectEdgeList[EdgeIndex][1]]].Pos;
                Vec3f VtxIntersect = P.IntersectLine(Vtx1, Vtx2);
                if(!Vec3f::WithinRect(VtxIntersect, Rectangle3f::ConstructFromTwoPoints(Vtx1, Vtx2)))
                {
                    VtxIntersect = (Vtx1 + Vtx2) * 0.5f;
                }
                
                LocalTriangle[3 + EdgeIndex] = VtxIntersect;
            }
        }

        for(UINT LocalTriangleIndex = 0; LocalTriangleIndex < 6; LocalTriangleIndex += 3)
        {
            if(M1Indices[TriangleType][LocalTriangleIndex] != -1)
            {
                Vec3f V[3];
                V[0] = LocalTriangle[M1Indices[TriangleType][LocalTriangleIndex + 0]];
                V[1] = LocalTriangle[M1Indices[TriangleType][LocalTriangleIndex + 1]];
                V[2] = LocalTriangle[M1Indices[TriangleType][LocalTriangleIndex + 2]];
                Result += Math::TriangleArea(V[0], V[1], V[2]);
            }
        }
    }
    return Result;
}

void BaseMesh::ClosedPlaneSplit(const Plane &P, BaseMesh &M1, BaseMesh &M2)
{
    UINT VC = VertexCount(), IC = IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    Vector<Vec3f> NewVertices[2];
    Vector<TriMeshFace> NewFaces[2];
    Vector<Vec2f> BoundaryVertices;
    Vector<UINT> BoundaryIndices[2];

    Vec3f OrthogonalBasis1, OrthogonalBasis2;
    Vec3f::CompleteOrthonormalBasis(P.Normal(), OrthogonalBasis1, OrthogonalBasis2);

    PerfectSplitVMapper *VMap = new PerfectSplitVMapper[VC];
    
    for(UINT VertexIndex = 0; VertexIndex < VC; VertexIndex++)
    {
        Vec3f Pos = V[VertexIndex].Pos;
        float Value = Plane::DotCoord(P, Pos);
        if(Value < 0.0f)
        {
            VMap[VertexIndex].Side = 0;
            VMap[VertexIndex].NVMap = NewVertices[0].Length();
            NewVertices[0].PushEnd(Pos);
        }
        else
        {
            VMap[VertexIndex].Side = 1;
            VMap[VertexIndex].NVMap = NewVertices[1].Length();
            NewVertices[1].PushEnd(Pos);
        }
    }

    for(UINT IndexIndex = 0; IndexIndex < IC; IndexIndex += 3)
    {
        int TSide[3];
        TSide[0] = VMap[I[IndexIndex + 0]].Side;
        TSide[1] = VMap[I[IndexIndex + 1]].Side;
        TSide[2] = VMap[I[IndexIndex + 2]].Side;

        DWORD LocalTriangleM1[6], LocalTriangleM2[6];
        LocalTriangleM2[0] = LocalTriangleM1[0] = VMap[I[IndexIndex + 0]].NVMap;
        LocalTriangleM2[1] = LocalTriangleM1[1] = VMap[I[IndexIndex + 1]].NVMap;
        LocalTriangleM2[2] = LocalTriangleM1[2] = VMap[I[IndexIndex + 2]].NVMap;

        UINT TriangleType = TSide[0] * 4 + TSide[1] * 2 + TSide[2] * 1;

        for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
        {
            if(PerfectEdges[TriangleType][EdgeIndex])
            {
                Vec3f Vtx1 = V[I[IndexIndex + PerfectEdgeList[EdgeIndex][0]]].Pos;
                Vec3f Vtx2 = V[I[IndexIndex + PerfectEdgeList[EdgeIndex][1]]].Pos;
                Vec3f VtxIntersect = P.IntersectLine(Vtx1, Vtx2);
                
                if(!Vec3f::WithinRect(VtxIntersect, Rectangle3f::ConstructFromTwoPoints(Vtx1, Vtx2)))
                {
                    VtxIntersect = (Vtx1 + Vtx2) * 0.5f;
                }
                
                BoundaryVertices.PushEnd(Vec2f(Vec3f::Dot(VtxIntersect, OrthogonalBasis1), Vec3f::Dot(VtxIntersect, OrthogonalBasis2)));

                LocalTriangleM1[3 + EdgeIndex] = NewVertices[0].Length();
                BoundaryIndices[0].PushEnd(NewVertices[0].Length());
                NewVertices[0].PushEnd(VtxIntersect);

                LocalTriangleM2[3 + EdgeIndex] = NewVertices[1].Length();
                BoundaryIndices[1].PushEnd(NewVertices[1].Length());
                NewVertices[1].PushEnd(VtxIntersect);
            }
        }

        for(UINT LocalTriangleIndex = 0; LocalTriangleIndex < 6; LocalTriangleIndex += 3)
        {
            if(M1Indices[TriangleType][LocalTriangleIndex] != -1)
            {
                TriMeshFace Tri;
                Tri.I[0] = LocalTriangleM1[M1Indices[TriangleType][LocalTriangleIndex + 0]];
                Tri.I[1] = LocalTriangleM1[M1Indices[TriangleType][LocalTriangleIndex + 1]];
                Tri.I[2] = LocalTriangleM1[M1Indices[TriangleType][LocalTriangleIndex + 2]];
                NewFaces[0].PushEnd(Tri);
            }
            if(M2Indices[TriangleType][LocalTriangleIndex] != -1)
            {
                TriMeshFace Tri;
                Tri.I[0] = LocalTriangleM2[M2Indices[TriangleType][LocalTriangleIndex + 0]];
                Tri.I[1] = LocalTriangleM2[M2Indices[TriangleType][LocalTriangleIndex + 1]];
                Tri.I[2] = LocalTriangleM2[M2Indices[TriangleType][LocalTriangleIndex + 2]];
                NewFaces[1].PushEnd(Tri);
            }
        }
    }

#ifdef DELAUNAY_TRIANGULATOR
    if(BoundaryVertices.Length() > 0)
    {
        Vector<DWORD> BoundaryTriangulation;
        DelaunayTriangulator::Triangulate(BoundaryVertices, BoundaryTriangulation);
        for(UINT TriangleIndex = 0; TriangleIndex < BoundaryTriangulation.Length() / 3; TriangleIndex++)
        {
            for(UINT MeshIndex = 0; MeshIndex < 2; MeshIndex++)
            {
                TriMeshFace Tri;
                Vec3f V[3];
                for(UINT LocalVertexIndex = 0; LocalVertexIndex < 3; LocalVertexIndex++)
                {
                    Tri.I[LocalVertexIndex] = BoundaryIndices[MeshIndex][UINT(BoundaryTriangulation[TriangleIndex * 3 + LocalVertexIndex])];
                    V[LocalVertexIndex] = NewVertices[MeshIndex][UINT(Tri.I[LocalVertexIndex])];
                }
                //Utility::Swap(Tri.I[0], Tri.I[1]);
                //if(Math::TriangleArea(V[0], V[1], V[2]) > 1e-5f)
                {
                    NewFaces[MeshIndex].PushEnd(Tri);
                }
            }
        }
    }
#endif

    delete[] VMap;

    M1.SetGD(GetGD());
    M2.SetGD(GetGD());
    M1.Allocate(NewVertices[0].Length(), NewFaces[0].Length());
    M2.Allocate(NewVertices[1].Length(), NewFaces[1].Length());
    
    for(UINT VertexIndex = 0; VertexIndex < NewVertices[0].Length(); VertexIndex++)
    {
        M1.Vertices()[VertexIndex].Pos = NewVertices[0][VertexIndex];
    }
    for(UINT VertexIndex = 0; VertexIndex < NewVertices[1].Length(); VertexIndex++)
    {
        M2.Vertices()[VertexIndex].Pos = NewVertices[1][VertexIndex];
    }
    
    if(NewFaces[0].Length() > 0)
    {
        memcpy(M1.Indices(), NewFaces[0].CArray(), M1.IndexCount() * sizeof(DWORD));
    }
    if(NewFaces[1].Length() > 0)
    {
        memcpy(M2.Indices(), NewFaces[1].CArray(), M2.IndexCount() * sizeof(DWORD));
    }
}

void BaseMesh::CullFaces(const BYTE FaceTest[])
{
    Vector<DWORD> NewIndices;
    Vector<MeshVertex> NewVertices;
    UINT NumFaces = FaceCount(), NumVertices = VertexCount();
    DWORD *I = Indices();
    MeshVertex *V = Vertices();
    for(UINT VertexIndex = 0; VertexIndex < NumVertices; VertexIndex++)
    {
        NewVertices.PushEnd(V[VertexIndex]);
    }
    for(UINT FaceIndex = 0; FaceIndex < NumFaces; FaceIndex++)
    {
        if(FaceTest[FaceIndex])
        {
            for(UINT i = 0; i < 3; i++)
            {
                NewIndices.PushEnd(I[FaceIndex * 3 + i]);
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