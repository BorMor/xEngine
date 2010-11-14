#pragma once

#include "xEngine.h"

#if defined(xPLATFORM_WIN32)
#include <windows.h>
#elif defined(xPLATFORM_LINUX)
#include <GL/glx.h>
#include <X11/X.h>
#endif

#include "xOpenGL.h"
