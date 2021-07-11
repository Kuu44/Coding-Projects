/*
ComplexMesh.cpp
Written by Matthew Fisher

ComplexMesh is a complex (edge-based) mesh structure.
*/

HalfEdge HalfEdge::Invalid;
FullEdge FullEdge::Invalid;
Triangle Triangle::Invalid;
Vertex Vertex::Invalid;

Triangle Triangle::Boundary;
FullEdge FullEdge::NotFound;

ComplexMesh::ComplexMesh()
{

}

ComplexMesh::~ComplexMesh()
{
    FreeMemory();
}

ComplexMesh::ComplexMesh(const ComplexMesh &M)
{
    Mesh MTemp;
    M.Dump(MTemp);
    Load(MTemp);
}

void ComplexMesh::FreeMemory()
{
    _Vertices.FreeMemory();
    _Triangles.FreeMemory();
    _HalfEdges.FreeMemory();

    for(UINT i = 0; i < _FullEdges.Length(); i++)
    {
        delete _FullEdges[i];
    }
    _FullEdges.FreeMemory();
    ClearHashTable();
}

ComplexMesh& ComplexMesh::operator = (const ComplexMesh &M)
{
    Mesh MTemp;
    M.Dump(MTemp);
    Load(MTemp);
    return *this;
}

bool ComplexMesh::ShootRay(const D3D9Mesh &M, const Vec3f &Pos, const Vec3f &Dir, UINT &TriangleIndex, UINT &VertexIndex, UINT &EdgeIndex, Vec3f &WorldPos) const
{
#ifdef USE_D3D9
    Vector<float> Hits;
    Vec3f NormalizedDir = Vec3f::Normalize(Dir);
    float u, v;
    DWORD FaceIndex;
    M.QueryHits(Pos, NormalizedDir, Hits, FaceIndex, u, v);
    if(Hits.Length() > 0)
    {
        TriangleIndex = FaceIndex;
        WorldPos = Pos + NormalizedDir * Hits[0];
        float ClosestVertexDistance = 1e10f, ClosestEdgeDistance = 1e10f;
        const Triangle &CurTriangle = _Triangles[TriangleIndex];
        for(UINT LocalIndex = 0; LocalIndex < 3; LocalIndex++)
        {
            float CurVertexDistance = Vec3f::Dist(CurTriangle.GetVertex(LocalIndex).Pos(), WorldPos);
            if(CurVertexDistance < ClosestVertexDistance)
            {
                ClosestVertexDistance = CurVertexDistance;
                VertexIndex = CurTriangle.GetVertex(LocalIndex).Index();
            }
            float CurEdgeDistance = Vec3f::Dist(CurTriangle.GetFullEdge(LocalIndex).Center(), WorldPos);
            if(CurEdgeDistance < ClosestEdgeDistance)
            {
                ClosestEdgeDistance = CurEdgeDistance;
                EdgeIndex = CurTriangle.GetFullEdge(LocalIndex).Index();
            }
        }
        return true;
    }
    else
    {
        VertexIndex = _Vertices.Length();
        EdgeIndex = _FullEdges.Length();
        TriangleIndex = _Triangles.Length();
        return false;
    }
#else
    SignalError("DirectX 9 required for ComplexMesh::ShootRay");
    return false;
#endif
}

float ComplexMesh::AverageEdgeLength() const
{
    float Avg = 0.0f;
    for(UINT EdgeIndex = 0; EdgeIndex < _FullEdges.Length(); EdgeIndex++)
    {
        Avg += _FullEdges[EdgeIndex]->Vector().Length();
    }
    return Avg / _FullEdges.Length();
}

float ComplexMesh::AverageTriangleArea() const
{
    float Avg = 0.0f;
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Avg += _Triangles[TriangleIndex].Area();
    }
    return Avg / _Triangles.Length();
}

void ComplexMesh::ValidateTopology()
{
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = _Triangles[TriangleIndex];
        for(UINT i = 0; i < 3; i++)
        {
            PersistentAssert(CurTriangle.GetHalfEdge(i).NextEdge() == CurTriangle.GetHalfEdge((i + 1) % 3), "Invalid topology");
            PersistentAssert(CurTriangle.GetHalfEdge(i).AcrossEdge() == CurTriangle.GetFullEdge(i), "Invalid topology");
        }
    }
}

void ComplexMesh::VerboseSave(const String &Filename)
{
    ofstream File(Filename.CString());
    File << "Triangle Count: " << _Triangles.Length() << endl;
    File << "Index\tEdges\t\t\tVertices\t\t\t\n";
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = _Triangles[TriangleIndex];
        File << TriangleIndex << '\t';
        for(UINT i = 0; i < 3; i++)
        {
            File << CurTriangle.GetHalfEdge(i).AcrossEdge().Index() << '\t';
        }
        for(UINT i = 0; i < 3; i++)
        {
            File << CurTriangle.GetVertex(i).Index() << '\t';
        }
        File << endl;
    }
    File << "Edge Count: " << _FullEdges.Length() << endl;
    File << "Index\tTriangles\t\tVertices\t\t\n";
    for(UINT EdgeIndex = 0; EdgeIndex < _FullEdges.Length(); EdgeIndex++)
    {
        FullEdge &CurEdge = *(_FullEdges[EdgeIndex]);
        File << EdgeIndex << '\t';
        for(UINT i = 0; i < 2; i++)
        {
            if(CurEdge.GetTriangle(i) == Triangle::Boundary)
            {
                File << "Boundary" << '\t';
            }
            else
            {
                File << CurEdge.GetTriangle(i).Index() << '\t';
            }
        }
        for(UINT i = 0; i < 2; i++)
        {
            File << CurEdge.GetVertex(i).Index() << '\t';
        }
        File << endl;
    }
}

bool ComplexMesh::ComputeDiskBoundary(Vector<FullEdge *> &Boundary)
{
    Boundary.FreeMemory();
    FullEdge *InitialBoundaryEdge = NULL;

    Vector<BYTE> VerticesVisited(_Vertices.Length());
    Vector<BYTE> EdgesVisited(_FullEdges.Length());
    VerticesVisited.Clear(0);
    EdgesVisited.Clear(0);

    for(UINT EdgeIndex = 0; EdgeIndex < _FullEdges.Length(); EdgeIndex++)
    {
        FullEdge *CurEdge = _FullEdges[EdgeIndex];
        if(CurEdge->Boundary())
        {
            InitialBoundaryEdge = CurEdge;
        }
    }

    if(InitialBoundaryEdge == NULL)
    {
        return false;
    }

    bool Done = false;
    FullEdge *CurBoundaryEdge = InitialBoundaryEdge;
    Vertex *StartVertex = &(CurBoundaryEdge->GetVertex(0));
    while(!Done)
    {
        Boundary.PushEnd(CurBoundaryEdge);
        EdgesVisited[CurBoundaryEdge->Index()] = true;
        VerticesVisited[CurBoundaryEdge->GetVertex(1).Index()] = true;

        Vertex &CurVertex = CurBoundaryEdge->GetVertex(1);
        bool NextEdgeFound = false;
        for(UINT i = 0; i < CurVertex.Vertices().Length() && !NextEdgeFound; i++)
        {
            Vertex *NeighborVertex = CurVertex.Vertices()[i];
            FullEdge &CurEdge = CurVertex.GetSharedEdge(*NeighborVertex);
            if(CurEdge.Boundary() && (CurEdge.GetVertex(0) == CurVertex))
            {
                NextEdgeFound = true;
                CurBoundaryEdge = &CurEdge;
                if(CurBoundaryEdge == InitialBoundaryEdge)
                {
                    Done = true;
                }
                else if(EdgesVisited[CurBoundaryEdge->Index()])
                {
                    SignalError("Revisited an edge!");
                }
            }
        }
        
        if(!NextEdgeFound)
        {
            SignalError("Invalid boundary behavior");
        }
    }

    for(UINT EdgeIndex = 0; EdgeIndex < _FullEdges.Length(); EdgeIndex++)
    {
        FullEdge *CurEdge = _FullEdges[EdgeIndex];
        if(!EdgesVisited[CurEdge->Index()])
        {
            //return false;
        }
    }
    return true;
}

bool ComplexMesh::ComputeDiskParameterization(bool Natural)
{
    const float Lambda = 1.0f;

    Vector<FullEdge *> Boundary;
    if(!ComputeDiskBoundary(Boundary))
    {
        return false;
    }

    float TotalBoundaryLength = 0.0f;
    for(UINT i = 0; i < Boundary.Length(); i++)
    {
        TotalBoundaryLength += Boundary[i]->Vector().Length();
        if(i != 0)
        {
            Assert(Boundary[i]->GetVertex(0).Index() == Boundary[i - 1]->GetVertex(1).Index(), "Invalid boundary");
        }
    }
    PersistentAssert(TotalBoundaryLength > 0.0f, "Invalid boundary");

    float CurBoundaryLength = 0.0f;
    for(UINT i = 0; i < Boundary.Length(); i++)
    {
        Vertex &CurVertex = Boundary[i]->GetVertex(0);
        CurVertex.TexCoords() = Vec2f::ConstructFromPolar(0.5f, 2.0f * Math::PIf * CurBoundaryLength / TotalBoundaryLength) + Vec2f(0.5f, 0.5f);
        CurBoundaryLength += Boundary[i]->Vector().Length();
    }
    
    SparseMatrix<double> M(_Vertices.Length() * 2);
    
    const UINT FixedIndexCount = 2;
    UINT FixedIndices[FixedIndexCount];
    FixedIndices[0] = Boundary[0]->GetVertex(0).Index();
    FixedIndices[1] = Boundary[Boundary.Length() / 2]->GetVertex(1).Index();

    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(CurVertex.Boundary())
        {
            if(Natural && VertexIndex != FixedIndices[0] && VertexIndex != FixedIndices[1])
            {
                for(UINT TriangleIndex = 0; TriangleIndex < CurVertex.Triangles().Length(); TriangleIndex++)
                {
                    Triangle &CurTriangle = *(CurVertex.Triangles()[TriangleIndex]);
                    UINT IBaseIndex = CurTriangle.GetVertexLocalIndex(CurVertex);
                    UINT IIndex = CurTriangle.GetVertex((IBaseIndex + 0) % 3).Index();
                    UINT JIndex = CurTriangle.GetVertex((IBaseIndex + 1) % 3).Index();
                    UINT KIndex = CurTriangle.GetVertex((IBaseIndex + 2) % 3).Index();

                    double Alpha = CurTriangle.GetCotangent(CurTriangle.GetVertex((IBaseIndex + 2) % 3));
                    double Beta = CurTriangle.GetCotangent(CurTriangle.GetVertex((IBaseIndex + 1) % 3));

                    M.PushElement(2 * VertexIndex + 0, 2 * IIndex + 0, Alpha + Beta);
                    M.PushElement(2 * VertexIndex + 1, 2 * IIndex + 1, Alpha + Beta);

                    M.PushElement(2 * VertexIndex + 0, 2 * JIndex + 0, -Alpha);
                    M.PushElement(2 * VertexIndex + 1, 2 * JIndex + 1, -Alpha);

                    M.PushElement(2 * VertexIndex + 0, 2 * KIndex + 0, -Beta);
                    M.PushElement(2 * VertexIndex + 1, 2 * KIndex + 1, -Beta);

                    M.PushElement(2 * VertexIndex + 0, 2 * JIndex + 1, 1.0);
                    M.PushElement(2 * VertexIndex + 1, 2 * JIndex + 0, -1.0);

                    M.PushElement(2 * VertexIndex + 0, 2 * KIndex + 1, -1.0);
                    M.PushElement(2 * VertexIndex + 1, 2 * KIndex + 0, 1.0);
                }
                /*for(UINT EdgeIndex = 0; EdgeIndex < CurVertex.Vertices().Length(); EdgeIndex++)
                {
                    Vertex &OtherVertex = *(CurVertex.Vertices()[EdgeIndex]);
                    FullEdge &CurEdge = CurVertex.GetSharedEdge(OtherVertex);
                    double ConstantFactor = Lambda * CurEdge.GetCotanTerm();
                    Assert(ConstantFactor == ConstantFactor, "ConstantFactor invalid");
                    M.PushDiagonalElement(VertexIndex * 2 + 0, -ConstantFactor);
                    M.PushDiagonalElement(VertexIndex * 2 + 1, -ConstantFactor);
                    M.PushElement(VertexIndex * 2 + 0, OtherVertex.Index() * 2 + 1, ConstantFactor);
                    M.PushElement(VertexIndex * 2 + 0, OtherVertex.Index() * 2 + 1, ConstantFactor);
                    M.PushElement(VertexIndex * 2 + 1, OtherVertex.Index() * 2 + 0, 1.0f);
                    M.PushElement(VertexIndex * 2 + 0, OtherVertex.Index() * 2 + 1, -1.0f);
                }*/
            }
            else
            {
                M.PushDiagonalElement(VertexIndex * 2 + 0, 1.0f);
                M.PushDiagonalElement(VertexIndex * 2 + 1, 1.0f);
            }
        }
        else
        {
            //M.PushDiagonalElement(VertexIndex * 2 + 0, VertexAreas[VertexIndex]);
            //M.PushDiagonalElement(VertexIndex * 2 + 1, VertexAreas[VertexIndex]);
            for(UINT EdgeIndex = 0; EdgeIndex < CurVertex.Vertices().Length(); EdgeIndex++)
            {
                Vertex &OtherVertex = *(CurVertex.Vertices()[EdgeIndex]);
                FullEdge &CurEdge = CurVertex.GetSharedEdge(OtherVertex);
                double ConstantFactor = Lambda * CurEdge.GetCotanTerm();
                Assert(ConstantFactor == ConstantFactor, "ConstantFactor invalid");
                M.PushDiagonalElement(VertexIndex * 2 + 0, -ConstantFactor);
                M.PushDiagonalElement(VertexIndex * 2 + 1, -ConstantFactor);
                M.PushElement(VertexIndex * 2 + 0, OtherVertex.Index() * 2 + 0, ConstantFactor);
                M.PushElement(VertexIndex * 2 + 1, OtherVertex.Index() * 2 + 1, ConstantFactor);
            }
        }
    }

    BiCGLinearSolver<double> Solver;
    //TaucsSymmetricLinearSolver Solver;
    Solver.LoadMatrix(&M);
    Solver.Factor();
    //ofstream File("Matrix.TexCoord.xt");
    //M.Dump(File, false);
    //File << endl;
    Solver.SetParamaters(1000, 1e-6);

    Vector<double> x(_Vertices.Length() * 2), b(_Vertices.Length() * 2);
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(CurVertex.Boundary())
        {
            if(!Natural || VertexIndex == FixedIndices[0] || VertexIndex == FixedIndices[1])
            {
                x[VertexIndex * 2 + 0] = CurVertex.TexCoords().x;
                x[VertexIndex * 2 + 1] = CurVertex.TexCoords().y;
                b[VertexIndex * 2 + 0] = CurVertex.TexCoords().x;
                b[VertexIndex * 2 + 1] = CurVertex.TexCoords().y;
            }
            else
            {
                x[VertexIndex * 2 + 0] = CurVertex.Pos().x;
                x[VertexIndex * 2 + 1] = CurVertex.Pos().y;
                b[VertexIndex * 2 + 0] = 0.0f;
                b[VertexIndex * 2 + 1] = 0.0f;
            }
        }
        else
        {
            x[VertexIndex * 2 + 0] = CurVertex.Pos().x;
            x[VertexIndex * 2 + 1] = CurVertex.Pos().y;
            b[VertexIndex * 2 + 0] = 0.0f;
            b[VertexIndex * 2 + 1] = 0.0f;
        }
        //File << b[VertexIndex * 2 + 0] << '\t' << b[VertexIndex * 2 + 1] << endl;
    }
    Solver.Solve(x, b);
    Console::WriteLine(Solver.GetOutputString());
    double Error = Solver.ComputeError(x, b);
    Console::WriteLine(String("Parameterization error: ") + String(Error));
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(Natural || !CurVertex.Boundary())
        {
            CurVertex.TexCoords().x = float(x[VertexIndex * 2 + 0]);
            CurVertex.TexCoords().y = float(x[VertexIndex * 2 + 1]);
        }
    }

    return true;
}

void ComplexMesh::ComputeConstrainedParameterization()
{
    const float Lambda = 1.0f;

    SparseMatrix<double> M(_Vertices.Length() * 2);
    Vector<double> x(_Vertices.Length() * 2), b(_Vertices.Length() * 2);
    
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(CurVertex.Boundary())
        {
            M.PushDiagonalElement(VertexIndex * 2 + 0, 1.0f);
            M.PushDiagonalElement(VertexIndex * 2 + 1, 1.0f);
        }
        else
        {
            for(UINT EdgeIndex = 0; EdgeIndex < CurVertex.Vertices().Length(); EdgeIndex++)
            {
                Vertex &OtherVertex = *(CurVertex.Vertices()[EdgeIndex]);
                FullEdge &CurEdge = CurVertex.GetSharedEdge(OtherVertex);
                double ConstantFactor = Lambda * CurEdge.GetCotanTerm();
                Assert(ConstantFactor == ConstantFactor, "ConstantFactor invalid");
                M.PushDiagonalElement(VertexIndex * 2 + 0, -ConstantFactor);
                M.PushDiagonalElement(VertexIndex * 2 + 1, -ConstantFactor);
                M.PushElement(VertexIndex * 2 + 0, OtherVertex.Index() * 2 + 0, ConstantFactor);
                M.PushElement(VertexIndex * 2 + 1, OtherVertex.Index() * 2 + 1, ConstantFactor);
            }
        }
    }

    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(CurVertex.Boundary())
        {
            x[VertexIndex * 2 + 0] = CurVertex.TexCoords().x;
            x[VertexIndex * 2 + 1] = CurVertex.TexCoords().y;
            b[VertexIndex * 2 + 0] = CurVertex.TexCoords().x;
            b[VertexIndex * 2 + 1] = CurVertex.TexCoords().y;
        }
        else
        {
            //x[VertexIndex * 2 + 0] = CurVertex.Pos().x;
            //x[VertexIndex * 2 + 1] = CurVertex.Pos().y;
            x[VertexIndex * 2 + 0] = pmrnd() * 0.01f;
            x[VertexIndex * 2 + 1] = pmrnd() * 0.01f;
            b[VertexIndex * 2 + 0] = 0.0f;
            b[VertexIndex * 2 + 1] = 0.0f;
        }
    }

    BiCGLinearSolver<double> Solver;
    //TaucsSymmetricLinearSolver Solver;
    Solver.LoadMatrix(&M);
    Solver.Factor();
    Solver.SetParamaters(1000, 1e-6);

    Solver.Solve(x, b);
    Console::WriteLine(Solver.GetOutputString());
    double Error = Solver.ComputeError(x, b);
    Console::WriteLine(String("Parameterization error: ") + String(Error));
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(!CurVertex.Boundary())
        {
            CurVertex.TexCoords().x = float(x[VertexIndex * 2 + 0]);
            CurVertex.TexCoords().y = float(x[VertexIndex * 2 + 1]);
        }
        //Console::WriteLine(String(CurVertex.TexCoords().x));
    }
}

void ComplexMesh::ExplicitMeanCurvatureFlow(float TimeStep)
{
    Vector<Vec3f> NewVertexPositions(_Vertices.Length());
    float AverageDelta = 0.0f;
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        Vec3f Delta = -TimeStep * CurVertex.MeanCurvatureNormal();
        AverageDelta += Delta.Length();
        NewVertexPositions[VertexIndex] = Delta;
    }
    AverageDelta /= _Vertices.Length();
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        if(NewVertexPositions[VertexIndex].Length() > 2.0f * AverageDelta)
        {
            NewVertexPositions[VertexIndex].SetLength(2.0f * AverageDelta);
        }
        CurVertex.Pos() += NewVertexPositions[VertexIndex];
    }
}

void ComplexMesh::ImplicitMeanCurvatureFlow(float TimeStep)
{
    Vector<double> VertexAreas(_Vertices.Length());
    Vector<Vec3f> NewVertexPositions(_Vertices.Length());
    NewVertexPositions.Clear(Vec3f::Origin);

    
    SparseMatrix<double> M(_Vertices.Length());

    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        VertexAreas[VertexIndex] = CurVertex.ComputeTriangleArea();
        M.PushElement(VertexIndex, VertexIndex, VertexAreas[VertexIndex]);
        //M.PushElement(VertexIndex, VertexIndex, 1.0f);
        for(UINT EdgeIndex = 0; EdgeIndex < CurVertex.Vertices().Length(); EdgeIndex++)
        {
            Vertex &OtherVertex = *(CurVertex.Vertices()[EdgeIndex]);
            FullEdge &CurEdge = CurVertex.GetSharedEdge(OtherVertex);
            double ConstantFactor = CurEdge.GetCotanTerm() / 4.0f;
            Assert(ConstantFactor == ConstantFactor, "ConstantFactor invalid");
            M.PushElement(VertexIndex, VertexIndex, TimeStep * ConstantFactor);
            M.PushElement(VertexIndex, OtherVertex.Index(), -TimeStep * ConstantFactor);
        }
    }

    BiCGLinearSolver<double> Solver;
    Solver.LoadMatrix(&M);
    const double ErrorTolerance = 1e-6;
    Solver.SetParamaters(1000, ErrorTolerance);
    Solver.Factor();

    for(UINT ElementIndex = 0; ElementIndex < 3; ElementIndex++)
    {
        Vector<double> x, b(_Vertices.Length());
        for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
        {
            b[VertexIndex] = _Vertices[VertexIndex].Pos()[ElementIndex] * VertexAreas[VertexIndex];
            //b[VertexIndex] = _Vertices[VertexIndex].Pos().Element(ElementIndex);
        }
        Solver.Solve(x, b);
        Console::WriteLine(Solver.GetOutputString());
        double Error = Solver.ComputeError(x, b);
        Console::WriteLine(String("Mean curvature error: ") + String(Error));
        if(Error < ErrorTolerance)
        {
            for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
            {
                NewVertexPositions[VertexIndex][ElementIndex] = float(x[VertexIndex]);
            }
        }
    }

    float AverageDelta = 0.0f;
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vec3f Delta = NewVertexPositions[VertexIndex] - _Vertices[VertexIndex].Pos();
        AverageDelta += Delta.Length();
    }
    AverageDelta /= _Vertices.Length();
    for(UINT VertexIndex = 0; VertexIndex < _Vertices.Length(); VertexIndex++)
    {
        Vertex &CurVertex = _Vertices[VertexIndex];
        Vec3f Delta = NewVertexPositions[VertexIndex] - _Vertices[VertexIndex].Pos();
        if(Delta.Length() > 2.0f * AverageDelta)
        {
            Delta.SetLength(2.0f * AverageDelta);
        }
        CurVertex.Pos() += Delta;
    }
}

bool ComplexMesh::Oriented()
{
    for(UINT i = 0; i < _FullEdges.Length(); i++)
    {
        FullEdge *CurEdge = _FullEdges[i];
        if(!CurEdge->Oriented())
        {
            return false;
        }
    }
    return true;
}

void ComplexMesh::ClearHashTable()
{
    for(UINT i = 0; i < _HashTable.Length(); i++)
    {
        if(_HashTable[i].Length() > 0)
        {
            _HashTable[i].FreeMemory();
        }
    }
    _HashTable.FreeMemory();
}

void ComplexMesh::InitHashTable(UINT Size)
{
    ClearHashTable();
    _HashTable.Allocate(Size);
}

void ComplexMesh::HashEdge(const FullEdge &FullE)
{
    Assert(FullE.GetVertex(0).Index() < FullE.GetVertex(1).Index(), "Invalid vertex ordering");
    //Console::WriteLine(String("Enqueing edge: ") + String(FullE.GetVertex(0).Index()) + String(", ") + String(FullE.GetVertex(1).Index()));
    UINT HTableIndex = FullE.GetVertex(0).Index() % _HashTable.Length();
    _HashTable[HTableIndex].PushEnd(FullE.Index());
}

FullEdge& ComplexMesh::FindFullEdge(Vertex *SearchV[2])
{
    UINT HTableIndex = SearchV[0]->Index() % _HashTable.Length();
    ComplexMeshEdgeHash &CurHashTable = _HashTable[HTableIndex];

    for(UINT EntryIndex = 0; EntryIndex < CurHashTable.Length(); EntryIndex++)
    {
        FullEdge &CurFullEdge = *(_FullEdges[CurHashTable[EntryIndex]]);
        if(CurFullEdge.ContainsVertex(*SearchV[0]) && CurFullEdge.ContainsVertex(*SearchV[1]))
        {
             return CurFullEdge;
        }
    }
    return FullEdge::NotFound;
}

void ComplexMesh::Load(const BaseMesh &Mesh)
{
    FreeMemory();
    
    _Vertices.Allocate(Mesh.VertexCount());
    _Triangles.Allocate(Mesh.FaceCount());
    _HalfEdges.Allocate(Mesh.FaceCount() * 3);
    _FullEdges.FreeMemory();

    for(UINT i = 0; i < _Vertices.Length(); i++)
    {
        _Vertices[i].Pos() = Mesh.Vertices()[i].Pos;
        _Vertices[i].TexCoords() = Mesh.Vertices()[i].TexCoord;
        _Vertices[i].Boundary() = false;
        _Vertices[i]._Index = i;
    }

    InitHashTable(_Vertices.Length());

    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = _Triangles[TriangleIndex];
        UINT LocalIndices[3];
        LocalIndices[0] = Mesh.Indices()[TriangleIndex * 3 + 0];
        LocalIndices[1] = Mesh.Indices()[TriangleIndex * 3 + 1];
        LocalIndices[2] = Mesh.Indices()[TriangleIndex * 3 + 2];
        CurTriangle._Index = TriangleIndex;
        for(UINT LocalEdgeIndex = 0; LocalEdgeIndex < 3; LocalEdgeIndex++)
        {
            Vertex *SearchV[2];

            CurTriangle._HalfEdges[LocalEdgeIndex] = &_HalfEdges[TriangleIndex * 3 + LocalEdgeIndex];
            CurTriangle._Vertices[LocalEdgeIndex] = &_Vertices[LocalIndices[LocalEdgeIndex]];
            _HalfEdges[TriangleIndex * 3 + LocalEdgeIndex]._NextEdge = &_HalfEdges[TriangleIndex * 3 + (LocalEdgeIndex + 1) % 3];

            SearchV[0] = &_Vertices[LocalIndices[(LocalEdgeIndex + 1) % 3]];
            SearchV[1] = &_Vertices[LocalIndices[(LocalEdgeIndex + 2) % 3]];
            if(SearchV[0]->Index() > SearchV[1]->Index())
            {
                Utility::Swap(SearchV[0], SearchV[1]);
            }
            FullEdge &Target = FindFullEdge(SearchV);
            if(Target != FullEdge::NotFound)
            {
                PersistentAssert(Target.GetTriangle(1) == Triangle::Boundary, "Duplicate edge; 2-manifold criterion violated.");
                //PersistentAssert(Target.GetTriangle(1) == Triangle::Boundary,
                //                 String("Duplicate edge; 2-manifold criterion violated: ") + String(SearchV[0]->Index()) + String(", ") + String(SearchV[1]->Index()));

                _HalfEdges[TriangleIndex * 3 + LocalEdgeIndex]._AcrossEdge = &Target;
                Target._Triangles[1] = &CurTriangle;
            }
            else
            {
                FullEdge *NewEdge = new FullEdge;
                Assert(NewEdge != NULL, "Out of memory");
                NewEdge->_Index = _FullEdges.Length();
                NewEdge->_Triangles[0] = &CurTriangle;
                NewEdge->_Triangles[1] = &Triangle::Boundary;
                NewEdge->_Vertices[0] = SearchV[0];
                NewEdge->_Vertices[1] = SearchV[1];
                _HalfEdges[TriangleIndex * 3 + LocalEdgeIndex]._AcrossEdge = NewEdge;

                _FullEdges.PushEnd(NewEdge);
                HashEdge(*NewEdge);
            }
        }
    }

    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = _Triangles[TriangleIndex];
        for(UINT AdjacentTriangleIndex = 0; AdjacentTriangleIndex < 3; AdjacentTriangleIndex++)
        {
            Triangle &AdjTriangle = CurTriangle.GetNeighboringTriangle(AdjacentTriangleIndex);
        }
    }

    ClearHashTable();
    
    for(UINT i = 0; i < _FullEdges.Length(); i++)
    {
        if(_FullEdges[i]->Boundary())
        {
            _FullEdges[i]->GetVertex(0).Boundary() = true;
            _FullEdges[i]->GetVertex(1).Boundary() = true;
            _FullEdges[i]->OrientMatchingBoundary();
        }
    }

    PrepareTopology();

    /*if(!Oriented())
    {
        Orient();
    }
    PersistentAssert(Oriented(), "Mesh not oriented");*/

}

void ComplexMesh::Orient()
{
    for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length(); TriangleIndex++)
    {
        Triangle &CurTriangle = _Triangles[TriangleIndex];
        for(UINT AdjacentTriangleIndex = 0; AdjacentTriangleIndex < 3; AdjacentTriangleIndex++)
        {
            Triangle &AdjTriangle = CurTriangle.GetNeighboringTriangle(AdjacentTriangleIndex);
        }
    }

    Vector<BYTE> TriangleOriented(_Triangles.Length());
    Vector<Triangle *> TriangleQueue;
    TriangleOriented.Clear(0);
    bool Done = false;
    while(!Done)
    {
        bool UnorientedTriangleFound = false;
        for(UINT TriangleIndex = 0; TriangleIndex < _Triangles.Length() && !UnorientedTriangleFound; TriangleIndex++)
        {
            if(TriangleOriented[TriangleIndex] == 0)
            {
                UnorientedTriangleFound = true;
                TriangleQueue.PushEnd(&_Triangles[TriangleIndex]);
                TriangleOriented[TriangleIndex] = 1;
            }
        }
        if(UnorientedTriangleFound)
        {
            while(TriangleQueue.Length() > 0)
            {
                Triangle &CurTriangle = *(TriangleQueue.Last());
                TriangleQueue.PopEnd();
                for(UINT AdjacentTriangleIndex = 0; AdjacentTriangleIndex < 3; AdjacentTriangleIndex++)
                {
                    Triangle &NeighborTriangle = CurTriangle.GetNeighboringTriangle(AdjacentTriangleIndex);
                    if(NeighborTriangle != Triangle::Boundary)
                    {
                        FullEdge &SharedEdge = CurTriangle.GetSharedEdge(NeighborTriangle);
                        if((CurTriangle.OrientedWith(SharedEdge) && NeighborTriangle.OrientedWith(SharedEdge)) ||
                           (!CurTriangle.OrientedWith(SharedEdge) && !NeighborTriangle.OrientedWith(SharedEdge)))
                        {
                            if(TriangleOriented[NeighborTriangle.Index()] == 1)
                            {
                                SignalError("Mesh not orientable");
                            }
                            Utility::Swap(NeighborTriangle._Vertices[0], NeighborTriangle._Vertices[1]);
                            //Utility::Swap(NeighborTriangle._HalfEdges[0], NeighborTriangle._HalfEdges[1]);

                            TriangleOriented[NeighborTriangle.Index()] = 1;
                            TriangleQueue.PushEnd(&NeighborTriangle);
                        }
                    }
                }
            }
        }
        else
        {
            Done = true;
        }
    }
}

void ComplexMesh::PrepareTopology()
{
    for(UINT i = 0; i < _Vertices.Length(); i++)
    {
        _Vertices[i].Triangles().FreeMemory();
    }
    for(UINT i = 0; i < _Triangles.Length(); i++)
    {
        Triangle &CurTriangle = _Triangles[i];
        for(UINT i2 = 0; i2 < 3; i2++)
        {
            CurTriangle.GetVertex(i2).Triangles().PushEnd(&CurTriangle);
        }
    }
    for(UINT i = 0; i < _Vertices.Length(); i++)
    {
        _Vertices[i].LoadVertices();
    }
}

void ComplexMesh::Dump(BaseMesh &Mesh) const
{
    Mesh.Allocate(_Vertices.Length(),_Triangles.Length());
    for(UINT i=0;i<_Vertices.Length();i++)
    {
        Mesh.Vertices()[i].Pos = _Vertices[i].Pos();
        Mesh.Vertices()[i].TexCoord.x = _Vertices[i].TexCoords().x;
        Mesh.Vertices()[i].TexCoord.y = _Vertices[i].TexCoords().y;
    }
    for(UINT i=0;i<_Triangles.Length();i++)
    {
        Mesh.Indices()[i * 3 + 0] = _Triangles[i].GetVertex(0).Index();
        Mesh.Indices()[i * 3 + 1] = _Triangles[i].GetVertex(1).Index();
        Mesh.Indices()[i * 3 + 2] = _Triangles[i].GetVertex(2).Index();
    }
    Mesh.GenerateNormals();
}

void ComplexMesh::Subdivision()
{
    Mesh M;
    Subdivision(M);
    Load(M);
}

void ComplexMesh::Subdivision(BaseMesh &Mesh)
{
    UINT VertexCount = _Vertices.Length();
    UINT EdgeCount = _FullEdges.Length();
    UINT TriangleCount = _Triangles.Length();
    //IntPair P;

    Mesh.Allocate(VertexCount + EdgeCount, TriangleCount * 4);

    MeshVertex *V = Mesh.Vertices();
    DWORD *I = Mesh.Indices();

    Vector<Vec3f> NewVertexPositions(_Vertices.Length());
    for(UINT VertexIndex = 0; VertexIndex < VertexCount; VertexIndex++)
    {
        V[VertexIndex].Pos = _Vertices[VertexIndex].ComputeLoopSubdivisionPos();
    }

    for(UINT EdgeIndex = 0; EdgeIndex < EdgeCount; EdgeIndex++)
    {
        V[VertexCount + EdgeIndex].Pos = _FullEdges[EdgeIndex]->ComputeLoopSubdivisionPos();
    }

    for(UINT i = 0; i < TriangleCount; i++)
    {
        UINT SourceI[6];
        Triangle &CurTriangle = _Triangles[i];

        for(UINT i2 = 0; i2 < 3; i2++)
        {
            SourceI[i2 + 0] = CurTriangle.GetVertex(i2).Index();
            SourceI[i2 + 3] = VertexCount + CurTriangle.GetOtherEdge(_Triangles[i].GetVertex(i2)).Index();
        }

        I[i * 12 + 0] = SourceI[0];
        I[i * 12 + 1] = SourceI[5];
        I[i * 12 + 2] = SourceI[4];

        I[i * 12 + 3] = SourceI[5];
        I[i * 12 + 4] = SourceI[1];
        I[i * 12 + 5] = SourceI[3];

        I[i * 12 + 6] = SourceI[4];
        I[i * 12 + 7] = SourceI[3];
        I[i * 12 + 8] = SourceI[2];

        I[i * 12 + 9] = SourceI[4];
        I[i * 12 + 10] = SourceI[5];
        I[i * 12 + 11] = SourceI[3];
    }
}

void Subdivide(BaseMesh &M1, BaseMesh &M2)
{
    M2.SetGD(M1.GetGD());
    ComplexMesh EM;
    EM.Load(M1);
    EM.Subdivision(M2);
}

void Subdivide(BaseMesh &M1, BaseMesh &M2, UINT Iterations)
{
    Mesh MTemp = M1;
    for(UINT i = 0; i < Iterations; i++)
    {
        Subdivide(MTemp, M2);
        MTemp = M2;
    }
}
