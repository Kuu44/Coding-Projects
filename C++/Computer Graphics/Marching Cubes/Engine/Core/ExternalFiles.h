/*
ExternalFiles.h
Written by Matthew Fisher

All #includes that are part of C++ core, STL, or other libraries
*/

//
// All libraries
// Media Foundation: Mfreadwrite.lib;Mfplat.lib
// DirectX: DXGI.lib;d3d9.lib;d3dx9.lib
// Windows: winmm.lib;opengl32.lib
// Math: libtaucs.lib;blas_win32.lib;lapack_win32.lib;libatlas.lib;libcblas.lib;libf77blas.lib;liblapack.lib;libmetis.lib;vcf2c.lib
// Images: libpng.lib;zdll.lib;SDL_image.lib;SDL.lib;SDLMain.lib
//

#define NOMINMAX

// Windows
#include <windows.h>
#include <winuser.h>

#ifdef USE_D3D9
// DirectX 9
#include <d3d9.h>
#include <d3dx9.h>
//#include <dxerr.h>
#endif

#ifdef USE_D3D10
// DirectX 10
#include <d3d10.h>
#include <d3dx10.h>
#endif
#pragma comment(lib,"d3d9.lib")

#ifdef USE_OPENGL
// OpenGL
#include <gl\gl.h>
#include <gl\glu.h>
#endif

// C/C++
#include <math.h>
#include <memory.h>
#include <time.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

// STL
#include <map>
#include <queue>
#include <set>
#include <hash_map>
#include <hash_set>

// TAUCS (sparse matrix package)
#ifdef USE_TAUCS
extern "C" {
#include "Taucs.h"
};
#endif

#ifdef USE_ZLIB

// ZLib (compression)
#include "zlib.h"

// PNG saving and loading (requires zlib)
#ifdef USE_PNG
#include "png.h"
#endif

#endif

#ifdef USE_SDL
#include "SDL\SDL_image.h"
#endif

//using namespace std avoids typing std::
using namespace std;
using namespace stdext;
