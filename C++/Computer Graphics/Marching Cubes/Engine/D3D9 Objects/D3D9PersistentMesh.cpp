/*
D3D9PersistentMesh.cpp
Written by Matthew Fisher

D3D9PersistentMesh is a D3D9Mesh that is backed up with a RAM copy, so it can be
preserved when the device is lost and needs to be reset.
*/

#ifdef USE_D3D9

D3D9PersistentMesh::D3D9PersistentMesh()
{
    _Device = NULL;
}

D3D9PersistentMesh::~D3D9PersistentMesh()
{
    FreeMemory();
}

void D3D9PersistentMesh::FreeMemory()
{
    _Mesh.FreeMemory();
    _D3DMesh.FreeMemory();
    _Device = NULL;
}

void D3D9PersistentMesh::ReleaseMemory()
{
    _D3DMesh.FreeMemory();
    _Device = NULL;
}

void D3D9PersistentMesh::Reset(GraphicsDevice &graphics)
{
    ReleaseMemory();
    _D3DMesh = _Mesh;
    _Device = graphics.CastD3D9().GetDevice();
}

void D3D9PersistentMesh::Init(GraphicsDevice &graphics, const BaseMesh &M)
{
    _Mesh = M;
    Reset(graphics);
}

/*void D3DSafeMesh::Set()
{
    FullValidate( Device->SetStreamSource( 0, VB, 0, sizeof(MeshVertex) ) );
    FullValidate( Device->SetIndices( IB ) );
}*/

void D3D9PersistentMesh::Render()
{
    _D3DMesh.Render();
    //Set();
    //D3DValidate( Device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, VCount, 0, FCount ) );
}

#endif