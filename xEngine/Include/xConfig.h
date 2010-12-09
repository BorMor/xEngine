#pragma once

#if defined(__GNUC__)
#	define xCOMPILER_GCC
#elif defined(_MSC_VER)
#	define xCOMPILER_MSVC
#else
#	error Could not detect compiler
#endif

#if defined(_WIN32)
#	define xPLATFORM_WIN32
#elif defined(__linux__)
#	define xPLATFORM_LINUX
#else
#	error Could not detect platform
#endif

#if defined(xCOMPILER_GCC)
#	define xFORCE_INLINE inline
#elif defined(xCOMPILER_MSVC)
#	define xFORCE_INLINE __forceinline
#endif

#if defined(DEBUG) || defined(_DEBUG)
#	define xDEBUG
#else
#	undef xDEBUG
#endif

#if defined (xCOMPILER_MSVC)
#	define xBREAKPOINT __asm { int 3 }
#elif defined (xCOMPILER_GCC)
#	define xBREAKPOINT asm("int3");
#else
#	error Breakpoints not implemented yet for this compiler
#endif

#if defined(DEBUG) || defined(_DEBUG)
#	define xDEBUG
#else
#	undef xDEBUG
#endif

#if defined(xDEBUG)
#	define xASSERT(a)  if (!(a))                           \
                        {                                   \
                            xBREAKPOINT		                \
                        }
#else
#	define xASSERT(a)  {}
#endif

#if defined(xPLATFORM_WIN32) && defined(xCOMPILER_MSVC)
#	if defined(xENGINE_EXPORTS)
#		define xEXPORT __declspec(dllexport)
#	else
#		define xEXPORT __declspec(dllimport)
#	endif
#   pragma warning(disable:4251)
#	pragma warning(disable:4996)
#else
#	define xEXPORT
#endif

#if defined(__LP64__) || defined(WIN64)
#	define x64
#endif
