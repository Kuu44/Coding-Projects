/*
BaseMesh.cpp
Written by Matthew Fisher

BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
Each mesh must be associated with a graphics device before most operations can be performed.

Because there are so many associated functions, they are grouped into various files.
*/

//BaseMeshBounding.cpp contains functions about bounding and determining the size of the mesh
#include "BaseMeshBounding.cpp"

//BaseMeshFiles.cpp contains functions about saving and loading ASCII, binary, and *.obj files
#include "BaseMeshFiles.cpp"

//BaseMeshIndexing.cpp contains the WeldVertices, UnIndex, and TwoPatch functions
#include "BaseMeshIndexing.cpp"

//BaseMeshMemory.cpp contains functions surrounding memory management and AppendVertices
#include "BaseMeshMemory.cpp"

//BaseMeshShapes.cpp contains all the shape generation functions
#include "BaseMeshShapes.cpp"

//BaseMeshSplitting.cpp contains all the Split and PerfectSplit functions
#include "BaseMeshSplitting.cpp"

//BaseMeshVertexModifiers.cpp contains all the vertex coloring, texturing, and transformation functions
#include "BaseMeshVertexModifiers.cpp"
