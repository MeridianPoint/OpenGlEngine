#include "stdafx.h"
#include "Fixed_Angle.h"


Fixed_Angle::Fixed_Angle()
{
}


Fixed_Angle::~Fixed_Angle()
{
}


Mat4f Fixed_Angle::getRotationMatrix(){
	//
	Mat4f xRotation = Mat4f(
		1, 0, 0, 0,
		0, cos(vAngles.x()), -sin(vAngles.x()), 0,
		0, sin(vAngles.x()), cos(vAngles.x()), 0,
		0, 0, 0, 1
		);
	Mat4f yRotation = Mat4f(
		cos(vAngles.y()), 0, sin(vAngles.y()), 0,
		0, 1, 0, 0,
		-sin(vAngles.y()), 0, cos(vAngles.y()), 0,
		0, 0, 0, 1
		);
	Mat4f zRotation = Mat4f(
		cos(vAngles.z()), -sin(vAngles.z()), 0, 0,
		sin(vAngles.z()), cos(vAngles.z()), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);
	return xRotation*yRotation*zRotation;
}