// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define  _USE_MATH_DEFINES

#include <mathimf.h>

#define _CRTDBG_MAP_ALLOC

#define _CRT_RAND_S

#include <stdlib.h>
#include <crtdbg.h>

#include <wx/wxprec.h>

#include <portaudio.h>
#include <porttime.h>

using namespace std;

#include <vector>
#include <algorithm>

// TODO: reference additional headers your program requires here

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release(); p = 0; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

#ifdef _DEBUG
   #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
   #define DEBUG_CLIENTBLOCK
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define		USE_FFT			FFT_FFTW

