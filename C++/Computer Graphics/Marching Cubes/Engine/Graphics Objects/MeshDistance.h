/*
MeshDistance.h
Written by Matthew Fisher

Abstract interface for mesh-mesh distance.
*/

class MeshDistance
{
public:
    void InitSingleMesh(const BaseMesh &m, const Matrix4 &transform)
    {
        Vector< pair<const BaseMesh*, Matrix4> > meshes;
        meshes.PushEnd( pair<const BaseMesh*, Matrix4>(&m, transform) );
        InitMeshList(meshes);
    }
    virtual void InitMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes) = 0;
    virtual bool IntersectMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes) const = 0;
    bool IntersectSingleMesh(const BaseMesh &m, const Matrix4 &transform) const
    {
        Vector< pair<const BaseMesh*, Matrix4> > meshes(1);
        meshes[0] = pair<const BaseMesh*, Matrix4>(&m, transform);
        return IntersectMeshList(meshes);
    }
};

class MeshDistanceBruteForce : public MeshDistance
{
public:
    void InitMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes);
    bool IntersectMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes) const;

private:
    struct TriangleEntry
    {
        Vec3f V[3];
        Vec3f center, variance;
    };
    Vector<TriangleEntry> _triangles;
};