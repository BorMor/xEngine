#pragma once

#include "xEngine.h"

#if defined(xPLATFORM_WIN32)
	#include <windows.h>
#elif defined(xPLATFORM_LINUX)
	#include <X11/Xlib.h>
#endif

#include "xOpenGL.h"
