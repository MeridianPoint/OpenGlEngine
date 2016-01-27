#ifndef EULAR_ANGLE_H_
#define EULAR_ANGLE_H_
#include "stdafx.h"
class Eular_Angle
{
private:
	Vec3f angles;
public:
	Eular_Angle();
	~Eular_Angle();

	Mat4f getMatrix();
	bool checkGimbalLock();
	Quaternion toQuaternion();
};

#endif