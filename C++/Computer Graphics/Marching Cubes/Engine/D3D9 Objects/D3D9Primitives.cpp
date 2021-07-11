/*
D3D9Primitives.cpp
Written by Matthew Fisher
*/

#ifdef USE_D3D9

void D3D9Primitives::Init(D3D9GraphicsDevice &graphics, D3D9VertexShader &vs, D3D9PixelShader &ps, int sphereRefinement, int stacks, int slices)
{
    _graphics = &graphics;
    _vs = &vs;
    _ps = &ps;

    _sphere.SetGD(graphics);
    _cylinder.SetGD(graphics);

    _sphere.CreateSphere(1.0f, sphereRefinement);
    _cylinder.CreateCylinder(1.0f, 1.0f, slices, stacks);

    //_box.CreateBox(1.0f, 1.0f, 1.0f);
}

void D3D9Primitives::RenderSphere(const Matrix4 &viewPerspective, float radius, const Vec3f &p, RGBColor color)
{
    Matrix4 scale = Matrix4::Scaling(Vec3f(radius, radius, radius));
    Matrix4 translate = Matrix4::Translation(p);
    Matrix4 world = scale * translate;

    _vs->Set();
    _ps->Set();
    
    _vs->SetMatrix("WorldViewProj", world * viewPerspective);
    _vs->SetMatrix("World", world);
    _ps->SetVec4("Color", Vec4f(Vec3f(color), 1.0f));
    
    _sphere.Render();
}

void D3D9Primitives::RenderCylinder(const Matrix4 &viewPerspective, float radius, const Vec3f &p0, const Vec3f &p1, RGBColor color)
{
    Vec3f diff = p1 - p0;
    float height = diff.Length();

    Matrix4 scale = Matrix4::Scaling(Vec3f(radius, radius, height));
    Matrix4 face = Matrix4::Face(Vec3f::eZ, diff);
    Matrix4 translate = Matrix4::Translation(p0);
    Matrix4 world = scale * face * translate;
	
    _vs->SetMatrix("WorldViewProj", world * viewPerspective);
    _vs->SetMatrix("World", world);
    _ps->SetVec4("Color", Vec4f(Vec3f(color), 1.0f));

    _cylinder.Render();
}

void D3D9Primitives::RenderOrientedBox(const Matrix4 &viewPerspective, float radius, const Vec3f *points, RGBColor color)
{
    RenderCylinder(viewPerspective, radius, points[0], points[1], color);
    RenderCylinder(viewPerspective, radius, points[0], points[2], color);
    RenderCylinder(viewPerspective, radius, points[1], points[3], color);
    RenderCylinder(viewPerspective, radius, points[2], points[3], color);

    RenderCylinder(viewPerspective, radius, points[0], points[4], color);
    RenderCylinder(viewPerspective, radius, points[1], points[5], color);
    RenderCylinder(viewPerspective, radius, points[2], points[6], color);
    RenderCylinder(viewPerspective, radius, points[3], points[7], color);

    RenderCylinder(viewPerspective, radius, points[4], points[5], color);
    RenderCylinder(viewPerspective, radius, points[4], points[6], color);
    RenderCylinder(viewPerspective, radius, points[5], points[7], color);
    RenderCylinder(viewPerspective, radius, points[6], points[7], color);

    /*LPDIRECT3DDEVICE9 device = _graphics->GetDevice();
    
    D3DCOLOR D3DColor = RGBColor(90, 90, 90);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device->SetRenderState(D3DRS_BLENDFACTOR, D3DColor);

    _box.Render();

    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}

/*void D3D9Primitives::RenderBox(const Matrix4 &viewPerspective, float radius, const Rectangle3f &rect, RGBColor color)
{
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Min.y, Rect.Min.z), Vec3f(Rect.Max.x, Rect.Min.y, Rect.Min.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Min.y, Rect.Min.z), Vec3f(Rect.Max.x, Rect.Max.y, Rect.Min.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Max.y, Rect.Min.z), Vec3f(Rect.Min.x, Rect.Max.y, Rect.Min.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Max.y, Rect.Min.z), Vec3f(Rect.Min.x, Rect.Min.y, Rect.Min.z), Color);

    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Min.y, Rect.Min.z), Vec3f(Rect.Min.x, Rect.Min.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Min.y, Rect.Min.z), Vec3f(Rect.Max.x, Rect.Min.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Max.y, Rect.Min.z), Vec3f(Rect.Max.x, Rect.Max.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Max.y, Rect.Min.z), Vec3f(Rect.Min.x, Rect.Max.y, Rect.Max.z), Color);

    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Min.y, Rect.Max.z), Vec3f(Rect.Max.x, Rect.Min.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Min.y, Rect.Max.z), Vec3f(Rect.Max.x, Rect.Max.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Max.x, Rect.Max.y, Rect.Max.z), Vec3f(Rect.Min.x, Rect.Max.y, Rect.Max.z), Color);
    RenderCylinder(GD, MC, Radius, Vec3f(Rect.Min.x, Rect.Max.y, Rect.Max.z), Vec3f(Rect.Min.x, Rect.Min.y, Rect.Max.z), Color);

    Matrix4 Scale = Matrix4::Scaling(Rect.Dimensions());
    Matrix4 Translate = Matrix4::Translation(Rect.Min);

    MC.World = Scale * Translate;

    LPDIRECT3DDEVICE9 Device = GD.CastD3D9().GetDevice();
    
    D3DCOLOR D3DColor = RGBColor(90, 90, 90);
    Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
    Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVBLENDFACTOR);
    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    Device->SetRenderState(D3DRS_BLENDFACTOR, D3DColor);

    _Box.SetColor(Color);
    _Box.Render();

    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}*/

#endif