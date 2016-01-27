#include "stdafx.h"
#include "Quaternion.h"

//constructors
Quaternion::Quaternion()
{
}

//Quaternion::Quaternion(float theta, Vec3f vector){
//	w = theta;
//	x = vector.x();
//	y = vector.y();
//	z = vector.z();
//}


//Quaternion::Quaternion(float W, float X, float Y, float Z){
//	w = W;
//	x = X;
//	y = Y;
//	z = Z;
//}

//Quaternion::Quaternion(const Quaternion & rkQ){
//	w = rkQ.W();
//	x = rkQ.X();
//	y = rkQ.Y();
//	z = rkQ.Z();
//}

Quaternion::~Quaternion()
{
}

//member functions
Mat4f Quaternion::getRotationMatrix(){
	return Mat4f(
		1-2*x*x-2*z*z, 2*x*y-2*w*z, 2*x*z+2*w*y, 0,
		2*x*y+2*w*z, 1-2*x*x-2*z*z, 2*y*z-2*w*x, 0,
		2*x*z-2*w*y, 2*y*z+2*w*x, 1-2*x*x-2*y*y, 0,
		0, 0, 0, 1
		);

}

//Quaternion Quaternion::operator* (const Quaternion & rkQ){
//	return Quaternion(w * rkQ.W() - x * rkQ.X() - y * rkQ.Y() - z * rkQ.Z(),
//		w * rkQ.X() + x * rkQ.W() + y * rkQ.Z() - z * rkQ.Y(),
//		w * rkQ.Y() + y * rkQ.W() + z * rkQ.X() - x * rkQ.Z(),
//		w * rkQ.Z() + z * rkQ.W() + x * rkQ.Y() - y * rkQ.X());
//}


//Quaternion Quaternion::log() const{
//	//
//}
//Quaternion Quaternion::exp() const;