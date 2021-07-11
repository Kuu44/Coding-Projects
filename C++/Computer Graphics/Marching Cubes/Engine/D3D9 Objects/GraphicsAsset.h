/*
GraphicsAsset.h
Written by Matthew Fisher

GraphicsAsset is an abstract class used for all resetable graphics objects
*/

class GraphicsAsset
{
public:
    virtual void ReleaseMemory() = 0;
    virtual void FreeMemory() = 0;
    virtual void Reset(GraphicsDevice &device) = 0;
};
