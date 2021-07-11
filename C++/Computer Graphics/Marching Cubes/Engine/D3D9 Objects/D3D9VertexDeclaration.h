/*
D3D9VertexDeclaration.h
Written by Matthew Fisher

D3D9VertexDeclaration is a wrapper around the D3D9 IDirect3DVertexDeclaration9 object.
*/

#ifdef USE_D3D9

class D3D9VertexDeclaration
{
public:
    D3D9VertexDeclaration();
    void Init(LPDIRECT3DDEVICE9 _Device);
    void Set();

private:
    LPDIRECT3DVERTEXDECLARATION9 Decleration;
    LPDIRECT3DDEVICE9 Device;
};

#endif