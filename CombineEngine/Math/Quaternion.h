#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "stdafx.h"
#include <cmath>
class Quaternion
{
private:
	float w;
	float x;
	float y;
	float z;
public:
	Quaternion();
	Quaternion(float theta, Vec3f vector){}
	Quaternion(float W, float X, float Y, float Z):w(W),x(X),y(Y),z(Z){}
	//Quaternion(const Quaternion & rkQ){ return rkQ; }
	//Quaternion& operator = (const Quaternion & rkQ){ return *rkQ; }
	
	~Quaternion();

	
	//calculations  ///////////////////////////////////////////////////////

	//with scalar 
	inline Quaternion operator+(const float t) const { return Quaternion(w + t, x, y, z); }
	inline Quaternion operator-(const float t) const { return Quaternion(w - t, x, y, z); }
	inline Quaternion operator*(const float t) const { return Quaternion(w*t, x*t, y*t, z*t); }
	inline Quaternion operator/(const float t) const { return Quaternion(w / t, x / t, y / t, z / t); }

	//with quaternion
	inline Quaternion operator+ (const Quaternion & rkQ) const { return Quaternion(w + rkQ.W(), x + rkQ.X(), y + rkQ.Y(), z + rkQ.Z()); }
	inline Quaternion operator- (const Quaternion & rkQ) const { return Quaternion(w - rkQ.W(), x - rkQ.X(), y - rkQ.Y(), z - rkQ.Z()); }
	inline Quaternion& operator+= (const Quaternion & rkQ) { w = w + rkQ.W(); x = x + rkQ.X(); y = y + rkQ.Y(); z = z + rkQ.Z(); return *this; }
	inline Quaternion& operator-= (const Quaternion & rkQ) { w = w - rkQ.W(); x = x - rkQ.X(); y = y - rkQ.Y(); z = z - rkQ.Z(); return *this; }
	inline Quaternion operator* (const Quaternion & rkQ) const {
		return Quaternion(w * rkQ.W() - x * rkQ.X() - y * rkQ.Y() - z * rkQ.Z(),
			w * rkQ.X() + x * rkQ.W() + y * rkQ.Z() - z * rkQ.Y(),
			w * rkQ.Y() + y * rkQ.W() + z * rkQ.X() - x * rkQ.Z(),
			w * rkQ.Z() + z * rkQ.W() + x * rkQ.Y() - y * rkQ.X());
	}
	inline Quaternion operator/ (const Quaternion & rkQ) const;
	inline Quaternion& operator*= (const Quaternion & rkQ);
	inline Quaternion& operator/= (const Quaternion & rkQ);
	inline Quaternion operator* () const;
	inline Quaternion& normalize(){
		float fNorm = sqrtf(w*w + x*x + y*y + z*z);
		w = w / fNorm;
		x = x / fNorm;
		y = y / fNorm;
		z = z / fNorm;
		return *this;
	}
	Quaternion log() const;
	Quaternion exp() const;
	inline Quaternion pow(const float t) const { return (this->log()*t).exp(); }

	//product
	inline float dot(const Quaternion & rkQ) const { return x*rkQ.x + y*rkQ.y + z*rkQ.z; }
	Quaternion cross(const Quaternion & rkQ) const{ return Quaternion(0, -z*rkQ.y + y*rkQ.z, z*rkQ.x - x*rkQ.z, -y*rkQ.x + x*rkQ.y); }

	////////////////////////////////////////////////////////////////////////////////////////
	
	//transformation
	Quaternion& FromRotationMatrix(const Mat4f & rkRot);
	Mat4f getRotationMatrix();

	//member access
	float W() const{ return w; }
	float & W(){ return w; }
	float X() const{ return x; }
	float & X(){ return x; }
	float Y() const{ return y; }
	float & Y(){ return y; }
	float Z() const{ return z; }
	float & Z(){ return z; }

	//interpolation
	//Quaternion lerp(const Quaternion & rkQ, float fFactor);
	//Quaternion slerp(const Quaternion & rkQ, float fFactor){}
};

//operators
inline Quaternion operator *(const float a, const Quaternion rhQ){  //constant scalar multiply quaternion
	return Quaternion(a*rhQ.W(), a*rhQ.X(), a*rhQ.Y(), a*rhQ.Z());
}

//inline Quaternion Lerp(const double tau, const Quaternion& Qa, const Quaternion& Qb) { return (pow((Qb / Qa), tau) * Qa); }
inline Quaternion Slerp(const float tau, const Quaternion& Qa, const Quaternion& Qb) { //two element spherical intoplation
	//getOmega
	float omega = acos(Qa.dot(Qb));
	Quaternion slerp = sin((1 - tau)*omega) / sin(omega)*Qa + sin(tau*omega) / sin(omega)*Qb;
}

inline Quaternion Squad(const float tau, const Quaternion& Qa, const Quaternion& Qb, const Quaternion& Qc, const Quaternion& Qd){ //Quadric spherical interpolation
	//
}



#endif //QUATERNION_H_