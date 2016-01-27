//-*- C++ -*-
/*
4D Vector and Matrix
*/
#ifndef MAT4_H_
#define MAT4_H_
#include "Vec3.h"
//#pragma once

//template <class T>
//class Vec3;

template <class T>
class Mat4;

template <class T>
class T_Vec4; //class for transposed 4d vector

template <class T>
class Vec4{	
public:
	typedef T VecType;
	T m_vec[4];

	/*	member functions	*/

	//constructors
	Vec4(){ m_vec[0] = 0; m_vec[1] = 0; m_vec[2] = 0; m_vec[3] = 0; }
	Vec4(T cx, T cy, T cz, T cw) { m_vec[0] = cx; m_vec[1] = cy; m_vec[2] = cz; m_vec[3] = cw; }
	Vec4(const Vec4& v) { *this = v; }
	Vec4(const Vec3<T>& v) :m_vec[0](v.x()), m_vec[1](v.y()), m_vec[2](v.z()), m_vec[3](1.0f){}


	//mathematic functions
	void assignFrom(const Vec4& v) { m_vec[0] = v.m_vec[0]; m_vec[1] = v.m_vec[1]; m_vec[2] = v.m_vec[2]; m_vec[3] = v.m_vec[3]; }
	Vec4& operator=(const Vec4& v) {
		m_vec[0] = v.m_vec[0]; m_vec[1] = v.m_vec[1]; m_vec[2] = v.m_vec[2]; m_vec[3] = v.m_vec[3]; return *this;
	}
	Vec4 operator+(const Vec4& v) const { return Vec4(m_vec[0] + v.m_vec[0], m_vec[1] + v.m_vec[1], m_vec[2] + v.m_vec[2], m_vec[3] + v.m_vec[3]); }
	Vec4 operator+(T c) const { return Vec4(m_vec[0] + c, m_vec[1] + c, m_vec[2] + c, m_vec[3] + c); }
	Vec4 operator-(const Vec4& v) const { return Vec4(m_vec[0] - v.m_vec[0], m_vec[1] - v.m_vec[1], m_vec[2] - v.m_vec[2], m_vec[3] - v.m_vec[3]); }
	Vec4 operator-(T c) const { return Vec4(m_vec[0] - c, m_vec[1] - c, m_vec[2] - c, m_vec[3] - c); }
	Vec4 operator-() const { return Vec4(-m_vec[0], -m_vec[1], -m_vec[2], m_vec[3]); }
	Vec4 operator*(T c) const { return Vec4(m_vec[0] * c, m_vec[1] * c, m_vec[2] * c, m_vec[3]*c); }
	// transpose( transpose(Mat4) * Vec4 )
	Vec4 operator*(const Mat4<T>& m) const{
		return Vec4(m_vec[0] * m.xx() + m_vec[1] * m.yx() + m_vec[2] * m.zx() + m_vec[3] * m.wx(), m_vec[0] * m.xy() + m_vec[1] * m.yy() + m_vec[2] * m.zy() + m_vec[3] * m.wy(),
			m_vec[0] * m.xz() + m_vec[1] * m.yz() + m_vec[2] * m.zz() + m_vec[3] * m.wz(), m_vec[0] * m.xw() + m_vec[1] * m.yw() + m_vec[2] * m.zw() + m_vec[3] * m.ww());
	} // 
	T operator*(const T_Vec4<T> t_vec) const{ //need work
		return m_vec[0] * t_vec.x() + m_vec[1] * t_vec.y() + m_vec[2] * t_vec.z() + m_vec[3] * t_vec.w();
	}
	//Vec4 operator*(const DiagMat4& m) const;
	Vec4 operator/(T c) const { return Vec4(m_vec[0] / c, m_vec[1] / c, m_vec[2] / c, m_vec[3] / c); }
	Vec4& operator+=(const Vec4& v) { m_vec[0] += v.m_vec[0], m_vec[1] += v.m_vec[1], m_vec[2] += v.m_vec[2], m_vec[3] += v.m_vec[2]; return *this; }
	Vec4& operator+=(T c) { m_vec[0] += c, m_vec[1] += c, m_vec[2] += c, m_vec[3] += c; return *this; }
	Vec4& operator-=(const Vec4& v) { m_vec[0] -= c, m_vec[1] -= c, m_vec[2] -= c, m_vec[3] -= c; return *this; }
	Vec4& operator*=(T c) { m_vec[0] *= c, m_vec[1] *= c, m_vec[2] *= c, m_vec[3] *= c; return *this; }
	Vec4& operator/=(T c) { m_vec[0] /= c, m_vec[1] /= c, m_vec[2] /= c, m_vec[3] /= c; return *this; }
	T in(const Vec4& v) const { return (m_vec[0] * v.m_vec[0] + m_vec[1] * v.m_vec[1] + m_vec[2] * v.m_vec[2] + m_vec[3] * v.m_vec[2]); }

	
	/*Vec4 out(const Vec4& v) const {
		return Vec4(m_vec[1] * v.m_vec[0] - m_vec[2] * v.m_vec[1],
			m_vec[2] * v.m_vec[0] - m_vec[0] * v.m_vec[2],
			m_vec[0] * v.m_vec[1] - m_vec[1] * v.m_vec[0]);
	}*/
	/*template <class T>
	Mat4 tns(const Vec4<T>& v) const;*/
	double norm() const { return (m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2] + m_vec[3] * m_vec[3]); }
	double abs() const { return sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2] + m_vec[3] * m_vec[3]); }
	//normalize vector
	Vec4& normalize() {
		T l = abs();
		m_vec[0] /= l; m_vec[1] /= l; m_vec[2] /= l; m_vec[3] /= l;
		return *this;
	}
	//cross product

	Vec4 cross(const Vec4& rhs);
	//down cast a 4 dim vector to 3 dim vector
	//template <class T>
	Vec3<T>& downcast();
	/*upcast vec3 to a vec4
	friend Vec4 Vec3::upcast() const;*/
	//access elements
	T x()const { return m_vec[0]; }
	T& x(){ return m_vec[0]; }

	T y()const { return m_vec[1]; }
	T& y(){ return m_vec[1]; }

	T z()const { return m_vec[2]; }
	T& z(){ return m_vec[2]; }

	T w()const { return m_vec[3]; }
	T& w(){ return m_vec[3]; }
};
//type specification
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;

/////////////////////////////////////////////////////////
//class: T_Vec4
//use: 4d tempate transposed vetor
/////////////////////////////////////////

template <class T>
class T_Vec4
{
	typedef T VecType;
	T m_vec[4];
public:
	T_Vec4(){ m_vec[0] = 0; m_vec[1] = 0; m_vec[2] = 0; m_vec[3] = 0; }
	T_Vec4(T cx, T cy, T cz, T cw) { m_vec[0] = cx; m_vec[1] = cy; m_vec[2] = cz; m_vec[3] = cw; }
	//T_Vec4(const Vec4<T>& v) { m_vec = v.m_vec; }
	T_Vec4(const Vec3<T>& v) :m_vec[0](v.x()), m_vec[1](v.y()), m_vec[2](v.z()), m_vec[3](1.0f){}

	//calculation
	//T operator*(Vec4<T> &rhs){ return m_vec[0] * rhs.x() + m_vec[1] * rhs.y() + m_vec[2] * rhs.z() + m_vec[3] * rhs.w(); }

	//access elements
	T x()const { return m_vec[0]; }
	T& x(){ return m_vec[0]; }

	T y()const { return m_vec[1]; }
	T& y(){ return m_vec[1]; }

	T z()const { return m_vec[2]; }
	T& z(){ return m_vec[2]; }

	T w()const { return m_vec[3]; }
	T& w(){ return m_vec[3]; }
	
};
//type specification
typedef T_Vec4<float> T_Vec4f;
typedef T_Vec4<double> T_Vec4d;

///////////////////////////////////////////////////////////////////
//class: Mat4
//use: 4D tempalte matrix 
//////////////////////////////////////////////////////////////

template <class T>
class Mat4
{
public:
	typedef T VecType;
	T m_mat[4][4];
public:
	Mat4(){
		for(int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				m_mat[i][j] = 0;
			}
		}
	}
	//~Mat4();
	Mat4(T cxx, T cxy, T cxz, T cxw,
		T cyx, T cyy, T cyz, T cyw,
		T czx, T czy, T czz, T czw,
		T cwx, T cwy, T cwz, T cww)
	{
		m_mat[0][0] = cxx; m_mat[0][1] = cxy; m_mat[0][2] = cxz; m_mat[0][3] = cxw;
		m_mat[1][0] = cyx; m_mat[1][1] = cyy; m_mat[1][2] = cyz; m_mat[1][3] = cyw;
		m_mat[2][0] = czx; m_mat[2][1] = czy, m_mat[2][2] = czz; m_mat[2][3] = czw;
		m_mat[3][0] = cwx; m_mat[3][1] = cwy; m_mat[3][2] = cwz; m_mat[3][3] = cww;
	};
	Mat4(T Tarray[4][4]){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				m_mat[i][j] = Tarray[i][j];
			}
		}
	}
	Mat4(const Mat4& m) {
		*this = m;
	}
	void assignFrom(const Mat4& m) {
		for (int i = 0; i < 4;i++){
			for (int j = 0; j < 4; j++){
				m_mat[i][j] = m.m_mat[i][j];
			}
		}
	}
	Mat4& operator=(const Mat4& m) {
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				m_mat[i][j] = m.m_mat[i][j];
			}
		}
		return *this;
	}
	Mat4 operator+(const Mat4& m) const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = m_mat[i][j]+ m.m_mat[i][j];
			}
		}
		return result;
	}
	Mat4 operator+(T c) const {
		return Mat4(m_mat[0][0] + c, m_mat[0][1], m_mat[0][2], m_mat[0][3],
			m_mat[1][0], m_mat[1][1] + c, m_mat[1][2], m_mat[1][3],
			m_mat[2][0], m_mat[2][1], m_mat[2][2] + c, m_mat[2][3],
			m_mat[3][0], m_mat[3][1], m_mat[3][2], m_mat[3][3] + c);
	}
	Mat4 operator-(const Mat4& m) const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = m_mat[i][j] - m.m_mat[i][j];
			}
		}
		return result;
	}
	Mat4 operator-(T c) const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = m_mat[i][j] -c;
			}
		}
		return result;
	}
	Mat4 operator-() const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = -m_mat[i][j];
			}
		}
		return result;
	}
	Mat4 operator*(const Mat4& m) const {
		Mat4 result=Mat4();
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				for (int iCount = 0; iCount < 4; iCount++){
					result.m_mat[i][j] += m_mat[i][iCount] * m.m_mat[iCount][j];
				}
			}
		}
		return result;
	}
	//multiply with vector
	template<class T>
	Vec4<T> operator*(const Vec4<T>& v) const {
		return Vec4<T>(m_mat[0][0] * v.x() + m_mat[0][1] * v.y() + m_mat[0][2] * v.z() + m_mat[0][3] * v.w(),
			m_mat[1][0] * v.x() + m_mat[1][1] * v.y() + m_mat[1][2] * v.z() + m_mat[1][3] * v.w(),
			m_mat[2][0] * v.x() + m_mat[2][1] * v.y() + m_mat[2][2] * v.z() + m_mat[2][3] * v.w(),
			m_mat[3][0] * v.x() + m_mat[3][1] * v.y() + m_mat[3][2] * v.z() + m_mat[3][3] * v.w());
	}
	Mat4 operator*(double c) const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = c*m_mat[i][j];
			}
		}
		return result;
	}
	Mat4 operator/(T c) const {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = m_mat[i][j]/c;
			}
		}
		return result;
	}

	///// additional operators ///////////////
	Mat4 operator+=(const Mat4& m){
		return this + m;
	}

	Mat4 operator+=(T c){
		return T + c;
	}

	Mat4 operator-=(const Mat4& m){
		return this + m;
	}

	Mat4 operator-=(T c){
		return T + c;
	}

	Mat4 operator*=(const Mat4& m){
		Mat4 r;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				r.m_mat[i][j] = m_mat[i][j] * m.m_mat[i][j];
			}
		}
		return r;
	}

	Mat4 operator*=(T c){
		return T * c;
	}

	Mat4 operator/=(T c){
		return T + c;
	}


	//absolut value
	T abs() const {
		T result(0);
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result += m_mat[i][j] * m_mat[i][j];
			}
		}
		return sqrt(result);
	}

	//transpose
	Mat4 Trans() {
		Mat4 result;
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j]=m_mat[j][i];
			}
		}
		return result;
	}


	//det
	T det(){
		T value=
			m_mat[0][3] * m_mat[1][2]* m_mat[2][1] * m_mat[3][0] - m_mat[0][2]*m_mat[1][3]*m_mat[2][1]*m_mat[3][0] - m_mat[0][3] * m_mat[1][1]*m_mat[2][2]*m_mat[3][0] + m_mat[0][1]*m_mat[1][3]*m_mat[2][2]*m_mat[3][0] +
			m_mat[0][2] * m_mat[1][1] *m_mat[2][3] * m_mat[3][0] - m_mat[0][1] * m_mat[1][2] * m_mat[2][3]*m_mat[3][0] - m_mat[0][3] * m_mat[1][2]*m_mat[2][0]*m_mat[3][1] + m_mat[0][2]*m_mat[1][3]*m_mat[2][0]*m_mat[3][1] +
			m_mat[0][3] * m_mat[1][0]* m_mat[2][2]*m_mat[3][1] - m_mat[0][0]*m_mat[1][3]*m_mat[2][2]*m_mat[3][1] - m_mat[0][2]*m_mat[1][0]*m_mat[2][3]*m_mat[3][1] + m_mat[0][0]*m_mat[1][2]*m_mat[2][3]*m_mat[3][1] +
			m_mat[0][3] * m_mat[1][1] * m_mat[2][0] * m_mat[3][2] - m_mat[0][1] * m_mat[1][3] * m_mat[2][0] * m_mat[3][2] - m_mat[0][3] * m_mat[1][0] * m_mat[2][1] * m_mat[3][2] + m_mat[0][0] * m_mat[1][3] * m_mat[2][1] * m_mat[3][2] +
			m_mat[0][1]*m_mat[1][0]*m_mat[2][3]*m_mat[3][2] - m_mat[0][0]*m_mat[1][1]*m_mat[2][3]*m_mat[3][2] - m_mat[0][2]*m_mat[1][1]*m_mat[2][0]*m_mat[3][3] + m_mat[0][1]*m_mat[1][2]*m_mat[2][0]*m_mat[3][3] +
			m_mat[0][2]*m_mat[1][0]*m_mat[2][1]*m_mat[3][3] - m_mat[0][0]*m_mat[1][2]*m_mat[2][1]*m_mat[3][3] - m_mat[0][1]*m_mat[1][0]*m_mat[2][2]*m_mat[3][3] + m_mat[0][0]*m_mat[1][1]*m_mat[2][2]*m_mat[3][3];
		return value;
	}

	//Inverse
	Mat4 Inverse() {
		Mat4 result;
		result.m_mat[0][0] = m_mat[1][2]*m_mat[2][3]*m_mat[3][1] - m_mat[1][3]*m_mat[2][2]*m_mat[3][1] + m_mat[1][3]*m_mat[2][1]*m_mat[3][2] - m_mat[1][1]*m_mat[2][3]*m_mat[3][2] - m_mat[1][2]*m_mat[2][1]*m_mat[3][3] + m_mat[1][1]*m_mat[2][2]*m_mat[3][3];
		result.m_mat[0][1] = m_mat[0][3]*m_mat[2][2]*m_mat[3][1] - m_mat[0][2]*m_mat[2][3]*m_mat[3][1] - m_mat[0][3]*m_mat[2][1]*m_mat[3][2] + m_mat[0][1]*m_mat[2][3]*m_mat[3][2] + m_mat[0][2]*m_mat[2][1]*m_mat[3][3] - m_mat[0][1]*m_mat[2][2]*m_mat[3][3];
		result.m_mat[0][2] = m_mat[0][2]*m_mat[1][3]*m_mat[3][1] - m_mat[0][3]*m_mat[1][2]*m_mat[3][1] + m_mat[0][3]*m_mat[1][1]*m_mat[3][2] - m_mat[0][1]*m_mat[1][3]*m_mat[3][2] - m_mat[0][2]*m_mat[1][1]*m_mat[3][3] + m_mat[0][1]*m_mat[1][2]*m_mat[3][3];
		result.m_mat[0][3] = m_mat[0][3]*m_mat[1][2]*m_mat[2][1] - m_mat[0][2]*m_mat[1][3]*m_mat[2][1] - m_mat[0][3]*m_mat[1][1]*m_mat[2][2] + m_mat[0][1]*m_mat[1][3]*m_mat[2][2] + m_mat[0][2]*m_mat[1][1]*m_mat[2][3] - m_mat[0][1]*m_mat[1][2]*m_mat[2][3];
		result.m_mat[1][0] = m_mat[1][3]*m_mat[2][2]*m_mat[3][0] - m_mat[1][2]*m_mat[2][3]*m_mat[3][0] - m_mat[1][3]*m_mat[2][0]*m_mat[3][2] + m_mat[1][0]*m_mat[2][3]*m_mat[3][2] + m_mat[1][2]*m_mat[2][0]*m_mat[3][3] - m_mat[1][0]*m_mat[2][2]*m_mat[3][3];
		result.m_mat[1][1] = m_mat[0][2]*m_mat[2][3]*m_mat[3][0] - m_mat[0][3]*m_mat[2][2]*m_mat[3][0] + m_mat[0][3]*m_mat[2][0]*m_mat[3][2] - m_mat[0][0]*m_mat[2][3]*m_mat[3][2] - m_mat[0][2]*m_mat[2][0]*m_mat[3][3] + m_mat[0][0]*m_mat[2][2]*m_mat[3][3];
		result.m_mat[1][2] = m_mat[0][3]*m_mat[1][2]*m_mat[3][0] - m_mat[0][2]*m_mat[1][3]*m_mat[3][0] - m_mat[0][3]*m_mat[1][0]*m_mat[3][2] + m_mat[0][0]*m_mat[1][3]*m_mat[3][2] + m_mat[0][2]*m_mat[1][0]*m_mat[3][3] - m_mat[0][0]*m_mat[1][2]*m_mat[3][3];
		result.m_mat[1][3] = m_mat[0][2]*m_mat[1][3]*m_mat[2][0] - m_mat[0][3]*m_mat[1][2]*m_mat[2][0] + m_mat[0][3]*m_mat[1][0]*m_mat[2][2] - m_mat[0][0]*m_mat[1][3]*m_mat[2][2] - m_mat[0][2]*m_mat[1][0]*m_mat[2][3] + m_mat[0][0]*m_mat[1][2]*m_mat[2][3];
		result.m_mat[2][0] = m_mat[1][1]*m_mat[2][3]*m_mat[3][0] - m_mat[1][3]*m_mat[2][1]*m_mat[3][0] + m_mat[1][3]*m_mat[2][0]*m_mat[3][1] - m_mat[1][0]*m_mat[2][3]*m_mat[3][1] - m_mat[1][1]*m_mat[2][0]*m_mat[3][3] + m_mat[1][0]*m_mat[2][1]*m_mat[3][3];
		result.m_mat[2][1] = m_mat[0][3]*m_mat[2][1]*m_mat[3][0] - m_mat[0][1]*m_mat[2][3]*m_mat[3][0] - m_mat[0][3]*m_mat[2][0]*m_mat[3][1] + m_mat[0][0]*m_mat[2][3]*m_mat[3][1] + m_mat[0][1]*m_mat[2][0]*m_mat[3][3] - m_mat[0][0]*m_mat[2][1]*m_mat[3][3];
		result.m_mat[2][2] = m_mat[0][1]*m_mat[1][3]*m_mat[3][0] - m_mat[0][3]*m_mat[1][1]*m_mat[3][0] + m_mat[0][3]*m_mat[1][0]*m_mat[3][1] - m_mat[0][0]*m_mat[1][3]*m_mat[3][1] - m_mat[0][1]*m_mat[1][0]*m_mat[3][3] + m_mat[0][0]*m_mat[1][1]*m_mat[3][3];
		result.m_mat[2][3] = m_mat[0][3]*m_mat[1][1]*m_mat[2][0] - m_mat[0][1]*m_mat[1][3]*m_mat[2][0] - m_mat[0][3]*m_mat[1][0]*m_mat[2][1] + m_mat[0][0]*m_mat[1][3]*m_mat[2][1] + m_mat[0][1]*m_mat[1][0]*m_mat[2][3] - m_mat[0][0]*m_mat[1][1]*m_mat[2][3];
		result.m_mat[3][0] = m_mat[1][2]*m_mat[2][1]*m_mat[3][0] - m_mat[1][1]*m_mat[2][2]*m_mat[3][0] - m_mat[1][2]*m_mat[2][0]*m_mat[3][1] + m_mat[1][0]*m_mat[2][2]*m_mat[3][1] + m_mat[1][1]*m_mat[2][0]*m_mat[3][2] - m_mat[1][0]*m_mat[2][1]*m_mat[3][2];
		result.m_mat[3][1] = m_mat[0][1]*m_mat[2][2]*m_mat[3][0] - m_mat[0][2]*m_mat[2][1]*m_mat[3][0] + m_mat[0][2]*m_mat[2][0]*m_mat[3][1] - m_mat[0][0]*m_mat[2][2]*m_mat[3][1] - m_mat[0][1]*m_mat[2][0]*m_mat[3][2] + m_mat[0][0]*m_mat[2][1]*m_mat[3][2];
		result.m_mat[3][2] = m_mat[0][2]*m_mat[1][1]*m_mat[3][0] - m_mat[0][1]*m_mat[1][2]*m_mat[3][0] - m_mat[0][2]*m_mat[1][0]*m_mat[3][1] + m_mat[0][0]*m_mat[1][2]*m_mat[3][1] + m_mat[0][1]*m_mat[1][0]*m_mat[3][2] - m_mat[0][0]*m_mat[1][1]*m_mat[3][2];
		result.m_mat[3][3] = m_mat[0][1]*m_mat[1][2]*m_mat[2][0] - m_mat[0][2]*m_mat[1][1]*m_mat[2][0] + m_mat[0][2]*m_mat[1][0]*m_mat[2][1] - m_mat[0][0]*m_mat[1][2]*m_mat[2][1] - m_mat[0][1]*m_mat[1][0]*m_mat[2][2] + m_mat[0][0]*m_mat[1][1]*m_mat[2][2];
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				result.m_mat[i][j] = result.m_mat[i][j]/det();
			}
		}
		return result;
	}

	//to array
	T* ToArray(){
		T *Array=new T[16];
		for (unsigned int i = 0; i < 4; i++){
			for (unsigned int j = 0; j < 4; j++){
				Array[4*j+i] = m_mat[i][j];
			}
		}
		return Array;
	}

	//set to identity
	void Identity(){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (i == j){
					m_mat[i][j] = (T)1;
				}
				m_mat[i][j] = (T)0;
			}
		}
	}

	//void print(const char *msg = "") const;
	//access member
	T xx()const { return m_mat[0][0]; }
	T& xx(){ return m_mat[0][0]; }

	T xy()const { return m_mat[0][1]; }
	T& xy(){ return m_mat[0][1]; }

	T xz()const { return m_mat[0][2]; }
	T& xz(){ return m_mat[0][2]; }

	T xw()const { return m_mat[0][3]; }
	T& xw(){ return m_mat[0][3]; }

	T yx()const { return m_mat[1][0]; }
	T& yx(){ return m_mat[1][0]; }

	T yy()const { return m_mat[1][1]; }
	T& yy(){ return m_mat[1][1]; }

	T yz()const { return m_mat[1][2]; }
	T& yz(){ return m_mat[1][2]; }

	T yw()const { return m_mat[1][3]; }
	T& yw(){ return m_mat[1][3]; }

	T zx()const { return m_mat[2][0]; }
	T& zx(){ return m_mat[2][0]; }

	T zy()const { return m_mat[2][1]; }
	T& zy(){ return m_mat[2][1]; }

	T zz()const { return m_mat[2][2]; }
	T& zz(){ return m_mat[2][2]; }

	T zw()const { return m_mat[2][3]; }
	T& zw(){ return m_mat[2][3]; }

	T wx()const { return m_mat[3][0]; }
	T& wx(){ return m_mat[3][0]; }

	T wy()const { return m_mat[3][1]; }
	T& wy(){ return m_mat[3][1]; }

	T wz()const { return m_mat[3][2]; }
	T& wz(){ return m_mat[3][2]; }

	T ww()const { return m_mat[3][3]; }
	T& ww(){ return m_mat[3][3]; }
};

//type specification
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;
// as a row vector
//template <class T>
//inline Vec4<T> Vec4<T>::operator*(const Mat4<T>& m) const {
//	return Vec4<T>(m_vec[0] * m.xx() + m_vec[1] * m.yx() + m_vec[2] * m.zx() + m_vec[3] * m.wx(),
//		m_vec[0]()*m.xy() + m_vec[1] * m.yy() + m_vec[2] * m.zy() + m_vec[3] * m.wy(),
//		m_vec[0]()*m.xz() + m_vec[1] * m.yz() + m_vec[2] * m.zz() + m_vec[3] * m.wz(),
//		m_vec[0]()*m.xw() + m_vec[1] * m.yw() + m_vec[2] * m.zw() + m_vec[3] * m.ww());
//}

//template <class T>
//inline Mat4<T> Vec4<T>::tns(const Vec4<T>& v) const {
//	return Mat4<T>(m_vec[0] * v.x, m_vec[0] * v.y, m_vec[0] * v.z, m_vec[0]*v.w,
//		m_vec[1] * v.x, m_vec[1] * v.y, m_vec[1] * v.z, m_vec[1]*v.w,
//		m_vec[2] * v.x, m_vec[2] * v.y, m_vec[2] * v.z,m_vec[2]*v.w,
//		m_vec[3] * v.x, m_vec[3] * v.y, m_vec[3] * v.z, m_vec[3] * v.w);
//}



//template <class T>
//friend Vec4<T> Vec3<T>::upcast() const{
//	return Vec4<T>(this.m_vec[0], this.m_vec[1], this.[2], 1);
//}

template <class T>
inline Vec4<T> Vec4<T>::cross(const Vec4& rhs)
{
	return Vec3(m_vec[1] * rhs.m_vec[2] - m_vec[2] * rhs.m_vec[1],
		m_vec[2] * rhs.m_vec[0] - m_vec[0] * rhs.m_vec[2],
		m_vec[0] * rhs.m_vec[1] - m_vec[1] * rhs.m_vec[0]
		m_vec[3]);

}
template <class T>
Vec3<T>& Vec4<T>::downcast(){
	/*T x = m_vec[0] / m_vec[3];
	T y = m_vec[1] / m_vec[3];
	T z = m_vec[2] / m_vec[3];*/
	return Vec3<T>(m_vec[0] / m_vec[3], m_vec[1] / m_vec[3], m_vec[2] / m_vec[3]);
}


template <class T>
//IdentityMatrix
class Mat4Identity : public Mat4<T>
{
	Mat4Identity(){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (i == j){
					m_mat[i][j] = 1;
				}
				m_mat[i][j] = 0;
			}
		}
	}
	~Mat4Identity();
};

#endif