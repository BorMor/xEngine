#pragma once

#define xSAFE_DELETE(p) \
	{ if(p) { delete p;     p=NULL; } }

#define xSAFE_ARRAY_DELETE(p) \
	{ if(p) { delete [] p;     p=NULL; } }

#define xHIDE_IMPLEMENTATION	\
private:						\
	struct Impl;				\
	Impl*	pImpl;

#define xDEFINE_FLAGS(T)			\
	inline T operator | (T a, T b)	\
	{								\
	  return T(int(a) | int(b));	\
	}

template<int T>
struct xIntToType
{
    enum 
    {
        Value = T
    };
};