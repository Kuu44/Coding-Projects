struct TriPoint {
	int x,y,z;
};

class IsoSurface {
public:
	IsoSurface();
	void FreeMemory();

	void IsoApproximate(float BoxSize, float CellSize, BaseMesh &Result, float (*Function)(const Vec3f &Pos));
	void IsoApproximate(const Vec3f &Start, const Vec3f &End, float _CellSize, BaseMesh &Result, float (*Function)(const Vec3f &Pos));

private:
    void PolygonizeGrids(float *TopVals, float *BottomVals, int TopZ);
	void FillGrid(float *Grid, int z);

	bool PushPolygons(GRIDCELL &g);
	void MakeObject(BaseMesh &Result);

	void CalcGradient(const Vec3f &Pos, Vec3f &Normal);

	UINT _XCount, _YCount, _ZCount;
	Vec3f _Start, _End, _Diff;
	float _CellSize;

	Vector<Vec3f> _AllVertices;
	Vector<TriMeshFace> _AllFaces;

    TriMeshFace _FaceStorage[10];
	Vec3f _VertexStorage[15];

	float (*_Function)(const Vec3f &Pos);
	float _Epsilon;
};