/*
D3D9Mesh.cpp
Written by Matthew Fisher

D3D9Mesh is a DirectX instance of the BaseMesh class.
In general all these functions just call DirectX equivalents.
Most of the functionality is gained through the BaseMesh functions.
*/

#ifdef USE_D3D9

//our vertices have a color, normal, position, and two texture coordinates.  This is reflected in D3DMeshFVF
const DWORD D3DMeshFVF = D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_XYZ | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEX1;

//our meshes have 32-bit indices (D3DXMESH_32BIT) and we want DirectX to handle moving them in and out of memory (D3DXMESH_MANAGED)
const DWORD D3DMeshOptions = D3DXMESH_32BIT | D3DXMESH_MANAGED;

//basic memory management...

D3D9Mesh::D3D9Mesh()
{
    _Mesh = NULL;
    _GD = NULL;
    _Vertices = NULL;
    _Indices = NULL;
}

D3D9Mesh::D3D9Mesh(GraphicsDevice &_GD)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    SetGD(_GD);
}

D3D9Mesh::D3D9Mesh(const BaseMesh &O)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    O.CopyMesh(*this);
}

D3D9Mesh::D3D9Mesh(const D3D9Mesh &O)
{
    _Mesh = NULL;
    _Vertices = NULL;
    _Indices = NULL;
    O.CopyMesh(*this);
}

D3D9Mesh::~D3D9Mesh()
{
    FreeMemory();
}

void D3D9Mesh::FreeMemory()
{
    Unlock();
    if(_Mesh)
    {
        _Mesh->Release();
        _Mesh = 0;
    }
}


void D3D9Mesh::Allocate(UINT VertexCount, UINT FaceCount)
{
    FreeMemory();
    if(VertexCount == 0 || FaceCount == 0)
    {
        return;
    }

    D3DXCreateMeshFVF(FaceCount, VertexCount, D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);    //tell DirectX to allocate space for the _Mesh
    Lock();        //toggle the buffer locking just to clear things up
    Unlock();    //we want the buffers unlocked whenever possible
}

D3D9Mesh& D3D9Mesh::operator = (const BaseMesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

D3D9Mesh& D3D9Mesh::operator = (const D3D9Mesh &o)
{
    o.CopyMesh(*this);
    return *this;
}

void D3D9Mesh::CopyMesh(BaseMesh &Copy) const
{
    Copy.SetGD(GetGD());

    int VC = VertexCount();
    int IC = IndexCount();

    if(VC > 0 && IC > 0)
    {
        if(_Vertices == NULL)
        {
            _Mesh->LockVertexBuffer(0,(void**) &_Vertices);
        }
        if(_Indices == NULL)
        {
            _Mesh->LockIndexBuffer(0,(void**) &_Indices);
        }

        Copy.Allocate(VC, IC / 3);                                //allocate space in Copy
        memcpy(Copy.Vertices(), _Vertices, VC * sizeof(MeshVertex));    //insert our vertices into Copy
        memcpy(Copy.Indices(), _Indices, IC * sizeof(DWORD));            //insert our indices into Copy

        Unlock();
    }
}

LPD3DXMESH D3D9Mesh::GetMesh() const
{
    return _Mesh;
}

LPDIRECT3DDEVICE9 D3D9Mesh::GetD3DDevice()
{
    Assert(GetGD().Type() == GD_D3D9, "D3DDevice requested on a non-D3D9 graphics device.");
    return ((D3D9GraphicsDevice *)&(GetGD()))->GetDevice();
}

UINT D3D9Mesh::VertexCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetNumVertices();
    }
}

UINT D3D9Mesh::FaceCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetNumFaces();
    }
}

UINT D3D9Mesh::IndexCount() const
{
    if(_Mesh == NULL)
    {
        return 0;
    }
    else
    {
        return _Mesh->GetNumFaces() * 3;
    }
}

void D3D9Mesh::Lock() const
{
    LockVB();
    LockIB();
}

void D3D9Mesh::LockVB() const
{
    if(_Mesh != NULL && _Vertices == NULL)
    {
        _Mesh->LockVertexBuffer(0, (void**) &_Vertices);
    }
}

void D3D9Mesh::LockIB() const
{
    if(_Mesh != NULL && _Indices == NULL)
    {
        _Mesh->LockIndexBuffer(0,(void**) &_Indices);
    }
}

void D3D9Mesh::Unlock() const
{
    if(_Vertices != NULL)
    {
        _Mesh->UnlockVertexBuffer();
        _Vertices = NULL;
    }
    if(_Indices != NULL)
    {
        _Mesh->UnlockIndexBuffer();
        _Indices = NULL;
    }
}

MeshVertex* D3D9Mesh::Vertices()
{
    if(_Vertices == NULL)
    {
        LockVB();
    }
    return _Vertices;
}

DWORD* D3D9Mesh::Indices()
{
    if(_Indices == NULL)
    {
        LockIB();
    }
    return _Indices;
}

const MeshVertex* D3D9Mesh::Vertices() const
{
    if(_Vertices == NULL)
    {
        LockVB();
    }
    return _Vertices;
}

const DWORD* D3D9Mesh::Indices() const
{
    if(_Indices == NULL)
    {
        LockIB();
    }
    return _Indices;
}

void D3D9Mesh::LoadFromXFile(const String &Filename)
{
    String FilenameCopy = Filename;
    FreeMemory();
    LPD3DXBUFFER Adjacency, Materials, EffectInstances;
    DWORD MaterialCount;
    LPD3DXMESH LoadedMesh;

    //call the DirectX function to load from an XFile,
    D3DXLoadMeshFromX(FilenameCopy.CString(), D3DMeshOptions, GetD3DDevice(), &Adjacency, &Materials, &EffectInstances, &MaterialCount, &LoadedMesh);

    //get rid of the components we don't care about
    Adjacency->Release(); Materials->Release(); EffectInstances->Release();

    //and copy the part we do care about (the _Mesh) into our _Mesh in the right format.
    LoadedMesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);
    LoadedMesh->Release();
}

void D3D9Mesh::SaveToXFile(const String &Filename)
{
    String FilenameCopy = Filename;
    D3DXMATERIAL M;
    ZeroMemory(&M, sizeof(D3DXMATERIAL));

    //call the DirectX function to save to an XFile,
    D3DXSaveMeshToX(FilenameCopy.CString(), _Mesh, NULL, &M, NULL, 0, D3DXF_FILESAVE_TOFILE);
}

void D3D9Mesh::LoadMesh(LPD3DXMESH _mesh)
{
    FreeMemory();
    _mesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);
}

void D3D9Mesh::Render(int Subset) const
{
    Unlock();
    if(_Mesh)
    {
        _Mesh->DrawSubset(Subset);
    }
}

void D3D9Mesh::Render() const
{
    Render(0);
}


void D3D9Mesh::CreateTeapot(float radius)
{
    //just call the DirectX function to create the teapot
    FreeMemory();
    LPD3DXMESH teapot;
    D3DXCreateTeapot(GetD3DDevice(), &teapot, NULL);
    teapot->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);
    teapot->Release();
    Stretch(radius);
    SetColor(RGBColor::White);
    GenerateNormals();
}

void D3D9Mesh::CreateText(const char *string, char *FontName, int FontHeight,
                float deviation, float depth, bool bold, bool italic)
{
    //just call the DirectX function to create the text
    FreeMemory();
    LPD3DXMESH TextMesh;
    
    HDC hdc = CreateCompatibleDC( NULL );
    HFONT hFont;
    HFONT hFontOld;
    
    INT nHeight = -MulDiv( FontHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72 );
    hFont = CreateFont(nHeight, 0, 0, 0, bold ? FW_BOLD : FW_NORMAL, italic, FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, FontName);
    hFontOld = (HFONT)SelectObject(hdc, hFont); 

    if(FAILED(D3DXCreateText(GetD3DDevice(), hdc, string, deviation, depth, &TextMesh, NULL, NULL))) _asm int 3;

    SelectObject(hdc, hFontOld);
    DeleteObject( hFont );
    DeleteDC( hdc );

    TextMesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);
    TextMesh->Release();
    SetColor(RGBColor::White);
    GenerateNormals();
}

void D3D9Mesh::NPatchEnhance(float segs, bool quadratic)
{
    DWORD *adj;
    Unlock();

    //get the _Mesh adjacency (needed by NPatchEnhance)
    GenerateAdj(adj);
    LPD3DXMESH sphere;

    //do the n-patching using the DirectX function
    D3DXTessellateNPatches(_Mesh, adj, segs, quadratic, &sphere, NULL);
    FreeMemory();

    //load the data into 
    sphere->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh);
    sphere->Release();
    delete[] adj;
}

/*void D3D9Mesh::GenerateNormals()
{
    DWORD *Adj;
    GenerateAdj(Adj);
    D3DAlwaysValidate(D3DXComputeNormals(_Mesh, Adj));
    delete[] Adj;
}*/

void D3D9Mesh::GenerateAdj(DWORD *& Adj)
{
    Adj = new DWORD[IndexCount()];
    PersistentAssert(Adj != NULL, "GenerateAdj failed");
    D3DAlwaysValidate(_Mesh->GenerateAdjacency(0.0f, Adj), "GenerateAdjacency");
}

void D3D9Mesh::GenerateAdj(Vector<DWORD> &Adjacency)
{
    Adjacency.Allocate(IndexCount());
    D3DAlwaysValidate(_Mesh->GenerateAdjacency(0.0f, Adjacency.CArray()), "GenerateAdjacency");
}

bool D3D9Mesh::QueryInside(const Vec3f &Pos, const Vec3f &Dir)
{
    D3DXVECTOR3 D3DPos = Pos;
    D3DXVECTOR3 D3DDir = Dir;
    BOOL Hit;
    DWORD FaceIndex, HitCount;
    FLOAT U, _Vertices, Dist;
    //LPD3DXBUFFER AllHits = NULL;

    D3DXIntersect(_Mesh, &D3DPos, &D3DDir, &Hit, &FaceIndex, &U, &_Vertices, &Dist, NULL, &HitCount);
    //AllHits->Release();

    return (HitCount % 2 == 1);
}

void D3D9Mesh::QueryHits(const Vec3f &Pos, const Vec3f &Dir, Vector<float> &Hits, DWORD &FirstHitFaceIndex, float &u, float &v) const
{
    D3DXVECTOR3 D3DPos = Pos;
    D3DXVECTOR3 D3DDir = Dir;
    BOOL Hit;
    DWORD HitCount;
    FLOAT Dist;
    LPD3DXBUFFER AllHits = NULL;

    D3DXIntersect(_Mesh, &D3DPos, &D3DDir, &Hit, &FirstHitFaceIndex, &u, &v, &Dist, &AllHits, &HitCount);

    Hits.Allocate(HitCount);
    if(HitCount)
    {
        LPD3DXINTERSECTINFO HitInfo = (LPD3DXINTERSECTINFO)AllHits->GetBufferPointer();
        for(UINT HitIndex = 0; HitIndex < HitCount; HitIndex++)
        {
            Hits[HitIndex] = HitInfo[HitIndex].Dist;
        }
        Hits.Sort();
    }

    if(AllHits != NULL)
    {
        AllHits->Release();
    }
}

void D3D9Mesh::SimplifyToFaces(UINT Count)
{
    Lock();
    Unlock();

    DWORD *Adj;
    Clean(1e-6f, Adj);

    LPD3DXMESH NewMesh = NULL;
    D3DAlwaysValidate(D3DXSimplifyMesh(_Mesh, Adj, NULL, NULL, Count, D3DXMESHSIMP_FACE, &NewMesh), "D3DXSimplifyMesh");
    Assert(NewMesh != NULL, "D3DXSimplifyMesh failed.");
    _Mesh->Release();
    D3DAlwaysValidate(NewMesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh), "CloneMeshFVF");
    NewMesh->Release();
    delete[] Adj;

    Lock();
    Unlock();
}

void D3D9Mesh::SimplifyToPercentFaces(float NewPercent)
{
    SimplifyToFaces(UINT(FaceCount() * NewPercent));
}

void D3D9Mesh::SimplifyToVertices(UINT Count)
{
    Lock();
    Unlock();

    DWORD *Adj;
    Clean(1e-6f, Adj);

    LPD3DXMESH NewMesh = NULL;
    D3DAlwaysValidate(D3DXSimplifyMesh(_Mesh, Adj, NULL, NULL, Count, D3DXMESHSIMP_VERTEX, &NewMesh), "D3DXSimplifyMesh");
    _Mesh->Release();
    D3DAlwaysValidate(NewMesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh), "CloneMeshFVF");
    NewMesh->Release();
    delete[] Adj;

    Lock();
    Unlock();
}

void D3D9Mesh::SimplifyToPercentVertices(float NewPercent)
{
    SimplifyToVertices(UINT(VertexCount() * NewPercent));
}

void D3D9Mesh::Optimize()
{
    if(_Mesh != NULL)
    {
        DWORD *AdjData = new DWORD[3 * _Mesh->GetNumFaces()];
        _Mesh->GenerateAdjacency(0.0f, AdjData);
        _Mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, AdjData, NULL, NULL, NULL);
        delete[] AdjData;
    }
}

void D3D9Mesh::Clean(float Epsilon, DWORD* &AdjDataOut)
{
    Assert(_Mesh != NULL, "Clean called on empty _Mesh.");

    LPD3DXMESH NewMesh;
    DWORD *AdjData = new DWORD[3 * _Mesh->GetNumFaces()];
    AdjDataOut = new DWORD[3 * _Mesh->GetNumFaces()];
    DWORD *FaceRemap = new DWORD[3 * _Mesh->GetNumFaces()];

    /*D3DXWELDEPSILONS Eps;
    Eps.Position = Epsilon;
    Eps.BlendWeights = 1.0f;
    Eps.Normal = 1.0f;
    Eps.PSize = 1.0f;
    Eps.Specular = 1.0f;
    Eps.Diffuse = 1.0f;
    Eps.Tangent = 1.0f;
    Eps.Binormal = 1.0f;
    Eps.TessFactor = 1.0f;
    for(UINT _Indices = 0; _Indices < 8; _Indices++)
    {
        Eps.Texcoord[_Indices] = 1.0f;
    }*/

    CleanVerticesAndTriangles();
    Unlock();
    //D3DAlwaysValidate(_Mesh->GenerateAdjacency(Epsilon, AdjDataOut));
    //D3DAlwaysValidate(D3DXWeldVertices(_Mesh, D3DXWELDEPSILONS_WELDPARTIALMATCHES, &Eps, AdjDataOut, AdjData, FaceRemap, NULL));
    //D3DAlwaysValidate(D3DXWeldVertices(_Mesh, D3DXWELDEPSILONS_WELDALL | D3DXWELDEPSILONS_WELDPARTIALMATCHES, NULL, AdjDataOut, AdjData, FaceRemap, NULL));
    //CleanTriangles();
    D3DAlwaysValidate(_Mesh->GenerateAdjacency(Epsilon, AdjData), "GenerateAdjacency");
    D3DAlwaysValidate(D3DXCleanMesh(D3DXCLEAN_SIMPLIFICATION, _Mesh, AdjData, &NewMesh, AdjDataOut, NULL), "D3DXCleanMesh");
    _Mesh->Release();
    D3DAlwaysValidate(NewMesh->CloneMeshFVF(D3DMeshOptions, D3DMeshFVF, GetD3DDevice(), &_Mesh), "CloneMeshFVF");
    NewMesh->Release();

    Lock();
    Unlock();

    delete[] AdjData;
    delete[] FaceRemap;
}

#endif