/*
BaseMesh.h
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.
*/

//
// a single face in the mesh
//
struct TriMeshFace
{
    TriMeshFace() {}
    TriMeshFace(DWORD I0, DWORD I1, DWORD I2)
    {
        I[0] = I0;
        I[1] = I1;
        I[2] = I2;
    }

    DWORD I[3];
};



class BaseMesh
{
public:
    BaseMesh();

    //
    // Memory
    //
    virtual void Allocate(UINT NewVertexCount, UINT NewFaceCount) = 0;
    virtual void FreeMemory() = 0;
    void CopyMesh(BaseMesh &Copy) const;
    BaseMesh& operator = (const BaseMesh &O);
    virtual void operator += (const BaseMesh &O);
    virtual void AppendVertices(const BaseMesh &O);
    virtual void LoadMeshList(const Vector<BaseMesh *> &Meshes);
    virtual void LoadMeshList(const Vector< pair<const BaseMesh *, Matrix4> > &Meshes);

    //
    // Accessors
    //
    virtual UINT IndexCount() const = 0;
    virtual UINT VertexCount() const = 0;
    virtual UINT FaceCount() const = 0;
    
    virtual MeshVertex* Vertices() = 0;
    virtual DWORD* Indices() = 0;
    virtual const MeshVertex* Vertices() const = 0;
    virtual const DWORD* Indices() const = 0;
    
    GraphicsDevice& GetGD() const;
    void SetGD(GraphicsDevice &GD);

    Vec3f EvaluateBarycentricPos(UINT FaceIndex, float u, float v) const;

    //
    // Coloring functions
    //
    void SetColor(RGBColor C);                          //sets the color of each vertex in the mesh
    void SetAlpha(BYTE Alpha);                          //sets the alpha component of the color color of each vertex in the mesh
    void RandomizeColors();                             //randomizes the color of each vertex in the mesh
    void ColorNormals();                                //colors the vertices of the mesh based upon the normal vector at that point
    void ColorNormals(float fr, float fg, float fb);    //colors the vertices of the mesh based upon the normal vector at that point,
                                                        //weighted by the given values (1.0 = full intensity, 0.0 = RGBColor::Black.)
    void ColorNormals(RGBColor Color);
    void ColorNormalsGrayScale(RGBColor Color);         //colors each vertex based upon the normals but to grayscale color
                                                        //values.  UseMaximumValue = true/false will give slightly different colorings.

    //
    // Texturing functions
    //
    void TextureSphericalMap(int variable);        //sets texture coordinates of each vertex based upon the spherical coordinates of the position of that vertex
    void TextureMapToNormals(int variable);        //sets texture coordinates of each vertex based upon the normal vector of that vertex

    //
    // Geometry functions
    //

    // Sphere
    void CreateSphere(float radius, int refinement);            //creates a icosahedron with a given radius refined to a sphere refinement times.
    void CreateSphere(float radius, int slices, int stacks);    //creates a sphere based upon a given number of angular slices/stacks in spherical coordinates.
    
    // Box
    void CreateBox(float w, float h, float d, int refinement = 0);    //creates a box with the given width, height, and depth, refined a given number of times.
    void CreateBox(const Rectangle3f &Rect);
    
    // Triangle
    void CreateTriangle(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, RGBColor color);

    // Teapot
    void CreateTeapot(float radius);                                //creates a teapot (by default loads it from a file, which must be initalized.)
    
    // Cylinder
    void CreateCylinder(float radius, float height, UINT slices, UINT stacks);        //creates a cylinder with the given paramaters
    void CreateCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks);    //creates a cylinder between two points in 3-space
    void CreateClosedCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks);    //creates a cylinder between two points in 3-space
    void ReCreateCylinder(float radius, const Vec3f &pt1, const Vec3f &pt2, UINT slices, UINT stacks);    //if CreateCylinder has already been called with the same paramaters, recreates the
                                                                                                //cylinder without reallocating memory space.
    void CreateCylinder(Vec3f (*PositionFunction) (float), float Start,        //creates a cylinder such that the center of each slice follows a given function from
                                float End, float radius, UINT slices, UINT stacks);    //Start to End.
    void ReCreateCylinder(Vec3f (*PositionFunction) (float), float Start,    //if CreateCylinder has already been called with the same paramaters, recreates the
        float End, float radius, UINT slices, UINT stacks);                            //cylinder without reallocating memory space.
    void CreateClosedCylinder(float radius, float height, UINT slices, UINT stacks);    //creates a cylinder whose ends are closed off.
    void CreateLantern(float radius, float height, UINT slices, UINT stacks);    //creates a lantern, which is just a cylinder that is poorly triangulated.

    // Planes
    void CreatePrettyPlane(float size, UINT slicesX, UINT slicesY);    //creates an X-Y plane centered at the origin with the given paramaters
    void CreateCanonicalRenderPlane();
    void CreatePlane(float size, UINT slicesX, UINT slicesY);    //creates an X-Y plane centered at the origin with the given paramaters
    void CreatePlane(const Vec3f &start, const Vec3f &end, UINT slicesX, UINT SlicesY);        //creates a plane between the given points
    void CreatePlane(const Plane &p, float length, UINT slices);    //creates a plane that represents the given plane
    void CreatePlane(const Plane &p, float length, UINT slices, const Vec3f &Center);    //creates a plane that represents the given plane
    void CreateViewPlane(float EyeDist, UINT slices, MatrixController &MC);    //creates a plane that covers the whole screen a given distance
                                                                                    //from the Matrix4 transform represented by MC

    // Torus
    void CreateTorus(float MainRadius, float SmallRadius,UINT slices, UINT stacks);    //creates a torus with the given paramaters

    // Lozenge
    void CreateLozenge(float Radius, const Vec3f &Start, const Vec3f &End, UINT slices, UINT stacks);    //creates a lozenge between the given points
    void ReCreateLozenge(float Radius, const Vec3f &Start, const Vec3f &End, UINT slices, UINT stacks);    //recreates a lozenge between the given points without reallocating memory.

    void CreatePointCloudBoxes(const Vector<Vec3f> &Points, float Radius);

    //
    // Rendering functions
    //
    virtual void Render() const = 0;                        //renders the mesh on the associated graphics device
    
    //
    // File functions
    //

    // ASCII
    void SaveASCII(const String &Filename) const;
    void LoadASCII(const String &Filename);

    void SaveStream(OutputDataStream &stream) const;
    void LoadStream(InputDataStream &stream);

    // Binary
    void SaveBinary(const String &Filename) const;
    void LoadBinary(const String &Filename);

    void SaveCompressed(const String &Filename) const;
    void LoadCompressed(const String &Filename);

    // Other
    void SaveObj(const String &Filename) const; //saves the mesh in *.obj format
    void SavePBRT(const String &Filename, const Vector<Vec3f> &LocalCoordinateFrame);
    void SavePly(const String &Filename);        //saves the mesh in *.ply format
    void LoadObj(const String &Filename, bool IgnoreSlashes = true);        //loads the mesh in *.obj format
    void LoadPly(const String &Filename);        //saves the mesh in *.ply format
    void LoadGridPly(const String &Filename);    //saves the mesh in *.ply format, Cyberware grid style
    
    //
    // Normal manipulation
    //
    virtual void GenerateNormals();        //generates the normals at each vertex based upon the average of the incident faces
    void GCNormals();              //generates and colors the normals at each vertex
    void NormalizeNormals();       //normalizes all vertex normals in the mesh

    //
    // Position manipulation
    //
    void Stretch(float Factor);            //stretches the mesh uniformly in all directions
    void Stretch(const Vec3f &V);          //stretches the mesh non-uniformly in each dimension
    void Translate(const Vec3f &V);        //translates every vertex in the mesh
    void SetRadius(float Size);            //rescales the mesh such that the maximum distance from the origin to a vertex is Size
    void ApplyMatrix(const Matrix4 &M);    //applys M to every vertex position and normal in the mesh

    //
    // Enhancement functions
    //
    void TwoPatch();                    //enhances the mesh by replacing each face with 4 faces.  Linear interpolation is used.
    void Subdivide();
    void Subdivide(UINT Iterations);

    //
    // Bounding visibility
    //
    Rectangle3f BoundingBox() const;   //calculates the bounding box for the set of all vertex in the mesh
    Rectangle3f BoundingBox(const Matrix4 &transform) const;
    float Radius();                    //computes the maximum distance from the origin to a vertex of the mesh
    float Radius(const Vec3f &Center);
    Matrix4 UnitSphereTransform();     //translates the mesh such that the center of the bounding box for the mesh is the origin
    
    //
    // Simplification
    //
#ifdef USE_POINT_SET
    virtual void WeldVertices(float epsilon);    //takes every group of vertices within epsilon of each other and replaces them with a single vertex,
                                                 //and alters incident faces to point to these new vertices.
    virtual void WeldVertices(float epsilon, Vector<UINT> &OldToNewMapping);
#endif

    void UnIndex();                     //duplicates every vertex such that each triangle points to its own set of 3 vertices, rather than
                                                //incident triangles sharing vertices.
    void CleanVerticesAndTriangles();
    void CleanVerticesAndTriangles(Vector<UINT> &OldToNewMapping);

    //
    // Splitting
    //
    void Split(Plane &p, BaseMesh &M1, BaseMesh &M2);    //given an arbitrary plane, returns in M1 the vertices and faces in this mesh that lie on one side
                                                                //of the plane, and returns the vertices/faces that lie on the other side in M2.
                                                                //triangles that lie on the boundary are grouped as if they were on the side with 2 vertices satisfying the condition.
    void Split(float (*PositionFunction) (Vec3f &), BaseMesh &M1, BaseMesh &M2);    //same as split, except the decision function is whether PositionFunction is
                                                                                        //negative or positive at the vertex position.
    void ClosedPlaneSplit(const Plane &P, BaseMesh &M1, BaseMesh &M2);
    void CullFaces(const BYTE FaceTest[]);

    //
    // Query
    //
    UINT32 Hash32() const;
    UINT64 Hash64() const;
    float SurfaceArea() const;
    float SidedSurfaceArea(const Plane &P);

    //
    // Helper functions
    //
    void RotateFaces();

protected:
    GraphicsDevice *_GD;
};
