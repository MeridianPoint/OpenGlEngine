#ifndef FIXED_ANGLE_H_
#define FIXED_ANGLE_H_

#include "stdafx.h"
class Fixed_Angle
{
private:
	Vec3f vAngles;
public:
	
	Fixed_Angle();
	Fixed_Angle(Vec3f vAngle) :vAngles(vAngle){}
	Fixed_Angle(float xAngle, float yAngle, float zAngle) :vAngles(xAngle,yAngle,zAngle){}
	~Fixed_Angle();

	//member functions
	Vec3f getAngles(){ return vAngles; }
	Mat4f getRotationMatrix();

	//member access
	float xAngle()const{ return vAngles.x(); }
	float yAngle()const{ return vAngles.y(); }
	float zAngle()const{ return vAngles.z(); }
};
//non-member function

Fixed_Angle lerp(Fixed_Angle fa1, Fixed_Angle fa2, float fFactor){ return Fixed_Angle((fa1.xAngle() + fa2.xAngle()) / 2, (fa1.yAngle() + fa2.yAngle()) / 2, (fa1.zAngle() + fa2.zAngle()) / 2); };

#endif//FIXED_ANGLE_H_