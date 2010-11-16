#include <new.h>

namespace Internal
{
	template<typename T>
    void xConstruct(T* ptr, xIntToType<false>)
    {
		new (ptr) T();
    }

    template<typename T>
    void xConstruct(T*, xIntToType<true>)
    {
    }

    template<typename T>
    void xConstructN(T* first, size_t n, xIntToType<false>)
    {
		for (size_t i = 0; i < n; ++i)
			new (first + i) T();
    }

    template<typename T>
    void xConstructN(T* first, int n, xIntToType<true>)
    {
    }

	template <typename T>
	void xCopyN(T* dst, T* first, size_t n, xIntToType<false>)
	{
		const T* last = first + n;

        switch (n & 0x3)
        {
        case 0:
                while (first != last)
                {
					*dst++ = *first++;
        case 3:		*dst++ = *first++;
        case 2:		*dst++ = *first++;
        case 1:		*dst++ = *first++;
                }
        }

	}	
	
	template <typename T>
	void xCopyN(T* dst, T* first, size_t n, xIntToType<true>)
	{		
		memcpy(dst, first, n * sizeof(T));
	}

	template<typename T>
	void xCopyConstruct(T* ptr, const T& orig, xIntToType<false>)
	{
		new (ptr) T(orig);
	}

	template<typename T>
	void xCopyConstruct(T* ptr, const T& orig, xIntToType<true>)
	{
		ptr[0] = orig;
	}

	template <typename T>
	void xCopyConstructN(T* dst, T* first, size_t n, xIntToType<false>)
	{
		for (size_t i = 0; i < n; ++i)
			new (dst + i) T(first[i]);
	}
	
	template <typename T>
	void xCopyConstructN(T* dst, T* first, size_t n, xIntToType<true>)
	{
		memcpy(dst, first, n * sizeof(T));
	}

	template <typename T>
	void xMoveN(T* dst, const T* first, size_t n, xIntToType<false>)
	{
		for (int i = int(n) - 1; i >= 0; --i)
			dst[i] = first[i];
	}

	template <typename T>
	void xMoveN(T* dst, const T* first, size_t n, xIntToType<true>)
	{
		memmove(dst, first, n * sizeof(T));
	}

	template<typename T>
	void xDestruct(T* ptr, xIntToType<false>)
	{		
			ptr->~T();
	}

	template<typename T>
	void xDestruct(T* ptr, xIntToType<true>)
	{
	}

	template<typename T>
	void xDestructN(T* first, size_t n, xIntToType<false>)
	{
		for (size_t i = 0; i < n; ++i)
			(first+n)->~T();
	}

	template<typename T>
	void xDestructN(T* first, size_t n, xIntToType<true>)
	{
	}
}



template<typename T>
void xConstruct(T* ptr)
{
	Internal::xConstruct(ptr, xIntToType<xHasTrivialConstructor<T>::Value>());
}


template<typename T>
void xConstructN(T* first, size_t n)
{
	Internal::xConstructN(first, n, xIntToType<xHasTrivialConstructor<T>::Value>());
}

template <typename T>
void xCopyN(T* dst, T* first, size_t n)
{
	Internal::xCopyN(dst, first, n, xIntToType<xHasTrivialCopy<T>::Value>());
}

template<typename T>
void xCopyConstruct(T* ptr, const T& orig)
{
	Internal::xCopyConstruct(ptr, orig, xIntToType<xHasTrivialCopy<T>::Value>());
}

template <typename T>
void xCopyConstructN(T* dst, T* first, size_t n)
{
	Internal::xCopyConstructN(dst, first, n, xIntToType<xHasTrivialCopy<T>::Value>());
}

template <typename T>
void xMoveN(T* dst, const T* first, size_t n)
{
	Internal::xMoveN(dst, first, n, xIntToType<xHasTrivialCopy<T>::Value>());
}

template<typename T>
void xDestruct(T* ptr)
{
	Internal::xDestruct(ptr, xIntToType<xHasTrivialDestructor<T>::Value>());
}

template<typename T>
void xDestructN(T* first, size_t n)
{
	Internal::xDestructN(first, n, xIntToType<xHasTrivialDestructor<T>::Value>());
}