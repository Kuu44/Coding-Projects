#include "Main.h"

IsoSurface::IsoSurface()
{
	_Function = NULL;
	_Epsilon = 0.0003f;
}

void IsoSurface::CalcGradient(const Vec3f &Pos, Vec3f &Normal)
{
	float value = _Function(Pos);
	Normal.x = (_Function(Vec3f(Pos.x + _Epsilon, Pos.y, Pos.z)) - value);
	Normal.y = (_Function(Vec3f(Pos.x, Pos.y + _Epsilon, Pos.z)) - value);
	Normal.z = (_Function(Vec3f(Pos.x, Pos.y, Pos.z + _Epsilon)) - value);
    Normal = Vec3f::Normalize(Normal);
}

void IsoSurface::IsoApproximate(float BoxSize, float CellSize, BaseMesh &Result, float (*Function)(const Vec3f &Pos))
{
	Vec3f End(BoxSize, BoxSize, BoxSize);
	IsoApproximate(-End, End, CellSize, Result, Function);
}

void IsoSurface::IsoApproximate(const Vec3f &Start, const Vec3f &End, float CellSize, BaseMesh &Result, float (*Function)(const Vec3f &Pos))
{
	_Function = Function;
	_CellSize = CellSize;
	_Start = Start;
	_End = End;
	_Diff = _End - _Start;
	_XCount = int(_Diff.x / _CellSize);
	_YCount = int(_Diff.y / _CellSize);
	_ZCount = int(_Diff.z / _CellSize);

	float *TopGrid = new float[_XCount * _YCount];
	float *BottomGrid = new float[_XCount * _YCount];
	
    FillGrid(TopGrid, 0);
	for(UINT z = 1; z < _ZCount - 1; z++)
	{
		FillGrid(BottomGrid, z);
		PolygonizeGrids(TopGrid, BottomGrid, z);
        Utility::Swap(TopGrid, BottomGrid);
	}

	delete[] TopGrid;
	delete[] BottomGrid;

	MakeObject(Result);
}

void IsoSurface::FreeMemory()
{
	
}

void IsoSurface::MakeObject(BaseMesh &Result)
{
	Result.Allocate(_AllVertices.Length(), _AllFaces.Length());
	
	MeshVertex *V = Result.Vertices();
	DWORD *I = Result.Indices();
	for(UINT VertexIndex = 0; VertexIndex < _AllVertices.Length(); VertexIndex++)
	{
        MeshVertex &CurVertex = V[VertexIndex];
        CurVertex.Pos = _AllVertices[VertexIndex];
		CalcGradient(CurVertex.Pos, CurVertex.Normal);
	}
    for(UINT FaceIndex = 0; FaceIndex < _AllFaces.Length(); FaceIndex++)
	{
        const TriMeshFace &CurFace = _AllFaces[FaceIndex];
        I[FaceIndex * 3 + 0] = CurFace.I[0];
        I[FaceIndex * 3 + 1] = CurFace.I[1];
        I[FaceIndex * 3 + 2] = CurFace.I[2];
	}
	
    Result.ColorNormals();
}

bool IsoSurface::PushPolygons(GRIDCELL &g)
{
	int NewVertexCount, IndexShift = _AllVertices.Length();
	int NewFaceCount = Polygonise(g, _FaceStorage, NewVertexCount, _VertexStorage);
	if(NewFaceCount)
	{
		for(int FaceIndex = 0; FaceIndex < NewFaceCount; FaceIndex++)
		{
			_FaceStorage[FaceIndex].I[0] += IndexShift;
			_FaceStorage[FaceIndex].I[1] += IndexShift;
			_FaceStorage[FaceIndex].I[2] += IndexShift;
			_AllFaces.PushEnd(_FaceStorage[FaceIndex]);
		}
		for(int VertexIndex = 0; VertexIndex < NewVertexCount; VertexIndex++)
		{
			_AllVertices.PushEnd(_VertexStorage[VertexIndex]);
		}
		return true;
	}
	return false;
}

void IsoSurface::FillGrid(float *Grid, int z)
{
	for(UINT x = 0; x < _XCount; x++)
    {
		for(UINT y = 0; y < _YCount; y++)
		{
			Vec3f Pos = Vec3f(_Start.x + _CellSize * x,_Start.y + _CellSize * y,_Start.z + _CellSize * (z + 1));
			Grid[x * _YCount + y] = _Function(Pos);
		}
    }
}

void IsoSurface::PolygonizeGrids(float *TopVals, float *BottomVals, int z)
{
	for(UINT x = 0; x < _XCount - 1; x++)
    {
		for(UINT y = 0; y < _YCount - 1; y++)
		{
            GRIDCELL g;
			g.p[0] = Vec3f(_Start.x + _CellSize * (x+0),_Start.y + _CellSize * (y+0),_Start.z + _CellSize * (z+0));
			g.p[1] = Vec3f(_Start.x + _CellSize * (x+1),_Start.y + _CellSize * (y+0),_Start.z + _CellSize * (z+0));
			g.p[2] = Vec3f(_Start.x + _CellSize * (x+1),_Start.y + _CellSize * (y+1),_Start.z + _CellSize * (z+0));
			g.p[3] = Vec3f(_Start.x + _CellSize * (x+0),_Start.y + _CellSize * (y+1),_Start.z + _CellSize * (z+0));

			g.val[0] = TopVals[x*_YCount+y];
			g.val[1] = TopVals[(x+1)*_YCount+y];
			g.val[2] = TopVals[(x+1)*_YCount+y+1];
			g.val[3] = TopVals[x*_YCount+y+1];

			g.p[4] = Vec3f(_Start.x + _CellSize * (x+0),_Start.y + _CellSize * (y+0),_Start.z + _CellSize * (z+1));
			g.p[5] = Vec3f(_Start.x + _CellSize * (x+1),_Start.y + _CellSize * (y+0),_Start.z + _CellSize * (z+1));
			g.p[6] = Vec3f(_Start.x + _CellSize * (x+1),_Start.y + _CellSize * (y+1),_Start.z + _CellSize * (z+1));
			g.p[7] = Vec3f(_Start.x + _CellSize * (x+0),_Start.y + _CellSize * (y+1),_Start.z + _CellSize * (z+1));

			g.val[4] = BottomVals[x*_YCount+y];
			g.val[5] = BottomVals[(x+1)*_YCount+y];
			g.val[6] = BottomVals[(x+1)*_YCount+y+1];
			g.val[7] = BottomVals[x*_YCount+y+1];

			bool Valid = true;
			for(UINT VertexIndex = 0; VertexIndex < 8 && Valid; VertexIndex++)
			{
				if(g.val[VertexIndex] == FLT_MAX)
				{
					Valid = false;
				}
			}
			if(Valid)
			{
				PushPolygons(g);
			}
		}
    }
}