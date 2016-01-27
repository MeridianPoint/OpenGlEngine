#include "stdafx.h"
#include "Interpolation.h"


Interpolation::Interpolation()
{
}


Interpolation::~Interpolation()
{
}


float Interpolation::LinearInterpolation(float x, float y, float step){
	if (step<1.0f&&step>0.0f)
	{
		float lower = x - y ? y : x;
		return lower + step*abs(x - y);
	}
	else
	{
		//throw 
		return 0;
	}
}

Vec3f Interpolation::LinearInterpolation(Vec3f x, Vec3f y, float step){
	if (step<1.0f&&step>0.0f)
	{
		return Vec3f(LinearInterpolation(x.x(), y.x(), step), LinearInterpolation(x.y(), y.y(), step), LinearInterpolation(x.z(), y.z(), step));
	}
	else
	{
		//throw 
		return Vec3f(0.0,0.0,0.0);
	}
}

float Interpolation::BSplineInterpolation(float x1, float x2, float x3, float x4, float step){
	//
	Mat4f Spline_Mat = Mat4f(
		-0.166f,0.5f,-0.5f,0.166f,
		0.5f,-1.0f,0.5f,0.0f,
		-0.5f,0.0f,0.5f,0.0f,
		0.166f,0.666f,0.166f,0.0f
		);
	Vec4f timeVector = Vec4f(step*step*step, step*step, step, 1);
	T_Vec4f tvPoints = T_Vec4f(x1, x2, x3, x4);
	return timeVector*Spline_Mat*tvPoints;
}

Vec3f Interpolation::BSplineInterpolation(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step){
	Vec3f vResult = Vec3f(Interpolation::BSplineInterpolation(x1.x(), x2.x(), x3.x(), x4.x(), step), Interpolation::BSplineInterpolation(x1.y(), x2.y(), x3.y(), x4.y(), step), Interpolation::BSplineInterpolation(x1.z(), x2.z(), x3.z(), x4.z(), step));
	return vResult;
}


Fixed_Angle Interpolation::BSplineInterpolation(Fixed_Angle x1, Fixed_Angle x2, Fixed_Angle x3, Fixed_Angle x4, float step){
	Vec3f vResult = Interpolation::BSplineInterpolation(x1.getAngles(), x2.getAngles(), x3.getAngles(), x4.getAngles(), step);
	return Fixed_Angle(vResult);
}

Quaternion Interpolation::BSplineInterpolation(Quaternion &q1, Quaternion &q2, Quaternion &q3, Quaternion &q4, float step){
	Quaternion qResult = Quaternion(Interpolation::BSplineInterpolation(q1.W(), q2.W(), q3.W(), q4.W(), step), Interpolation::BSplineInterpolation(q1.X(), q2.X(), q3.X(), q4.X(), step), Interpolation::BSplineInterpolation(q1.Y(), q2.Y(), q3.Y(), q4.Y(), step), Interpolation::BSplineInterpolation(q1.Z(), q2.Z(), q3.Z(), q4.Z(), step));
	return qResult;
}




//////catmull rom /////////////////////
float Interpolation::Catmull_RomInterpolation(float x1, float x2,float x3,float x4, float step){
	//
	Mat4f Catmul_Rome = Mat4f(
		-0.5,1.5,-1.5,0.5,
		1,-2.5,2,-0.5,
		-0.5,0,0.5,0,
		0,1,0,0
		);
	Vec4f timeVector = Vec4f(step*step*step, step*step, step, 1);
	T_Vec4f tvPoints = T_Vec4f(x1, x2, x3, x4);
	return timeVector*Catmul_Rome*tvPoints;
}

Vec3f Interpolation::Catmull_RomInterpolation(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step){
	Vec3f vResult = Vec3f(Interpolation::Catmull_RomInterpolation(x1.x(), x2.x(), x3.x(), x4.x(), step), Interpolation::Catmull_RomInterpolation(x1.y(), x2.y(), x3.y(), x4.y(), step), Interpolation::Catmull_RomInterpolation(x1.z(), x2.z(), x3.z(), x4.z(), step));
	return vResult;
}

Fixed_Angle Interpolation::Catmull_RomInterpolation(Fixed_Angle x1, Fixed_Angle x2, Fixed_Angle x3, Fixed_Angle x4, float step){
	//
	Vec3f vResult = Interpolation::Catmull_RomInterpolation(x1.getAngles(), x2.getAngles(), x3.getAngles(), x4.getAngles(), step);
	return Fixed_Angle(vResult);
}

Quaternion Interpolation::Catmull_RomInterpolation(Quaternion &q1, Quaternion &q2, Quaternion &q3, Quaternion &q4, float step){
	Quaternion qResult = Quaternion(Interpolation::Catmull_RomInterpolation(q1.W(), q2.W(), q3.W(), q4.W(), step), Interpolation::Catmull_RomInterpolation(q1.X(), q2.X(), q3.X(), q4.X(), step), Interpolation::Catmull_RomInterpolation(q1.Y(), q2.Y(), q3.Y(), q4.Y(), step), Interpolation::Catmull_RomInterpolation(q1.Z(), q2.Z(), q3.Z(), q4.Z(), step));
	return qResult;
}


//get accelerate ///////////////////////////////////////////////////////////////
float Interpolation::BSplineInterpolationDeprivative(float x1, float x2, float x3, float x4, float step){
	//
	//Mat4f Spline_Mat = Mat4f(
	//	-0.166f, 0.5f, -0.5f, 0.166f,
	//	0.5f, -1.0f, 0.5f, 0.0f,
	//	-0.5f, 0.0f, 0.5f, 0.0f,
	//	0.166f, 0.666f, 0.166f, 0.0f
	//	);
	Mat4f Spline_Mat_dep = Mat4f(
		0.0f,-0.5f,1.0f,-0.5f,
		0.0f,1.5f,-2.0f,0.5f,
		0.0f,-1.5f,0.0f,0.5f,
		0.0f,0.5f,1.333f,0.166f
		);
	Vec4f timeVector = Vec4f(step*step*step, step*step, step, 1);
	T_Vec4f tvPoints = T_Vec4f(x1, x2, x3, x4);
	return timeVector*Spline_Mat_dep*tvPoints;
}
Vec3f Interpolation::BSplineInterpolationDeprivative(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step){
	//
	return Vec3f(BSplineInterpolationDeprivative(x1.x(), x2.x(), x3.x(), x4.x(), step), BSplineInterpolationDeprivative(x1.y(), x2.y(), x3.y(), x4.y(), step), BSplineInterpolationDeprivative(x1.z(), x2.z(), x3.z(), x4.z(), step));
}

float Interpolation::Catmull_RomInterpolationDeprivative(float x1, float x2, float x3, float x4, float step){
	//
	Mat4f Catmul_Rome_dep = Mat4f(
		0.0f, -1.5f, 3.0f, -1.5f,
		0.0f, 3.0f, -5.0f, 2.0f,
		0.0f, -1.5f, 0.0f, 0.5f,
		0.0f, 3.0f, .0f, .0f
		);
	Vec4f timeVector = Vec4f(step*step*step, step*step, step, 1);
	T_Vec4f tvPoints = T_Vec4f(x1, x2, x3, x4);
	return timeVector*Catmul_Rome_dep*tvPoints;
}
Vec3f Interpolation::Catmull_RomInterpolationDeprivative(Vec3f x1, Vec3f x2, Vec3f x3, Vec3f x4, float step){
	//
	return Vec3f(Catmull_RomInterpolationDeprivative(x1.x(), x2.x(), x3.x(), x4.x(), step), Catmull_RomInterpolationDeprivative(x1.y(), x2.y(), x3.y(), x4.y(), step), Catmull_RomInterpolationDeprivative(x1.z(), x2.z(), x3.z(), x4.z(), step));
}