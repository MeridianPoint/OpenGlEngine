// File: $Id: progstyle-c++.html,v 1.4 2003/12/01 23:08:03 cs4 Exp $
// Author: Qiushuo Wang
// Contributors: other people who contributed to the class
// Description: a description of what the class does
// Revisions:
// $Log: progstyle-c++.html,v $
// Revision 1.4  2003/12/01 23:08:03  cs4
// Changed '.C' references to '.cpp'.
//
// Revision 1.3  2002/09/18 02:49:20  cs4
// Responded to suggestions from CS4 faculty.
//
// Revision 1.2  2002/09/17 18:40:12  cs4
// First complete rework into html (jeh)
//

#ifndef VEC2_H_
#define VEC2_H_

template <class T>
class Vec2
{
public:
	typedef T VecType;
	T m_vec[2];
public:
	Vec2() {};
	//~Vec2();



	Vec2(const Vec2& v) { *this = v; }
	Vec2(T v) { m_vec[0] = v; m_vec[1] = v; }
	Vec2(T x, T y) { m_vec[0] = x; m_vec[1] = y; }
	Vec2(T* v) { m_vec[0] = v[0]; m_vec[1] = v[1]; }

	//calculation
	Vec2 operator -(const Vec2 &rhs){
		return Vec2(m_vec[0] - rhs.x(), m_vec[1] - rhs.y());
	}

	Vec2 operator +(const Vec2 &rhs){
		return Vec2(m_vec[0] + rhs.x(), m_vec[1] + rhs.y());
	}

	Vec2 operator +=(const Vec2 &rhs){
		return Vec2(m_vec[0] + rhs.x(), m_vec[1] + rhs.y());
	}

	T& x() { return m_vec[0]; }
	T x() const { return m_vec[0]; }
	T& y() { return m_vec[1]; }
	T y() const { return m_vec[1]; }

	T* getPtr(){ return m_vec; }
};
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int> Vec2i;

#endif