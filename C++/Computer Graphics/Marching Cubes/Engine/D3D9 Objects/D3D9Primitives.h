/*
D3D9Primitives.h
Written by Matthew Fisher
*/

#ifdef USE_D3D9

class D3D9Primitives
{
public:
    void Init(D3D9GraphicsDevice &graphics, D3D9VertexShader &vs, D3D9PixelShader &ps, int sphereRefinement, int stacks, int slices);

    void RenderSphere(const Matrix4 &viewPerspective, float radius, const Vec3f &p, RGBColor color);

    void RenderCylinder(const Matrix4 &viewPerspective, float radius, const Vec3f &p0, const Vec3f &p1, RGBColor color);

    void RenderOrientedBox(const Matrix4 &viewPerspective, float radius, const Vec3f *points, RGBColor color);

private:
    D3D9GraphicsDevice *_graphics;
    D3D9VertexShader *_vs;
    D3D9PixelShader *_ps;
    D3D9Mesh _sphere, _cylinder, _box;
};

#endif