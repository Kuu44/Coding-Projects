/*
BaseMeshShapes.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshShapes.cpp contains all the shape generation functions.
*/

#define XXX .525731112119133606f
#define ZZZ .850650808352039932f    //constants for icosahedron data

float IcosahedronVData[12][3] = {    
   {-XXX, 0.0, ZZZ}, {XXX, 0.0, ZZZ}, {-XXX, 0.0, -ZZZ}, {XXX, 0.0, -ZZZ},    
   {0.0, ZZZ, XXX}, {0.0, ZZZ, -XXX}, {0.0, -ZZZ, XXX}, {0.0, -ZZZ, -XXX},    
   {ZZZ, XXX, 0.0}, {-ZZZ, XXX, 0.0}, {ZZZ, -XXX, 0.0}, {-ZZZ, -XXX, 0.0} 
};

int IcosahedronIData[20][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };    //the icosahedron vertices/indices

void BaseMesh::CreateSphere(float radius, int refinement)
{
    //allocate space for the icosahedron
    Allocate(12, 20);

    MeshVertex Temp(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    int i,vc=VertexCount(),ic=IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    for(i=0;i<12;i++)
    {
        Temp.Pos = Vec3f(IcosahedronVData[i][0],IcosahedronVData[i][1],IcosahedronVData[i][2]);
        V[i] = Temp;                        //load the icosahedron vertices
    }
    for(i=0;i<20;i++)
    {
        I[i*3+0] = IcosahedronIData[i][1];
        I[i*3+1] = IcosahedronIData[i][0];
        I[i*3+2] = IcosahedronIData[i][2];    //load the icosahedron indices
    }

    for(i=0;i<refinement;i++)
        TwoPatch();                //refine the specified number of times

    vc=VertexCount();
    V = Vertices();

    for(i=0;i<vc;i++)
    {
        V[i].Pos = Vec3f::Normalize(V[i].Pos);
        V[i].Pos *= radius;        //project all the points to lie on a sphere of the specified radius
    }

    GenerateNormals();            //generate normals
    SetColor(RGBColor::White);
}

void BaseMesh::CreateSphere(float radius, int slices, int stacks)
{
    Allocate(slices * (stacks - 1) + 2,slices * 2 * (stacks - 1));    //allocate space for the angular splits

    float PI_Stacks = Math::PIf / float(stacks);
    float PI2_Slices = 2.0f * Math::PIf / float(slices);

    float Theta, Phi,CosP,SinP;
    int i,i2,vc=0,ic=0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(i=1;i < stacks;i++)
    {
        Phi = float(i) * PI_Stacks;
        CosP = cosf(Phi);
        SinP = sinf(Phi);

        for(i2=0;i2 < slices;i2++)
        {
            Theta = float(i2) * PI2_Slices;
            MVtx.Pos = Vec3f(radius * cosf(Theta) * SinP, radius * sinf(Theta) * SinP, radius * CosP);    //create the new vertex
            V[vc++] = MVtx;    //add the vertex to the mesh
        }
    }

    //add the top and bottom vertices to the mesh
    int TopVertex = vc,BottomVertex = vc+1;
    MVtx.Pos = Vec3f(0.0f,0.0f,radius);
    V[vc++] = MVtx;
    MVtx.Pos = Vec3f(0.0f,0.0f,-radius);
    V[vc++] = MVtx;

    //add the top and bottom triangles (all triangles involving the TopVertex and BottomVertex)
    int ip1,i2p1;
    for(i=0;i < slices;i++)
    {
        ip1 = i + 1;
        if(ip1 == slices) ip1 = 0;

        I[ic++] = i;
        I[ic++] = TopVertex;                    //top triangle
        I[ic++] = ip1;
        
        I[ic++] = ip1 + (stacks - 2) * slices;
        I[ic++] = BottomVertex;                    //bottom triangle
        I[ic++] = i + (stacks - 2) * slices;
    }

    //add all the remaining triangles
    for(i=0;i < stacks - 2;i++)
    {
        for(i2=0;i2 < slices;i2++)
        {
            i2p1 = i2 + 1;
            if(i2p1 == slices) i2p1 = 0;
            
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = i * slices + i2;
            I[ic++] = i * slices + i2p1;

            
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = i * slices + i2p1;
            I[ic++] = (i+1) * slices + i2p1;
        }
    }

    GenerateNormals();
}

float CubeVData[8][3] = {    
   {1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, 
   {1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}};

  int CubeIData[12][3] = { 
   {1,2,3}, {1,3,0}, {0,3,7}, {0,7,4}, {3,2,6},    
   {3,6,7}, {1,6,2}, {1,5,6}, {0,5,1}, {0,4,5},    
   {6,5,4}, {6,4,7}};        //simple definition of a cube

void BaseMesh::CreateBox(float w, float h, float d, int refinement)
{
    Allocate(8, 12);

    MeshVertex Temp(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    int i,vc=VertexCount(),ic=IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    for(i=0;i<8;i++)
    {
        Temp.Pos = Vec3f(CubeVData[i][0],CubeVData[i][1],CubeVData[i][2]);
        V[i] = Temp;        ///load the vertices
    }
    for(i=0;i<12;i++)
    {
        I[i*3+0] = CubeIData[i][0];
        I[i*3+1] = CubeIData[i][1];
        I[i*3+2] = CubeIData[i][2];    //load the triangles
    }

    for(i=0;i<refinement;i++)
    {
        TwoPatch();                //refine the requested number of times
    }

    Stretch(Vec3f(0.5f*w, 0.5f*h, 0.5f*d));    //stretch to the requested dimensions
    GenerateNormals();
}

void BaseMesh::CreateTriangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, RGBColor color)
{
    Allocate(3, 1);
    
    Vec3f normal = Math::TriangleNormal(v0, v1, v2);
    MeshVertex *V = Vertices();
    V[0] = MeshVertex(v0, normal, color, Vec2f(0.0f, 0.0f));
    V[1] = MeshVertex(v1, normal, color, Vec2f(1.0f, 0.0f));
    V[2] = MeshVertex(v2, normal, color, Vec2f(0.0f, 1.0f));

    DWORD *I = Indices();
    I[0] = 0;
    I[1] = 1;
    I[2] = 2;
}

void BaseMesh::CreateBox(const Rectangle3f &Rect)
{
    Vec3f Dimensions = Rect.Dimensions();
    CreateBox(Dimensions.x, Dimensions.y, Dimensions.z, 0);
    Translate(Rect.Center());
}

void BaseMesh::CreateTeapot(float radius)
{
    LoadBinary("C:\\Data\\Teapot.obj");        //load the teapot from a standard file.  Will do nothing if the file doesn't exist.
    Stretch(radius);                        //stretch to the requested size
}

void BaseMesh::CreateCylinder(float radius, float height, UINT slices, UINT stacks)
{
    //this code is almost identical to CreateSphere(radius, slices, stacks) except there is no TopVertex/Bottom vertex,
    //and there is only one angle (and instead there is a height.)
    Allocate(slices * (stacks + 1), 2 * stacks * slices);
    
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    float Theta;

    int vc=0, ic=0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i = 0; i <= stacks; i++)
    {
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Theta = float(i2) * PI2_Slices;
            MVtx.Pos = Vec3f(radius * cosf(Theta), radius * sinf(Theta), height * float(i) / float(stacks));
            MVtx.TexCoord.x = i / float(stacks);
            MVtx.TexCoord.y = i2 / float(slices - 1);
            V[vc++] = MVtx;
        }
    }

    for(UINT i=0;i < stacks;i++)
    {
        for(UINT i2=0;i2 < slices;i2++)
        {
            int i2p1 = i2 + 1;
            if(i2p1 == slices) i2p1 = 0;
            
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = i * slices + i2;
            I[ic++] = i * slices + i2p1;

            
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = i * slices + i2p1;
            I[ic++] = (i+1) * slices + i2p1;
        }
    }

    GenerateNormals();
}

void BaseMesh::CreateLantern(float radius, float height, UINT slices, UINT stacks)
{
    //this code is almost identical to CreateCylinder(radius, height slices, stacks) except it flips all non-border
    //edges; this is a much worse triangulation of the surface and does not behave well numerically (which was the
    //goal for the project I was working on at the time.)
    //it also has a cap on the top/bottom.

    Allocate(slices * (stacks + 1),2 * stacks * slices + 2*(slices-2));
    
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    float Theta;

    int vc=0, ic=0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i = 0; i <= stacks; i++)
    {
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Theta = float(i2+0.5f*i) * PI2_Slices;
            MVtx.Pos = Vec3f(radius * cosf(Theta), radius * sinf(Theta), height * (float(i) / stacks - 0.5f));
            V[vc++] = MVtx;
        }
    }

    for(UINT i = 0; i < FaceCount(); i++)
    {
        I[i*3+0] = 0;
        I[i*3+1] = 1;
        I[i*3+2] = 2;
    }

    int i2m1;
    for(UINT i = 0; i < stacks - 1; i++)
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            i2m1 = int(i2) - 1;
            if(i2m1 == -1) i2m1 = slices-1;
            
            I[ic++] = i * slices + i2;
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = (i+2) * slices + i2m1;
            
            I[ic++] = i * slices + i2;
            I[ic++] = (i+2) * slices + i2m1;
            I[ic++] = (i+1) * slices + i2m1;
        }

    UINT i = 0;
    for(UINT i2 = 0; i2 < slices; i2++)
    {
        i2m1 = i2 - 1;
        if(i2m1 == -1) i2m1 = slices-1;

        I[ic++] = i * slices + i2m1;
        I[ic++] = i * slices + i2;
        I[ic++] = (i+1) * slices + i2m1;
    }

    i = stacks - 1;
    for(UINT i2 = 0; i2 < slices; i2++)
    {
        i2m1 = i2 - 1;
        if(i2m1 == -1)
        {
            i2m1 = slices - 1;
        }

        I[ic++] = (i + 1) * slices + i2m1;
        I[ic++] = i * slices + i2;
        I[ic++] = (i + 1) * slices + i2;
    }

    i = 0;
    for(UINT i2 = 1; i2 < slices - 1; i2++)
    {
        I[ic++] = i * slices + 0;
        I[ic++] = i * slices + i2 + 1;
        I[ic++] = i * slices + i2;
    }

    i = stacks;
    for(UINT i2 = 1; i2 < slices - 1; i2++)
    {
        I[ic++] = i * slices + 0;
        I[ic++] = i * slices + i2;
        I[ic++] = i * slices + i2 + 1;
    }

    GenerateNormals();
}

void BaseMesh::CreateClosedCylinder(float radius, float height, UINT slices, UINT stacks)
{
    //this code is almost identical to CreateCylinder(radius, height slices, stacks) except it 
    //adds on a cap (like CreateLantern.)
    Allocate(slices * (stacks + 1),2 * stacks * slices + 2*(slices-2));
    
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    float Theta;

    int vc=0,ic=0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i=0;i <= stacks;i++)
    {
        for(UINT i2=0;i2 < slices;i2++)
        {
            Theta = float(i2+0.5f*i) * PI2_Slices;
            MVtx.Pos = Vec3f(radius * cosf(Theta), radius * sinf(Theta), height * (float(i) / stacks - 0.5f));
            V[vc++] = MVtx;
        }
    }

    for(UINT i=0;i < FaceCount();i++)
    {
        I[i*3+0] = 0;
        I[i*3+1] = 1;
        I[i*3+2] = 2;
    }

    for(UINT i=0;i < stacks-1;i++)
        for(UINT i2=0;i2 < slices;i2++)
        {
            UINT i2m1 = i2 - 1;
            if(i2m1 == -1) i2m1 = slices-1;
            
            I[ic++] = i * slices + i2;
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = (i+1) * slices + i2m1;
            
            I[ic++] = (i+1) * slices + i2m1;
            I[ic++] = (i+1) * slices + i2;
            I[ic++] = (i+2) * slices + i2m1;
        }

    UINT i = 0;
    for(UINT i2=0;i2 < slices;i2++)
    {
        UINT i2m1 = i2 - 1;
        if(i2m1 == -1)
        {
            i2m1 = slices-1;
        }

        I[ic++] = i * slices + i2m1;
        I[ic++] = i * slices + i2;
        I[ic++] = (i+1) * slices + i2m1;
    }

    i = stacks - 1;
    for(UINT i2 = 0; i2 < slices; i2++)
    {
        UINT i2m1 = i2 - 1;
        if(i2m1 == -1)
        {
            i2m1 = slices-1;
        }

        I[ic++] = (i+1) * slices + i2m1;
        I[ic++] = i * slices + i2;
        I[ic++] = (i+1) * slices + i2;
    }

    i = 0;
    for(UINT i2 = 1; i2 < slices - 1; i2++)
    {
        I[ic++] = i * slices + 0;
        I[ic++] = i * slices + i2+1;
        I[ic++] = i * slices + i2;
    }

    i = stacks;
    for(UINT i2 = 1; i2 < slices - 1; i2++)
    {
        I[ic++] = i * slices + 0;
        I[ic++] = i * slices + i2;
        I[ic++] = i * slices + i2+1;
    }

    GenerateNormals();
}

void BaseMesh::CreateCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks)
{
    float height = (pt2 - pt1).Length();
    CreateCylinder(radius, height, slices, stacks);    //create a basic cylinder of the appropriate height

    Matrix4 Face = Matrix4::Face(Vec3f::eZ, pt2 - pt1);                    //make it face the direction pt2 - pt1 instead of eZ
    Matrix4 T2 = Matrix4::Translation(pt1);                                //translate it so it goes from pt1 -> pt2

    ApplyMatrix(Face * T2);
    GenerateNormals();
}

void BaseMesh::CreateClosedCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks)
{
    float height = (pt2 - pt1).Length();
    CreateClosedCylinder(radius, height, slices, stacks);    //create a basic cylinder of the appropriate height

    Matrix4 T1 = Matrix4::Translation(Vec3f(0.0f,0.0f,height / 2.0f));    //translate so it goes from Origin to eZ*height
    Matrix4 Face = Matrix4::Face(Vec3f::eZ, pt2 - pt1);                        //make it face the direction pt2 - pt1 instead of eZ
    Matrix4 T2 = Matrix4::Translation(pt1);                            //translate it so it goes from pt1 -> pt2 as requested

    ApplyMatrix(T1 * Face * T2);    //apply the constructed Matrix4
    GenerateNormals();
}

void BaseMesh::ReCreateCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks)
{
    //a merge of the CreateCylinder(radius, height, slices, stacks) and CreateCylinder(radius, pt1, pt2, slices, stacks)
    Vec3f Diff = pt2 - pt1;
    float height = Diff.Length();
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    float Theta;

    int vc = 0, ic = 0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i = 0; i <= stacks; i++)
    {
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Theta = float(i2) * PI2_Slices;
            MVtx.Pos = Vec3f(radius * cosf(Theta), radius * sinf(Theta), height * (float(i) / stacks - 0.5f));
            V[vc++] = MVtx;
        }
    }

    Matrix4 T1 = Matrix4::Translation(Vec3f(0.0f,0.0f,height / 2.0f));
    Matrix4 Face = Matrix4::Face(Vec3f(0.0f,0.0f,1.0f),pt2 - pt1);
    Matrix4 T2 = Matrix4::Translation(pt1);

    ApplyMatrix(T1 * Face * T2);
    GenerateNormals();
}

void BaseMesh::CreateCylinder(Vec3f (*PositionFunction) (float), float Start, float End, float radius, UINT slices, UINT stacks)
{
    //this function allocates space for ReCreateCylinder then just rerouts to ReCreateCylinder.
    CreateCylinder(radius, 0.0f, slices, stacks);
    ReCreateCylinder(PositionFunction, Start, End, radius, slices, stacks);
}

void BaseMesh::ReCreateCylinder(Vec3f (*PositionFunction) (float), float Start, float End, float radius, UINT slices, UINT stacks)
{
    MeshVertex *V = Vertices();

    Matrix4 Face, Translate;
    Vec3f Tangent;
    float DeltaT = 0.0001f,Time,Theta;
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    Vec3f CurPos;

    for(UINT i = 0; i <= stacks; i++)
    {
        Time = float(Math::LinearMap(0.0f,float(stacks),Start,End,float(i)));        //get the approriate value between Start and End
        CurPos = PositionFunction(Time);        //get the current position along the curve
        
        if(Time + DeltaT <= End) Tangent = PositionFunction(Time + DeltaT) - CurPos;    //approximate the derivative (tangent vector)
        else Tangent = CurPos - PositionFunction(Time - DeltaT);
        Face = Matrix4::Face(Vec3f(0.0f, 0.0f, 1.0f), Tangent);    //face Matrix4 causes the local cylinder ring to face the right direction
        Translate = Matrix4::Translation(CurPos);                //the local cylinder ring should be centered on CurPos
        Face = Face * Translate;

        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Theta = float(i2) * PI2_Slices;
            V[i*slices+i2].Pos = Vec3f(radius * cosf(Theta), radius * sinf(Theta), 0.0f);    //construct the basic circle
            V[i*slices+i2].Pos = Face.TransformPoint(V[i*slices+i2].Pos);                //transform the circle to its approrpriate using the Matrix4
        }
    }

    GenerateNormals();
}

void BaseMesh::CreateLozenge(float Radius, const Vec3f &Start, const Vec3f &End, UINT slices, UINT stacks)
{
    //allocate space for the lozenge and call ReCreateLozenge
    CreateCylinder(1.0f, 1.0f, slices, stacks);
    ReCreateLozenge(Radius, Start, End, slices, stacks);
}

void BaseMesh::ReCreateLozenge(float Radius, const Vec3f &Start, const Vec3f &End, UINT slices, UINT stacks)
{
    //this is just like CreateCylinder(radius, pt1, pt2, slices, stacks) except the radius function isn't fixed;
    //towards the ends it rounds off into a sphere.
    MeshVertex *V = Vertices();
    
    float Theta,CurZ,SqrtValue;
    float PI2_Slices = 2.0f * Math::PIf / float(slices), Height, LocalRadius;
    Vec3f Diff = End - Start;
    Height = Diff.Length();

    for(UINT i=0; i <= stacks; i++)
    {
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Theta = float(i2) * PI2_Slices;
            CurZ = float(Math::LinearMap(0.0f, float(stacks), -Radius, Height+Radius, float(i)));

            if(CurZ < 0.0f)        //if we need to round the cylinder,
            {
                LocalRadius = float(Math::LinearMap(-Radius, 0.0f, 1.0f, 0.0f, CurZ));
                SqrtValue = 1.0f - LocalRadius*LocalRadius;
                if(SqrtValue < 0.0f) SqrtValue = 0.0f;
                LocalRadius = sqrtf(SqrtValue) * Radius;    //compute the appropriate radius
            }
            else if(CurZ > Height)    //if we're on the other end of the cylinder and need to round,
            {
                LocalRadius = float(Math::LinearMap(Height, Height+Radius, 0.0f, 1.0f, CurZ));
                SqrtValue = 1.0f - LocalRadius*LocalRadius;
                if(SqrtValue < 0.0f) SqrtValue = 0.0f;
                LocalRadius = sqrtf(SqrtValue) * Radius;    //do the same thing
                if(LocalRadius < 0.0f || LocalRadius > Radius + 1e-5f) LocalRadius = 0.0f;
            }
            else
            {
                LocalRadius = Radius;    //otherwise we're in the middle and our radius is fixed like a cylinder
            }

            V[i*slices+i2].Pos = Vec3f(LocalRadius * cosf(Theta), LocalRadius * sinf(Theta), CurZ);    //load the appropriate position
        }
    }

    Vec3f UpVec(0.0f, 0.0f, 1.0f);

    ApplyMatrix(Matrix4::Face(UpVec, Diff) * Matrix4::Translation(Start));            //make it face the right direction and translate it to the right position
}

void BaseMesh::CreatePrettyPlane(float size, UINT slicesX, UINT slicesY)
{
    /*Allocate(slicesX * slicesY, (slicesX - 1) * (slicesY - 1) * 2);
    
    UINT vc = 0, ic = 0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx = MakeVertex(Vec3f::Origin, Vec3f::Origin, RGBColor::White, 0.0f, 0.0f);

    float ConversionX = (size / (slicesX - 1));
    float ConversionY = (size / (slicesY - 1));
    for(UINT i = 0; i < slicesX; i++)
    {
        for(UINT i2 = 0; i2 < slicesY; i2++)
        {
            //if((i % 2 == 0) && (i2 > 0))
            if(i % 2 == 0)
            {
                MVtx.Pos.x = ConversionX * float(i) - size / 2.0f;
                MVtx.Pos.y = ConversionY * (i2 - 0.5f) - size / 2.0f;
            }
            else
            {
                MVtx.Pos.x = ConversionX * float(i) - size / 2.0f;
                MVtx.Pos.y = ConversionY * float(i2) - size / 2.0f;
            }
            MVtx.TexCoord.x = i / float(slicesX - 1);
            MVtx.TexCoord.y = i2 / float(slicesY - 1);
            V[vc++] = MVtx;
        }
    }

    for(UINT i = 0; i < slicesY - 1; i++)
    {
        for(UINT i2 = 0; i2 < slicesX - 1; i2++)
        {
            if(i2 % 2 == 0 && i % 2 == 0)
            {
                I[ic++] = slicesY * i2 + i;
                I[ic++] = slicesY * i2 + (i + 1);
                I[ic++] = slicesY * (i2 + 1) + (i + 1);

                I[ic++] = slicesY * i2 + i;
                I[ic++] = slicesY * (i2 + 1) + (i + 1);
                I[ic++] = slicesY * (i2 + 1) + i;
            }
            else
            {
                I[ic++] = slicesY * i2 + i;
                I[ic++] = slicesY * i2 + (i + 1);
                I[ic++] = slicesY * (i2 + 1) + i;
                I[ic++] = slicesY * i2 + (i + 1);
                I[ic++] = slicesY * (i2 + 1) + (i + 1);
                I[ic++] = slicesY * (i2 + 1) + i;
            }
        }
    }

    GenerateNormals();*/
}

void BaseMesh::CreatePlane(float size, UINT slicesX, UINT slicesY)
{
    Allocate(slicesX * slicesY, (slicesX - 1) * (slicesY - 1) * 2);
    
    UINT vc = 0, ic = 0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    float ConversionX = (size / (slicesX - 1));
    float ConversionY = (size / (slicesY - 1));
    for(UINT i = 0; i < slicesX; i++)
    {
        for(UINT i2 = 0; i2 < slicesY; i2++)
        {
            MVtx.Pos.x = ConversionX * float(i) - size / 2.0f;
            MVtx.Pos.y = ConversionY * float(i2) - size / 2.0f;
            MVtx.TexCoord.x = i / float(slicesX - 1);
            MVtx.TexCoord.y = i2 / float(slicesY - 1);
            V[vc++] = MVtx;
        }
    }

    for(UINT i = 0; i < slicesY - 1; i++)
    {
        for(UINT i2 = 0; i2 < slicesX - 1; i2++)
        {
            I[ic++] = slicesY*i2+i;
            I[ic++] = slicesY*i2+(i+1);
            I[ic++] = slicesY*(i2+1)+i;
            I[ic++] = slicesY*i2+(i+1);
            I[ic++] = slicesY*(i2+1)+(i+1);
            I[ic++] = slicesY*(i2+1)+i;
        }
    }

    GenerateNormals();
}

void BaseMesh::CreateCanonicalRenderPlane()
{
    Allocate(4, 6);
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    for(UINT i = 0; i < 4; i++)
    {
        V[i] = MVtx;
    }
    V[0].Pos = Vec3f(-1.0f, -1.0f, 0.5f);
    V[1].Pos = Vec3f( 1.0f, -1.0f, 0.5f);
    V[2].Pos = Vec3f( 1.0f, 1.0f, 0.5f);
    V[3].Pos = Vec3f(-1.0f, 1.0f, 0.5f);
    for(UINT i = 0; i < 4; i++)
    {
        V[i].TexCoord = Vec2f(V[i].Pos.x * 0.5f + 0.5f, 0.5f - V[i].Pos.y * 0.5f);
    }
    I[0] = 0; I[1] = 1; I[2] = 2;
    I[3] = 0; I[4] = 2; I[5] = 3;
}

void BaseMesh::CreatePlane(const Vec3f &Start, const Vec3f &End, UINT SlicesX, UINT SlicesY)
{
    /*Vec3f start = _start, end = _end;
    CreatePlane(1.0f, slicesX, slicesY);

    if(start.x > end.x)
    {
        Utility::Swap(start.x, end.x);
    }
    if(start.y > end.y)
    {
        Utility::Swap(start.y, end.y);
    }
    
    Matrix4 T1 = Matrix4::Translation(Vec3f(0.5f,0.5f,0.0f));
    Matrix4 Scale = Matrix4::Scaling(Vec3f((end.x-start.x),(end.y-start.y),1.0f));
    Matrix4 T2 = Matrix4::Translation(start);

    ApplyMatrix(T1 * Scale * T2);*/

    Vec3f Axis0, Axis1;

    Vec3f Diff = End - Start;
    if(Math::Abs(Diff.x) < Math::Abs(Diff.y) && Math::Abs(Diff.x) < Math::Abs(Diff.z))
    {
        Axis0 = Vec3f::eY;
        Axis1 = Vec3f::eZ;
    }
    else if(Math::Abs(Diff.y) < Math::Abs(Diff.z))
    {
        Axis0 = Vec3f::eX;
        Axis1 = Vec3f::eZ;
    }
    else
    {
        Axis0 = Vec3f::eX;
        Axis1 = Vec3f::eY;
    }

    Axis0 *= Vec3f::Dot(End - Start, Axis0);
    Axis1 *= Vec3f::Dot(End - Start, Axis1);

    Allocate(SlicesX * SlicesY, (SlicesX - 1) * (SlicesY - 1) * 2);
    
    UINT VertexCount = 0;
    MeshVertex *V = Vertices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i = 0; i < SlicesX; i++)
    {
        for(UINT i2 = 0; i2 < SlicesY; i2++)
        {
            MVtx.Pos = Start + Axis0 * float(i) / float(SlicesX - 1) + Axis1 * float(i2) / float(SlicesY - 1);
            MVtx.TexCoord.x = i / float(SlicesX - 1);
            MVtx.TexCoord.y = i2 / float(SlicesY - 1);
            V[VertexCount++] = MVtx;
        }
    }

    UINT IndexCount = 0;
    DWORD *I = Indices();
    for(UINT i = 0; i < SlicesY - 1; i++)
    {
        for(UINT i2 = 0; i2 < SlicesX - 1; i2++)
        {
            I[IndexCount++] = SlicesY*i2+i;
            I[IndexCount++] = SlicesY*i2+(i+1);
            I[IndexCount++] = SlicesY*(i2+1)+i;
            I[IndexCount++] = SlicesY*i2+(i+1);
            I[IndexCount++] = SlicesY*(i2+1)+(i+1);
            I[IndexCount++] = SlicesY*(i2+1)+i;
        }
    }

    GenerateNormals();
}

void BaseMesh::CreatePlane(const Plane &p, float length, UINT slices)
{
    CreatePlane(p, length, slices, p.Normal()*-p.d);
}

void BaseMesh::CreatePlane(const Plane &P, float Length, UINT Slices, const Vec3f &Center)
{
    CreatePlane(Length, Slices, Slices);
    ApplyMatrix(Matrix4::Face(Vec3f(0.0f, 0.0f, 1.0f), P.Normal()) * Matrix4::Translation(Center));
}

void BaseMesh::CreateViewPlane(float EyeDist, UINT slices, MatrixController &MC)
{
    Matrix4 Perspective = MC.Perspective, PInverse;

    PInverse = Perspective.Inverse();

    Vec3f PerspectiveCoord(0.0f, 0.0f, EyeDist);
    PerspectiveCoord = Perspective.TransformPoint(PerspectiveCoord);    //get the top-left coord in persp. space

    PerspectiveCoord.x = 1.0f;
    PerspectiveCoord.y = -1.0f;
    PerspectiveCoord = PInverse.TransformPoint(PerspectiveCoord);        //get the bottom-right coord in persp. space

    CreatePlane(2.0f, slices, slices);    //create the X-Y plane

    Matrix4 Scale = Matrix4::Scaling(Vec3f(PerspectiveCoord.x, PerspectiveCoord.y, 1.0f));    //scale it appropriately,
    Matrix4 Translate = Matrix4::Translation(Vec3f(0.0f,0.0f,PerspectiveCoord.z));            //translate it away from the eye,

    Matrix4 VInverse = MC.View.Inverse();    //we need to transform our mesh and we want to fact the view and world transforms in
    Matrix4 WInverse = MC.World.Inverse();

    //
    // Translate and scale, then go into object space by multiplying through the inverse of view/world.
    //
    ApplyMatrix(Translate * Scale * VInverse * WInverse);
}

void BaseMesh::CreateTorus(float MainRadius, float SmallRadius, UINT slices, UINT stacks)
{
    //much like all the others shape functions...create a torus by taking a cylinder and wrapping
    //it around a point in space, then connect the two ends.

    Allocate(slices * stacks,2 * stacks * slices);

    float PI2_Stacks = 2.0f * Math::PIf / float(stacks);
    float PI2_Slices = 2.0f * Math::PIf / float(slices);
    float Theta,SinT,CosT,Phi,SinP;

    UINT vc = 0, ic = 0;
    MeshVertex *V = Vertices();
    DWORD *I = Indices();
    MeshVertex MVtx(Vec3f::Origin, Vec3f::Origin, RGBColor::White, Vec2f::Origin);

    for(UINT i = 0; i < stacks; i++)
    {
        Theta = float(i) * PI2_Stacks;
        SinT = sinf(Theta);
        CosT = cosf(Theta);
        Vec3f MainTranslation(CosT*MainRadius,SinT*MainRadius,0.0f);
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            Phi = float(i2) * PI2_Slices;
            SinP = sinf(Phi);
            MVtx.Pos = Vec3f(SmallRadius * CosT * SinP, SmallRadius * SinT * SinP, SmallRadius * cosf(Phi)) + MainTranslation;
            V[vc++] = MVtx;
        }
    }

    UINT i2p1,ip1;
    for(UINT i = 0; i < stacks; i++)
    {
        ip1 = i + 1;
        if(ip1 == stacks)
        {
            ip1 = 0;
        }
        for(UINT i2 = 0; i2 < slices; i2++)
        {
            i2p1 = i2 + 1;
            if(i2p1 == slices) i2p1 = 0;
            
            I[ic++] = ip1 * slices + i2;
            I[ic++] = i * slices + i2;
            I[ic++] = i * slices + i2p1;

            
            I[ic++] = ip1 * slices + i2;
            I[ic++] = i * slices + i2p1;
            I[ic++] = ip1 * slices + i2p1;
        }
    }

    GenerateNormals();
}

void BaseMesh::CreatePointCloudBoxes(const Vector<Vec3f> &Points, float Radius)
{
    Mesh BaseBox;
    BaseBox.CreateBox(1.0f, 1.0f, 1.0f, 0);
    BaseBox.SetRadius(Radius);

    MeshVertex *BaseBoxVertices = BaseBox.Vertices();
    DWORD *BaseBoxIndices = BaseBox.Indices();
    UINT BaseBoxVertexCount = BaseBox.VertexCount();
    UINT BaseBoxFaceCount = BaseBox.FaceCount();
    
    Allocate(Points.Length() * BaseBox.VertexCount(), Points.Length() * BaseBox.FaceCount());

    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    for(UINT PointIndex = 0; PointIndex < Points.Length(); PointIndex++)
    {
        const Vec3f &CurPoint = Points[PointIndex];
        UINT StartVertex = PointIndex * BaseBoxVertexCount;
        for(UINT VertexIndex = 0; VertexIndex < BaseBoxVertexCount; VertexIndex++)
        {
            MeshVertex &SourceVertex = BaseBoxVertices[VertexIndex];
            MeshVertex &DestVertex = V[VertexIndex + StartVertex];
            DestVertex = SourceVertex;
            DestVertex.Pos += CurPoint;
            DestVertex.Color = RGBColor::White;
        }
        for(UINT FaceIndex = 0; FaceIndex < BaseBoxFaceCount; FaceIndex++)
        {
            for(UINT i = 0; i < 3; i++)
            {
                I[(FaceIndex + PointIndex * BaseBoxFaceCount) * 3 + i] = BaseBoxIndices[FaceIndex * 3 + i] + StartVertex;
            }
        }
    }
}
