#pragma once

#include "../config.h"

template<class T> inline T operator~ (T a) { return (T)~(GLenum)a; }
template<class T> inline T operator| (T a, T b) { return (T)((GLenum)a | (GLenum)b); }
template<class T> inline T operator& (T a, T b) { return (T)((GLenum)a & (GLenum)b); }
template<class T> inline T operator^ (T a, T b) { return (T)((GLenum)a ^ (GLenum)b); }
template<class T> inline T& operator|= (T& a, T b) { return (T&)((GLenum&)a |= (GLenum)b); }
template<class T> inline T& operator&= (T& a, T b) { return (T&)((GLenum&)a &= (GLenum)b); }
template<class T> inline T& operator^= (T& a, T b) { return (T&)((GLenum&)a ^= (GLenum)b); }
