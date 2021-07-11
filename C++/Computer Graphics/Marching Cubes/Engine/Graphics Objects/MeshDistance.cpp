/*
MeshDistance.cpp
Written by Matthew Fisher

Mesh-mesh distance implementation.
*/

void MeshDistanceBruteForce::InitMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes)
{
    UINT triangleSum = 0;
    const UINT meshCount = meshes.Length();
    for(UINT meshIndex = 0; meshIndex < meshCount; meshIndex++)
    {
        triangleSum += meshes[meshIndex].first->FaceCount();
    }

    _triangles.Allocate(triangleSum);

	UINT triangleListIndex = 0;

	for(UINT meshIndex = 0; meshIndex < meshCount; meshIndex++)
    {
        const BaseMesh &curMesh = *meshes[meshIndex].first;
        const Matrix4 &curTransform = meshes[meshIndex].second;
        const UINT triangleCount = curMesh.FaceCount();
        const MeshVertex *vertices = curMesh.Vertices();
        const DWORD *indices = curMesh.Indices();
		for(UINT triangleIndex = 0; triangleIndex < triangleCount; triangleIndex++)
		{
            TriangleEntry &curEntry = _triangles[triangleListIndex];
            curEntry.V[0] = curTransform.TransformPoint(vertices[ indices[ triangleIndex * 3 + 0 ] ].Pos);
            curEntry.V[1] = curTransform.TransformPoint(vertices[ indices[ triangleIndex * 3 + 1 ] ].Pos);
            curEntry.V[2] = curTransform.TransformPoint(vertices[ indices[ triangleIndex * 3 + 2 ] ].Pos);
            Rectangle3f curBBox = Rectangle3f::ConstructFromTwoPoints(curEntry.V[0], curEntry.V[1]);
            curBBox.ExpandBoundingBox(curEntry.V[2]);
            curEntry.center = curBBox.Center();
            curEntry.variance = curBBox.Variance();
			triangleListIndex++;
		}
    }
}

bool MeshDistanceBruteForce::IntersectMeshList(const Vector< pair<const BaseMesh*, Matrix4> > &meshes) const
{
    const UINT meshCount = meshes.Length();
    const UINT mTriangleCount = _triangles.Length();
    for(UINT meshIndex = 0; meshIndex < meshCount; meshIndex++)
    {
        const BaseMesh &curMesh = *meshes[meshIndex].first;
        const Matrix4 &curTransform = meshes[meshIndex].second;
        const UINT triangleCount = curMesh.FaceCount();
        const MeshVertex *vertices = curMesh.Vertices();
        const DWORD *indices = curMesh.Indices();
		for(UINT outerTriangleIndex = 0; outerTriangleIndex < triangleCount; outerTriangleIndex++)
		{
			const Vec3f t0 = curTransform.TransformPoint(vertices[ indices[ outerTriangleIndex * 3 + 0 ] ].Pos);
			const Vec3f t1 = curTransform.TransformPoint(vertices[ indices[ outerTriangleIndex * 3 + 1 ] ].Pos);
			const Vec3f t2 = curTransform.TransformPoint(vertices[ indices[ outerTriangleIndex * 3 + 2 ] ].Pos);

            Rectangle3f curBBox = Rectangle3f::ConstructFromTwoPoints(t0, t1);
            curBBox.ExpandBoundingBox(t2);
            const Vec3f center = curBBox.Center();
            const Vec3f variance = curBBox.Variance();
			
            for(UINT innerTriangleIndex = 0; innerTriangleIndex < mTriangleCount; innerTriangleIndex++)
            {
                const TriangleEntry &curEntry = _triangles[innerTriangleIndex];
                if(Math::Abs(center.x - curEntry.center.x) <= variance.x + curEntry.variance.x &&
                   Math::Abs(center.y - curEntry.center.y) <= variance.y + curEntry.variance.y &&
                   Math::Abs(center.z - curEntry.center.z) <= variance.z + curEntry.variance.z)
                {
                    if(Math::DistanceTriangleTriangleSq(t0, t1, t2, curEntry.V[0], curEntry.V[1], curEntry.V[2]) == 0.0f)
                    {
                        float value = Math::DistanceTriangleTriangleSq(t0, t1, t2, curEntry.V[0], curEntry.V[1], curEntry.V[2]);
                        return true;
                    }
                }
            }
		}
    }
    return false;
}
