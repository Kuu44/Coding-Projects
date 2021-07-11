/*
BaseMeshVertexModifiers.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.

BaseMeshVertexModifiers.cpp contains all the vertex coloring, texturing, and transformation functions.
*/

Vec3f BaseMesh::EvaluateBarycentricPos(UINT FaceIndex, float u, float v) const
{
    const MeshVertex *V = Vertices();
    const DWORD *I = Indices();
    Vec3f V0 = V[I[FaceIndex * 3 + 0]].Pos;
    Vec3f V1 = V[I[FaceIndex * 3 + 1]].Pos;
    Vec3f V2 = V[I[FaceIndex * 3 + 2]].Pos;
    return V0 + u * (V1 - V0) + v * (V2 - V0);
}

void BaseMesh::SetColor(RGBColor Color)
{
    MeshVertex *V = Vertices();
    UINT vc = VertexCount();

    //
    // rgba to bgra
    //
    Color = Color.FlipBlueAndRed();

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Color = Color;
    }
}

void BaseMesh::SetAlpha(BYTE Alpha)
{
    MeshVertex *V = Vertices();
    UINT vc = VertexCount();

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Color.a = Alpha;
    }
}

void BaseMesh::RandomizeColors()
{
    int i,vc=VertexCount();
    MeshVertex *V = Vertices();
    for(i=0;i<vc;i++)
    {
        V[i].Color = RGBColor::RandomColor();
    }
}

void BaseMesh::GCNormals()
{
    GenerateNormals();
    ColorNormals();
}

void BaseMesh::GenerateNormals()
{
    UINT vc = VertexCount(), ic = IndexCount();
    MeshVertex *V = Vertices();
    DWORD *I = Indices();

    Vec3f V1, V2, Normal;

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Normal = Vec3f::Origin;    //zero each normal
    }

    for(UINT i = 0; i < ic; i += 3)            //for every triangle
    {
        V1 = V[I[i+2]].Pos - V[I[i+0]].Pos;
        V2 = V[I[i+1]].Pos - V[I[i+0]].Pos;
        Normal = Vec3f::Cross(V1, V2);            //compute the triangle normal
        V[I[i+0]].Normal += Normal;
        V[I[i+1]].Normal += Normal;
        V[I[i+2]].Normal += Normal;            //each adjacent vertex adds the triangle normal to its summed normal
    }

    NormalizeNormals();
}

void BaseMesh::NormalizeNormals()
{
    UINT vc = VertexCount();
    MeshVertex *V = Vertices();

    for(UINT i = 0; i < vc; i++)
    {
        if(V[i].Normal.LengthSq() != 0.0f)
        {
            V[i].Normal = Vec3f::Normalize(V[i].Normal);
        }
    }
}

void BaseMesh::ColorNormals()
{
    ColorNormals(1.0f, 1.0f, 1.0f);
}

void BaseMesh::ColorNormals(float fr, float fg, float fb)
{
    int i,vc=VertexCount();
    MeshVertex *V = Vertices();

    for(i=0;i<vc;i++)
    {
        Vec3f Normal = V[i].Normal;
        int r = int((Normal.x/2.0f+0.5f)*255*fr);
        int g = int((Normal.y/2.0f+0.5f)*255*fg);
        int b = int((Normal.z/2.0f+0.5f)*255*fb);    //remap each normal's (x, y, z) to (r, g, b)
        V[i].Color = RGBColor(r,g,b);
    }
}

void BaseMesh::ColorNormals(RGBColor Color)
{
    ColorNormals(Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f);
}

void BaseMesh::ColorNormalsGrayScale(RGBColor Color)
{
    int i,vc = VertexCount();
    MeshVertex *V = Vertices();

    for(i=0;i<vc;i++)
    {
        Vec3f normal = V[i].Normal;
        int r = Utility::Bound(int(Math::Abs(normal.x/2.0f+0.5f)*255), 0, 255);
        int g = Utility::Bound(int(Math::Abs(normal.y/2.0f+0.5f)*255), 0, 255);
        int b = Utility::Bound(int(Math::Abs(normal.z/2.0f+0.5f)*255), 0, 255);    //remap each normal's (x, y, z) to (r, g, b)

        const bool UseMaximumValue = false;
        if(UseMaximumValue)
        {
            if(g > r) r = g;
            if(b > r) r = b;
        }
        else
        {
            r = (r + g + b) / 3;        //merge the 3 values into one value via some method
        }
        V[i].Color = RGBColor(r / 255.0f * Vec3f(Color));
    }
}

void BaseMesh::SetRadius(float Size)
{
    Stretch(Size / Radius());
}

void BaseMesh::Stretch(float ScaleFactor)
{
    Stretch(Vec3f(ScaleFactor, ScaleFactor, ScaleFactor));
}

void BaseMesh::Stretch(const Vec3f &v)
{
    UINT vc = VertexCount();
    MeshVertex *V = Vertices();

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Pos.x *= v.x;
        V[i].Pos.y *= v.y;
        V[i].Pos.z *= v.z;
    }
}

void BaseMesh::Translate(const Vec3f &v)
{
    UINT vc = VertexCount();
    MeshVertex *V = Vertices();

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Pos += v;
    }
}

void BaseMesh::ApplyMatrix(const Matrix4 &M)
{
    UINT vc = VertexCount();
    MeshVertex *V = Vertices();

    for(UINT i = 0; i < vc; i++)
    {
        V[i].Pos = M.TransformPoint(V[i].Pos);
        V[i].Normal = M.TransformNormal(V[i].Normal);
    }
}

void BaseMesh::TextureMapToNormals(int variable)
{
    int i,vc = VertexCount();
    MeshVertex *V = Vertices();

    //remap the normals into texture coordinates
    //there are three normal components (x, y, z) and only two texture coordinates (x, y),
    //so variable tells us which normal component not to map.

    for(i=0;i<vc;i++)
    {
        if(variable == 0)
        {
            V[i].TexCoord.x = (V[i].Normal.y + 1.0f) / 2.0f;
            V[i].TexCoord.y = (V[i].Normal.z + 1.0f) / 2.0f;
        } else if(variable == 1) {
            V[i].TexCoord.x = (V[i].Normal.x + 1.0f) / 2.0f;
            V[i].TexCoord.y = (V[i].Normal.z + 1.0f) / 2.0f;
        } else {
            V[i].TexCoord.x = (V[i].Normal.x + 1.0f) / 2.0f;
            V[i].TexCoord.y = (V[i].Normal.y + 1.0f) / 2.0f;
        }
    }
}

void BaseMesh::TextureSphericalMap(int variable)
{
    int i;

    //spherical coordinates have two angles.  This function computes
    //these angles for each vertex and maps these angles into tx and ty.
    //variable exists for the same reason as TextureMapToNormals
    
    int vc = VertexCount();
    MeshVertex *V = Vertices();

    Vec3f Pos;

    for(i=0;i<vc;i++)
    {
        if(variable == 0)
            Pos = Vec3f(V[i].Pos.x,V[i].Pos.y,V[i].Pos.z);

        if(variable == 1)
            Pos = Vec3f(V[i].Pos.x,V[i].Pos.z,V[i].Pos.y);

        V[i].TexCoord.x = (atan2f(Pos.y,Pos.x) + Math::PIf) / (2.0f * Math::PIf);
        V[i].TexCoord.y = 1.0f - (atan2f(Pos.z,sqrtf(Pos.y * Pos.y + Pos.x * Pos.x)) + Math::PIf / 2.0f) / Math::PIf;
    }
}