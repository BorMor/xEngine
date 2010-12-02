#pragma once

#include "xConfig.h"

typedef unsigned char	xByte;
typedef char			xChar;
typedef unsigned int	xUInt32;
typedef int				xInt32;
typedef unsigned short	xUInt16;
typedef short			xInt16;
typedef float			xFloat;

#if defined(xPLATFORM_WIN32)
	#include <windows.h>
#elif defined(xPLATFORM_LINUX)	
	#include <string.h>
	#include <stdarg.h>
#endif

#include <utility>

#include <stdio.h>
#include <math.h>

#include "Core/xUtil.h"
#include "Core/xTypeTraits.h"
#include "Core/xString.h"

#include "Core/xException.h"

#include "Core/xSharedPtr.h"

#include "Core/xAlgorithm.h"
#include "Core/Containers/xArray.h"
#include "Core/Containers/xKeyValuePair.h"
#include "Core/Containers/xHashTable.h"
#include "Core/Containers/xList.h"

#include "Math/xColor.h"
#include "Math/xVector2.h"
#include "Math/xVector3.h"
#include "Math/xPlane.h"
#include "Math/xQuaternion.h"
#include "Math/xMatrix.h"

#include "Util/xDelegate.h"
#include "Util/xEvent.h"
#include "Util/xSleep.h"
#include "Util/xTimer.h"

#include "IO/xConsole.h"
#include "IO/xStream.h"
#include "IO/xFile.h"
#include "IO/xFileStream.h"
#include "IO/xMemoryStream.h"
#include "IO/xBinaryReader.h"
#include "IO/xBinaryWriter.h"

#include "Text/xRegex.h"

#include "Graphics/xPixelShader.h"
#include "Graphics/xVertexShader.h"
#include "Graphics/xMaterial.h"
#include "Graphics/xVertexFormat.h"
#include "Graphics/xIndexBuffer.h"
#include "Graphics/xVertexBuffer.h"
#include "Graphics/xRenderWindow.h"
#include "Graphics/xRenderDevice.h"

#include "Graphics/xMesh.h"

#include "Framework/xApplication.h"
#include "Framework/xConsoleApplication.h"
#include "Framework/xGraphicApplication.h"
