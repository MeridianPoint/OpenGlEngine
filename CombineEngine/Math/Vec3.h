/*
 *  Vec3.h
 *
 */
#ifndef _VEC3_H_
#define _VEC3_H_
//#pragma once

#define _USE_MATH_DEFINES
#include <cmath> 
#include <limits>
#include <algorithm>
//#include "Mat4.h"

template <class T>
class Vec3
{
public:
	//typedef float T;
    typedef T VecType;
	static const int dim = 3;
	
public:
	Vec3() {};
	Vec3(const Vec3& v) { *this = v; }
	Vec3(T v) { m_vec[0]=v; m_vec[1]=v; m_vec[2] = v; }
	Vec3(T x, T y, T z) { m_vec[0]=x; m_vec[1]=y; m_vec[2] = z; }
	Vec3(T* v) {m_vec[0] = v[0]; m_vec[1] = v[1]; m_vec[2] = v[2]; }
	
    Vec3& operator=(float rhs) { for (size_t i=0; i<dim; ++i) {m_vec[i] = rhs; }; return *this; }
	Vec3& operator=(const Vec3& rhs) { for (size_t i=0; i<dim; ++i) {m_vec[i] = rhs.m_vec[i]; } return *this; }
	
	// Comparison operators 
	bool operator==(const Vec3& rhs) const { return (m_vec[0]==rhs.m_vec[0] && m_vec[1]==rhs.m_vec[1] && m_vec[2]==rhs.m_vec[2]); }
	bool operator!=(const Vec3& rhs) const { return !(*this == rhs); }
	bool operator<(const Vec3& rhs) const { return (lengthsq() < rhs.lengthsq()); }
	bool operator<=(const Vec3& rhs) const { return (lengthsq() <= rhs.lengthsq()); }
	bool operator>(const Vec3& rhs) const { return !(*this <= rhs); }
	bool operator>=(const Vec3& rhs) const { return !(*this < rhs); }

	// Math operators (+,-,/*,+=,-=,/=,*=)
	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(const Vec3& rhs);
	Vec3& operator/=(const Vec3& rhs);
	
	Vec3& operator+=(const T rhs);
	Vec3& operator-=(const T rhs);
	Vec3& operator*=(const T rhs);
	Vec3& operator/=(const T rhs);
	
	Vec3 operator+(const Vec3& rhs);
	Vec3 operator-(const Vec3& rhs);
	Vec3 operator*(const Vec3& rhs);
	Vec3 operator/(const Vec3& rhs);
	
	Vec3 operator+(T rhs);
	Vec3 operator-(T rhs);
	Vec3 operator*(T rhs);
	Vec3 operator/(T rhs);
	
	Vec3 operator-() {Vec3<T> v(-m_vec[0], -m_vec[1], -m_vec[2]); return v; }
	
	// functions: dot(), cross(), len, lensq, norm, norm_safe
	T length() const { return sqrtf(lengthsq()); }
	T lengthsq() const { return (m_vec[0]*m_vec[0] + m_vec[1]*m_vec[1] + m_vec[2]*m_vec[2]); }	
	//nomralization
	T normalize();
	Vec3 getNorm() const { Vec3 v(*this);  v.normalize(); return v; }
	
	T dot(const Vec3& rhs);
	Vec3 cross(const Vec3& rhs);
	
	T minVal() const;
	T maxVal() const;
	
	// Access Elements:
	T& operator[](size_t i) { return m_vec[i]; }
	const T& operator[](size_t i) const { return m_vec[i]; }
	
	void set(T v) { for (size_t i=0; i<dim; ++i) { m_vec[i] = v; } }
	void set(T x, T y, T z) { m_vec[0]=x; m_vec[1]=y; m_vec[2]=z; }
	//upcast 
	//Vec4& upcast(){
	//	return Vec4(m_vec[0], m_vec[1], m_vec[2], m_vec[3]);
	//}
	
	T& x() { return m_vec[0]; }
	T x() const { return m_vec[0]; }
	T& y() { return m_vec[1]; }
	T y() const { return m_vec[1]; }
	T& z() { return m_vec[2]; }
	T z() const { return m_vec[2]; }
	
	T& r() { return m_vec[0]; }
	T r() const { return m_vec[0]; }
	T& g() { return m_vec[1]; }
	T g() const { return m_vec[1]; }
	T& b() { return m_vec[2]; }
	T b() const { return m_vec[2]; }
	
	T* getPtr() { return m_vec; }
	const T* getPtr() const { return m_vec; }
	
protected:
	T m_vec[dim];
};

// typedefs for declaring standard vectors
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<int> Vec3i;
	
template <class T>
inline T Vec3<T>::normalize() 
{
	T len = length();
	
	for (size_t i=0; i<dim; ++i)
		m_vec[i] = m_vec[i]/len;
	
	return len;
}
	
template <class T>
inline T Vec3<T>::dot(const Vec3& rhs)
{
	T dp = T(0);
	for (size_t i=0; i<dim; ++i)
	{
		dp += m_vec[i]*rhs.m_vec[i];
	}
	
	return dp;
}
	
template <class T>
inline Vec3<T> Vec3<T>::cross(const Vec3& rhs)
{
	return Vec3(m_vec[1]*rhs.m_vec[2] - m_vec[2]*rhs.m_vec[1],
				m_vec[2]*rhs.m_vec[0] - m_vec[0]*rhs.m_vec[2],
				m_vec[0]*rhs.m_vec[1] - m_vec[1]*rhs.m_vec[0]);
			
}

template <class T>
inline T Vec3<T>::minVal() const
{
	T min_val = std::numeric_limits<T>::min();
	
	for (size_t i=0; i<dim; ++i)
		min_val = std::min(min_val, m_vec[i]);
	
	return min_val;
}

template <class T>
inline T Vec3<T>::maxVal() const
{
	T max_val = std::numeric_limits<T>::max();
		
	for (size_t i=0; i<dim; ++i)
		max_val = std::max(max_val, m_vec[i]);
			
	return max_val;
}
	
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] += rhs.m_vec[i];
	}
	return *this;
}

template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] -= rhs.m_vec[i];
	}
	return *this;
}
    
template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const Vec3& rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] *= rhs.m_vec[i];
	}
	return *this;
}

template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const Vec3& rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] /= rhs.m_vec[i];
	}
	return *this;
}
    
template <class T>
inline Vec3<T>& Vec3<T>::operator+=(const T rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] += rhs;
	}
	return *this;
}

template <class T>
inline Vec3<T>& Vec3<T>::operator-=(const T rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] -= rhs;
	}
	return *this;
}

template <class T>
inline Vec3<T>& Vec3<T>::operator*=(const T rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] *= rhs;
	}
	return *this;
}

template <class T>
inline Vec3<T>& Vec3<T>::operator/=(const T rhs)
{
	for (size_t i=0; i<dim; ++i)
	{
		m_vec[i] /= rhs;
	}
	return *this;
}

template <class T>
inline Vec3<T> Vec3<T>::operator+(const Vec3& rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] + rhs.m_vec[i];
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator-(const Vec3& rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] - rhs.m_vec[i];
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator*(const Vec3& rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] * rhs.m_vec[i];
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator/(const Vec3& rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] / rhs.m_vec[i];
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator+(T rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] + rhs;
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator-(T rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] - rhs;
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator*(T rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] * rhs;
	}
	return result;
}

template <class T>
inline Vec3<T> Vec3<T>::operator/(T rhs)
{
	Vec3 result;
	
	for (size_t i=0; i<dim; ++i)
	{
		result.m_vec[i] = m_vec[i] / rhs;
	}
	return result;
}


#endif

