/*
BaseMeshFiles.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, the source is further grouped into multiple files.
*/

void BaseMesh::SaveASCII(const String &Filename) const
{
    ofstream file(Filename.CString());

    int i, vc = VertexCount(), ic = IndexCount();
    const MeshVertex *V = Vertices();
    const DWORD *I = Indices();

    file << vc << ' ' << ic/3 << endl;

    int r,g,b,a;
    for(i=0;i<vc;i++)
    {
        r = V[i].Color.r;
        g = V[i].Color.g;
        b = V[i].Color.b;
        a = V[i].Color.a;
        file << V[i].Pos.TabSeparatedString() << " " << V[i].Normal.TabSeparatedString() << " " << r << ' ' << g << ' ' << b << ' ' << a << " " <<  V[i].TexCoord.x << ' ' << V[i].TexCoord.y << endl;
    }

    for(i=0;i<ic;i+=3)
        file << I[i+0] << ' ' << I[i+1] << ' ' << I[i+2] << endl;
}

void BaseMesh::LoadASCII(const String &Filename)
{
    ifstream file(Filename.CString());
    int vc, ic, fc;

    Assert(!file.fail(), "BaseMesh::Load file failed");
    file >> vc >> fc;
    
    Assert(!file.fail(), "BaseMesh::Load file failed");
    Allocate(vc, fc);
    
    int i, r, g, b, a;
    vc=VertexCount();
    ic=IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    for(i=0;i<vc;i++)
    {
        file >> V[i].Pos.x >> V[i].Pos.y >> V[i].Pos.z;
        file >> V[i].Normal.x >> V[i].Normal.y >> V[i].Normal.z;
        file >> r >> g >> b >> a;
        file >> V[i].TexCoord.x >> V[i].TexCoord.y;

        V[i].Color.r = r;
        V[i].Color.g = g;
        V[i].Color.b = b;
        V[i].Color.a = a;
    }
    for(i=0;i<ic;i+=3)
    {
        file >> I[i] >> I[i+1] >> I[i+2];
    }
}

void BaseMesh::SavePly(const String &Filename)
{
    ofstream File(Filename.CString());
    PersistentAssert(!File.fail(), "Failed to open file");

    UINT vc = VertexCount(), ic = IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    File << "ply" << endl;
    File << "format ascii 1.0" << endl;
    File << "element vertex " << vc << endl;
    File << "property float x" << endl;
    File << "property float y" << endl;
    File << "property float z" << endl;
    File << "element face " << ic / 3 << endl;
    File << "property list uchar int vertex_indices" << endl;
    File << "end_header" << endl;
    for(UINT i = 0; i < vc; i++)
    {
        File << V[i].Pos.TabSeparatedString() << endl;
    }
    for(UINT i = 0; i < ic; i += 3)
    {
        File << "3 " << I[i + 0] << ' ' << I[i + 1] << ' ' << I[i + 2] << endl;
    }
}

void BaseMesh::SavePBRT(const String &Filename, const Vector<Vec3f> &LocalCoordinateFrame)
{
    ofstream File(Filename.CString());
    File << "Shape \"trianglemesh\" ";
    File <<    "\"point P\" [ ";
    for(UINT VertexIndex = 0; VertexIndex < VertexCount(); VertexIndex++)
    {
        File << Vertices()[VertexIndex].Pos.TabSeparatedString() << endl;
    }
    /*File << "] \"float uv\" [ ";
    for(UINT VertexIndex = 0; VertexIndex < VertexCount(); VertexIndex++)
    {
        Vec2f TexCoord = Vertices()[VertexIndex].TexCoord;
        Vec2f NewTexCoord(TexCoord.x, TexCoord.y);
        File << NewTexCoord.TabSeparatedString() << endl;
    }
    File << "] \"normal N\" [ ";
    for(UINT VertexIndex = 0; VertexIndex < VertexCount(); VertexIndex++)
    {
        File << Vertices()[VertexIndex].Normal.TabSeparatedString() << endl;
    }
    if(LocalCoordinateFrame.Length() > 0)
    {
        File <<    "] \"vector S\" [ ";
        for(UINT VertexIndex = 0; VertexIndex < VertexCount(); VertexIndex++)
        {
            File << LocalCoordinateFrame[VertexIndex].TabSeparatedString() << endl;
        }
    }*/
    File << "] \"integer indices\" [ ";
    for(UINT TriangleIndex = 0; TriangleIndex < FaceCount(); TriangleIndex++)
    {
        File << Indices()[TriangleIndex * 3 + 1] << ' ';
        File << Indices()[TriangleIndex * 3 + 0] << ' ';
        File << Indices()[TriangleIndex * 3 + 2] << endl;
    }
    File << "]" << endl;
}

void BaseMesh::SaveObj(const String &Filename) const
{
    ofstream file(Filename.CString());

    UINT vc = VertexCount(), ic = IndexCount();
    const MeshVertex *V = Vertices();
    const DWORD *I = Indices();

    file << "# OBJ file format with ext .obj" << endl;
    file << "# vertex count = " << vc << endl;
    file << "# face count = " << ic/3 << endl;

    for(UINT i = 0; i < vc; i++)
    {
        file << "v " << V[i].Pos.TabSeparatedString() << endl;
    }
    for(UINT i = 0; i < ic; i+=3)
    {
        file << "f " << I[i+0]+1 << ' ' << I[i+1]+1 << ' ' << I[i+2]+1 << endl;
    }
}

void BaseMesh::LoadObj(const String &Filename, bool IgnoreSlashes)
{
    PersistentAssert(Utility::FileExists(Filename), String("File not found: ") + Filename);
    ifstream file(Filename.CString());

    float x, y, z;
    TriMeshFace I;

    char CurLine[256];
    Vector<TriMeshFace> NewIndexArray;
    Vector<MeshVertex> NewVertexArray;

    MeshVertex CurMeshVertex = MeshVertex(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    while(!file.eof())
    {
        file.getline(CurLine,999);
        if(strlen(CurLine) > 3)
        {
            if(CurLine[0] == 'v')
            {
                if(CurLine[1] == ' ' || CurLine[1] == '\t')
                {
                    CurLine[0] = ' ';
                    sscanf(CurLine, "%e%e%e", &x, &y, &z);
                    CurMeshVertex.Pos = Vec3f(x, y, z);
                    NewVertexArray.PushEnd(CurMeshVertex);
                }
            }
            if(CurLine[0] == 't')
            {
                CurLine[0] = ' ';
                sscanf(CurLine, "%e%e", &x, &y);
                NewVertexArray.Last().TexCoord.x = x;
                NewVertexArray.Last().TexCoord.y = y;
            }
            if(CurLine[0] == 'f')
            {
                CurLine[0] = ' ';
                CurLine[1] = ' ';
                if(IgnoreSlashes)
                {
                    sscanf(CurLine,"%d%d%d",&I.I[0], &I.I[1], &I.I[2]);
                    I.I[0]--; I.I[1]--; I.I[2]--;
                    NewIndexArray.PushEnd(I);
                }
                else
                {
                    String Line = CurLine;
                    Vector<String> Words;
                    Line.Partition(' ', Words);
                    if(Words.Length() == 3)
                    {
                        I.I[0] = Words[0].ConvertToInteger() - 1;
                        I.I[1] = Words[1].ConvertToInteger() - 1;
                        I.I[2] = Words[2].ConvertToInteger() - 1;
                        NewIndexArray.PushEnd(I);
                    }
                    else if(Words.Length() == 4)
                    {
                        I.I[0] = Words[0].ConvertToInteger() - 1;
                        I.I[1] = Words[1].ConvertToInteger() - 1;
                        I.I[2] = Words[2].ConvertToInteger() - 1;
                        NewIndexArray.PushEnd(I);

                        I.I[1] = I.I[2];
                        I.I[2] = Words[3].ConvertToInteger() - 1;
                        NewIndexArray.PushEnd(I);
                    }
                }
            }
        }
    }

    Allocate(NewVertexArray.Length(), NewIndexArray.Length());

    UINT VC = VertexCount();
    for(UINT i = 0; i < VC; i++)
    {
        Vertices()[i] = NewVertexArray[i];
    }
    NewVertexArray.FreeMemory();

    UINT FC = FaceCount();
    for(UINT i = 0; i < FC; i++)
    {
        Indices()[i*3+0] = NewIndexArray[i].I[0];
        Indices()[i*3+1] = NewIndexArray[i].I[1];
        Indices()[i*3+2] = NewIndexArray[i].I[2];
    }
    NewIndexArray.FreeMemory();

    GenerateNormals();
}

void BaseMesh::LoadGridPly(const String &Filename)
{
    PersistentAssert(Utility::FileExists(Filename), "File not found");
    ifstream File(Filename.CString());
    
    Vector<Vec3f> NewVertices;
    Grid<UINT> IndexGrid;

    bool InsideHeader = true;
    UINT RowCount = 0, ColCount = 0, VertexCount = 0;
    UINT VerticesRead = 0, CurGridRow = 0, CurGridCol = 0;

    while(!File.eof())
    {
        char CurLineCString[256];
        File.getline(CurLineCString, 256);
        String CurLine = CurLineCString;
        if(CurLine.Length() > 0)
        {
            Vector<String> Partition;
            CurLine.Partition(' ', Partition);
            if(InsideHeader)
            {
                if(Partition[0] == "obj_info")
                {
                    if(Partition[1] == "num_cols")
                    {
                        ColCount = Partition[2].ConvertToUnsignedInteger();
                    }
                    if(Partition[1] == "num_rows")
                    {
                        RowCount = Partition[2].ConvertToUnsignedInteger();
                    }
                }
                if(Partition[0] == "element")
                {
                    if(Partition[1] == "vertex")
                    {
                        VertexCount = Partition[2].ConvertToUnsignedInteger();
                    }
                }
                if(Partition[0] == "end_header")
                {
                    InsideHeader = false;
                    PersistentAssert(RowCount != 0 && ColCount != 0 && VertexCount != 0, "Incomplete header");
                    NewVertices.ReSize(VertexCount);
                    IndexGrid.Allocate(RowCount, ColCount);
                }
            }
            else
            {
                if(VerticesRead < VertexCount)
                {
                    NewVertices[VerticesRead++] = (Vec3f(Partition[0].ConvertToFloat(), Partition[1].ConvertToFloat(), Partition[2].ConvertToFloat()));
                }
                else
                {
                    UINT Index = VertexCount;
                    if(Partition.Length() == 2)
                    {
                        Index = Partition[1].ConvertToUnsignedInteger();
                    }
                    IndexGrid(CurGridRow, CurGridCol++) = Index;
                    if(CurGridCol == ColCount)
                    {
                        CurGridCol = 0;
                        CurGridRow++;
                    }
                }
            }
        }
    }

    float SmallestEdgeLength = 1e10f;
    for(UINT Row = 0; Row < IndexGrid.Rows() - 1; Row++)
    {
        for(UINT Col = 0; Col < IndexGrid.Cols() - 1; Col++)
        {
            UINT I[4];
            UINT FaceCanidateCount = 0;
            TriMeshFace FaceCanidates[2];
            I[0] = IndexGrid(Row + 0, Col + 0);
            I[1] = IndexGrid(Row + 1, Col + 0);
            I[2] = IndexGrid(Row + 1, Col + 1);
            I[3] = IndexGrid(Row + 0, Col + 1);
            UINT VerticesInSquare = 0;
            for(UINT Index = 0; Index < 4; Index++)
            {
                if(I[Index] != VertexCount)
                {
                    VerticesInSquare++;
                }
            }
            if(VerticesInSquare == 4)
            {
                FaceCanidateCount = 2;
                FaceCanidates[0] = TriMeshFace(I[0], I[1], I[2]);
                FaceCanidates[1] = TriMeshFace(I[0], I[2], I[3]);
            }
            for(UINT FaceCanidateIndex = 0; FaceCanidateIndex < FaceCanidateCount; FaceCanidateIndex++)
            {
                TriMeshFace &CurCanidate = FaceCanidates[FaceCanidateIndex];
                for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
                {
                    float CurLength = (NewVertices[UINT(CurCanidate.I[(EdgeIndex + 1) % 3])] - NewVertices[UINT(CurCanidate.I[EdgeIndex])]).Length();
                    SmallestEdgeLength = Math::Min(SmallestEdgeLength, CurLength);
                }
            }
        }
    }

    Vector<TriMeshFace> NewFaces;
    for(UINT Row = 0; Row < IndexGrid.Rows() - 1; Row++)
    {
        for(UINT Col = 0; Col < IndexGrid.Cols() - 1; Col++)
        {
            UINT I[4];
            UINT FaceCanidateCount = 0;
            TriMeshFace FaceCanidates[2];
            I[0] = IndexGrid(Row + 0, Col + 0);
            I[1] = IndexGrid(Row + 1, Col + 0);
            I[2] = IndexGrid(Row + 1, Col + 1);
            I[3] = IndexGrid(Row + 0, Col + 1);
            UINT VerticesInSquare = 0;
            for(UINT Index = 0; Index < 4; Index++)
            {
                if(I[Index] != VertexCount)
                {
                    VerticesInSquare++;
                }
            }
            if(VerticesInSquare == 4)
            {
                FaceCanidateCount = 2;
                FaceCanidates[0] = TriMeshFace(I[0], I[1], I[2]);
                FaceCanidates[1] = TriMeshFace(I[0], I[2], I[3]);
            }
            if(VerticesInSquare == 3)
            {
                FaceCanidateCount = 1;
                UINT LocalIndex = 0;
                for(UINT SquareVertexIndex = 0; SquareVertexIndex < 4; SquareVertexIndex++)
                {
                    if(I[SquareVertexIndex] != VertexCount)
                    {
                        FaceCanidates[0].I[LocalIndex++] = I[SquareVertexIndex];
                    }
                }
            }
            for(UINT FaceCanidateIndex = 0; FaceCanidateIndex < FaceCanidateCount; FaceCanidateIndex++)
            {
                TriMeshFace &CurCanidate = FaceCanidates[FaceCanidateIndex];
                float MinLength, MaxLength;
                for(UINT EdgeIndex = 0; EdgeIndex < 3; EdgeIndex++)
                {
                    float CurLength = (NewVertices[UINT(CurCanidate.I[(EdgeIndex + 1) % 3])] - NewVertices[UINT(CurCanidate.I[EdgeIndex])]).Length();
                    if(EdgeIndex == 0)
                    {
                        MinLength = CurLength;
                        MaxLength = CurLength;
                    }
                    else
                    {
                        MinLength = Math::Min(MinLength, CurLength);
                        MaxLength = Math::Max(MaxLength, CurLength);
                    }
                }
                //if(MaxLength / MinLength < 6.0f)
                //if(MaxLength / SmallestEdgeLength < 10.0f)
                {
                    NewFaces.PushEnd(CurCanidate);
                }
            }
        }
    }

    Allocate(NewVertices.Length(), NewFaces.Length());

    for(UINT VertexIndex = 0; VertexIndex < VertexCount; VertexIndex++)
    {
        Vertices()[VertexIndex] = MeshVertex(NewVertices[VertexIndex]);
    }

    for(UINT FaceIndex = 0; FaceIndex < NewFaces.Length(); FaceIndex++)
    {
        for(UINT LocalIndex = 0; LocalIndex < 3; LocalIndex++)
        {
            Indices()[FaceIndex * 3 + LocalIndex] = NewFaces[FaceIndex].I[LocalIndex];
        }
    }

    GenerateNormals();
}

void BaseMesh::LoadPly(const String &Filename)
{
    PersistentAssert(Utility::FileExists(Filename), "File not found");
    ifstream File(Filename.CString());
    
    Vector<TriMeshFace> NewFaceArray;
    Vector<Vec3f> NewVertexArray;

    bool HeaderDone = false;
    while(!File.eof())
    {
        char CurLineCString[256];
        File.getline(CurLineCString, 256);
        String CurLine = CurLineCString;
        if(!HeaderDone)
        {
            if(CurLine.StartsWith(String("end_header")))
            {
                HeaderDone = true;
            }
        }
        else
        {
            if(CurLine.Length() > 3)
            {
                Vector<String> Partition;
                CurLine.Partition(' ', Partition);
                if(Partition.Length() == 3)
                {
                    Vec3f CurPosition;
                    for(UINT ElementIndex = 0; ElementIndex < 3; ElementIndex++)
                    {
                        CurPosition[ElementIndex] = Partition[ElementIndex].ConvertToFloat();
                    }
                    NewVertexArray.PushEnd(CurPosition);
                }
                else if(Partition.Length() == 4)
                {
                    TriMeshFace CurFace;
                    for(UINT FaceVertexIndex = 0; FaceVertexIndex < 3; FaceVertexIndex++)
                    {
                        CurFace.I[FaceVertexIndex] = Partition[FaceVertexIndex + 1].ConvertToInteger();
                    }
                    NewFaceArray.PushEnd(CurFace);
                }
            }
        }
    }

    Allocate(NewVertexArray.Length(), NewFaceArray.Length());

    UINT VC = VertexCount();
    for(UINT VertexIndex = 0; VertexIndex < VC; VertexIndex++)
    {
        Vertices()[VertexIndex] = MeshVertex(NewVertexArray[VertexIndex]);
    }

    UINT FC = FaceCount();
    for(UINT FaceIndex = 0; FaceIndex < FC; FaceIndex++)
    {
        Indices()[FaceIndex * 3 + 0] = NewFaceArray[FaceIndex].I[0];
        Indices()[FaceIndex * 3 + 1] = NewFaceArray[FaceIndex].I[1];
        Indices()[FaceIndex * 3 + 2] = NewFaceArray[FaceIndex].I[2];
    }

    GenerateNormals();
}

void BaseMesh::SaveBinary(const String &filename) const
{
    FILE *file = Utility::CheckedFOpen(filename.CString(), "wb");
    
    UINT vc=VertexCount(), ic=IndexCount();
    const MeshVertex *V = Vertices();
    const DWORD *I = Indices();

    Utility::CheckedFWrite(&vc, sizeof(UINT), 1, file);
    Utility::CheckedFWrite(&ic, sizeof(UINT), 1, file);
    Utility::CheckedFWrite(V, sizeof(MeshVertex), vc, file);
    Utility::CheckedFWrite(I, sizeof(DWORD), ic, file);
    fclose(file);
}

void BaseMesh::LoadBinary(const String &filename)
{
    FILE *file = Utility::CheckedFOpen(filename.CString(), "rb");

    UINT vc, ic;
    Utility::CheckedFRead(&vc, sizeof(UINT), 1, file);
    Utility::CheckedFRead(&ic, sizeof(UINT), 1, file);

    Allocate(vc, ic / 3);
    
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    Utility::CheckedFRead(V, sizeof(MeshVertex), vc, file);
    Utility::CheckedFRead(I, sizeof(DWORD), ic, file);
    fclose(file);
}

void BaseMesh::SaveCompressed(const String &filename) const
{
    UINT vc=VertexCount(),ic=IndexCount();
    const MeshVertex *V = Vertices();
    const DWORD *I = Indices();

    OutputDataStream stream;
    stream << vc;
    stream << ic;
    stream.WriteData((BYTE *)V, sizeof(MeshVertex) * vc);
    stream.WriteData((BYTE *)I, sizeof(DWORD) * ic);
    
    Compression::CompressStreamToFile(stream.Data(), filename);
}

void BaseMesh::LoadCompressed(const String &filename)
{
    Vector<BYTE> decompressedStream;
    Compression::DecompressStreamFromFile(filename, decompressedStream);

    InputDataStream stream;
    stream.WrapMemory(decompressedStream);

    UINT vc, ic;
    stream >> vc;
    stream >> ic;
    
    Allocate(vc, ic / 3);
    
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    stream.ReadData((BYTE *)V, sizeof(MeshVertex) * vc);
    stream.ReadData((BYTE *)I, sizeof(DWORD) * ic);
}

void BaseMesh::SaveStream(OutputDataStream &stream) const
{
    UINT vertexCount = VertexCount();
    UINT indexCount = IndexCount();
    const MeshVertex *vertices = Vertices();
    const DWORD *indices = Indices();

    stream << vertexCount << indexCount;
    stream.WriteData((BYTE *)vertices, sizeof(MeshVertex) * vertexCount);
    stream.WriteData((BYTE *)indices, sizeof(DWORD) * indexCount);
}

void BaseMesh::LoadStream(InputDataStream &stream)
{
    UINT vertexCount, indexCount;
    stream >> vertexCount >> indexCount;
    
    Allocate(vertexCount, indexCount / 3);
    
    MeshVertex *vertices = Vertices();
    DWORD *indices = Indices();
    stream.ReadData((BYTE *)vertices, sizeof(MeshVertex) * vertexCount);
    stream.ReadData((BYTE *)indices, sizeof(DWORD) * indexCount);
}
