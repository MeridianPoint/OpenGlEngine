#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_
//#include "stdafx.h"
class Interpolation
{
public:
	Interpolation();
	~Interpolation();

	float LinearInterpolation(float x, float y, float step);
	Vec3f LinearInterpolation(Vec3f x, Vec3f y, float step);
	Quaternion LinearInterpolation(Quaternion x, Quaternion y, float step);

	//B-spline interpolation overridens
	float BSplineInterpolation(float x1, float x2, float x3, float x4, float step);
	Vec3f BSplineInterpolation(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step);
	Fixed_Angle BSplineInterpolation(Fixed_Angle x1, Fixed_Angle x2, Fixed_Angle x3, Fixed_Angle x4, float step);
	Quaternion BSplineInterpolation(Quaternion &q1, Quaternion &q2, Quaternion &q3, Quaternion &q4, float step);

	float Catmull_RomInterpolation(float x1, float x2, float x3, float x4, float step);
	Vec3f Catmull_RomInterpolation(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step);
	Fixed_Angle Catmull_RomInterpolation(Fixed_Angle x1, Fixed_Angle x2, Fixed_Angle x3, Fixed_Angle x4, float step);
	Quaternion Catmull_RomInterpolation(Quaternion &q1, Quaternion &q2, Quaternion &q3, Quaternion &q4, float step);


	//get accelerate
	float BSplineInterpolationDeprivative(float x1, float x2, float x3, float x4, float step);
	Vec3f BSplineInterpolationDeprivative(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step);

	float Catmull_RomInterpolationDeprivative(float x1, float x2, float x3, float x4, float step);
	Vec3f Catmull_RomInterpolationDeprivative(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step);


};
#endif