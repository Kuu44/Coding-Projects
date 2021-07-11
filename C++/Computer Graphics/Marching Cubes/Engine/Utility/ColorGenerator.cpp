/*
ColorGenerator.cpp
Written by Matthew Fisher
*/

void ColorGenerator::Generate(Vector<RGBColor> &Result)
{
    Generate(Result, Vec3f(1.0f, 1.0f, 1.0f));
}

void ColorGenerator::Generate(Vector<RGBColor> &Result, const Vec3f &Scale)
{
    const UINT ColorCount = Result.Length();
    KMeansClustering<Vec3f, Vec3fKMeansMetric> Clustering;
    
    Vector<Vec3f> AllColors(ColorCount * 25);
    const UINT AllColorsCount = AllColors.Length();
    for(UINT Index = 0; Index < AllColorsCount; Index++)
    {
        Vec3f CurColor = Vec3f(rnd(), rnd(), rnd());
        while(CurColor.x + CurColor.y + CurColor.z < 0.5f)
        {
            CurColor = Vec3f(rnd(), rnd(), rnd());
        }
        AllColors[Index] = Vec3f(CurColor.x * Scale.x, CurColor.y * Scale.y, CurColor.z * Scale.z);
    }

    Clustering.Cluster(AllColors, ColorCount, 20, false);

    for(UINT ColorIndex = 0; ColorIndex < ColorCount; ColorIndex++)
    {
        Result[ColorIndex] = RGBColor(Clustering.ClusterCenter(ColorIndex));
    }
}
