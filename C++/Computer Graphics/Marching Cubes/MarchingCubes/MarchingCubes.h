struct GRIDCELL {
   Vec3f p[8];		//position of each corner of the grid in world space
   float val[8];	//value of the function at this grid corner
};

//given a grid cell, returns the set of triangles that approximates the region where val == 0.
/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
	0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
int Polygonise(GRIDCELL &Grid, TriMeshFace *Triangles, int &NewVertexCount, Vec3f *Vertices);