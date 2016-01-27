#include "stdafx.h"
#include "Eular_Angle.h"


Eular_Angle::Eular_Angle()
{
}


Eular_Angle::~Eular_Angle()
{
}

Mat4f Eular_Angle::getMatrix(){
	Mat4f xRotation = Mat4f(
		1,0,0,0,
		0, cos(angles.x()), -sin(angles.x()),0,
		0, sin(angles.x()), cos(angles.x()),0,
		0,0,0,1
		);
	Mat4f yRotation = Mat4f(
		cos(angles.y()),0, sin(angles.y()),0,
		0, 1, 0, 0,
		-sin(angles.y()),0, cos(angles.y()),0,
		0,0,0,1
		);
	Mat4f zRotation = Mat4f(
		cos(angles.z()), -sin(angles.z()), 0, 0,
		sin(angles.z()), cos(angles.z()), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);
	return xRotation*yRotation*zRotation;
}