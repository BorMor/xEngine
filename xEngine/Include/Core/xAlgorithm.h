#pragma once

template<typename T>
void xConstruct(T* ptr);

template<typename T>
void xConstructN(T* first, size_t n);

template <typename T>
void xCopyN(T* dst, T* first, size_t n);

template<typename T>
void xCopyConstruct(T* ptr, const T& orig);

template <typename T>
void xCopyConstructN(T* dst, T* first, size_t n);

template <typename T>
void xMoveN(T* dst, const T* first, size_t n);

template<typename T>
void xDestruct(T* ptr);

template<typename T>
void xDestructN(T* first, size_t n);

#include "xAlgorithm.inl"