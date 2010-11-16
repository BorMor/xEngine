#pragma once

template<typename T> 
struct xIsIntegral 
{
        enum { Value = false };
};


template<typename T> 
struct xIsFloatingPoint
{
        enum { Value = false };
};


template<> struct xIsIntegral<char> { enum { Value = true }; };
template<> struct xIsIntegral<bool> { enum { Value = true }; };
template<> struct xIsIntegral<short> { enum { Value = true }; };
template<> struct xIsIntegral<int> { enum { Value = true }; };
template<> struct xIsIntegral<long> { enum { Value = true }; };
template<> struct xIsIntegral<wchar_t> { enum { Value = true }; };

template<> struct xIsFloatingPoint<float> { enum { Value = true }; };
template<> struct xIsFloatingPoint<double> { enum { Value = true }; };

template<typename T>
struct xIsPod
{
        enum { Value = false };
};

#define xTYPE_IS_POD(T)	\
	template<> struct xIsPod<T> { enum { Value = true }; };

template<typename T>
struct xIsPointer
{
        enum { Value = false };
};

template<typename T> struct xIsPointer<T*> { enum { Value = true }; };

template<typename T> 
struct xIsFundamental
{
        enum 
        {
                Value = xIsIntegral<T>::Value || xIsFloatingPoint<T>::Value
        };
};

template<typename T> 
struct xHasTrivialConstructor
{
        enum
        {
                Value = xIsFundamental<T>::Value || xIsPointer<T>::Value || xIsPod<T>::Value
        };
};


template<typename T> 
struct xHasTrivialCopy
{
        enum
        {
                Value = xIsFundamental<T>::Value || xIsPointer<T>::Value || xIsPod<T>::Value
        };
};

template<typename T> 
struct xHasTrivialAssign
{
        enum
        {
                Value = xIsFundamental<T>::Value || xIsPointer<T>::Value || xIsPod<T>::Value
        };
};

template<typename T> 
struct xHasTrivialDestructor
{
        enum
        {
                Value = xIsFundamental<T>::Value || xIsPointer<T>::Value || xIsPod<T>::Value
        };
};
