/*Transformation.h
* base class to provide virtual functions and parameters for transformation
*
*/
#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_
#include "stdafx.h"
//#include "Mat4.h"

class Transformation
{
public:
	//parent matrix
	Mat4f Parent_Matrix;
	//record translate actions
	Mat4f Translate_Matrix;
	//record rotation actions
	Mat4f Rotation_Matrix;
	//record translate actions
	Mat4f Scale_Matrix;
	//record Transformation
	Mat4f Transformation_Matrix;

	//pivot 
	Vec3f pivot;
	Mat4f pivotSpace;
public:
	Transformation();
	//transformation
	/*virtual void Translate(Vec3f offsetVector)=0;
	virtual void Rotate(Vec3f angles, Vec3f axis)=0;
	virtual void Scale(Vec3f scaleVector)=0;
	virtual void Reset() = 0;*/
	//set get
	void setPivot(Vec3f PivotPosition){
		pivot = PivotPosition;
	}
	void setPivot(Vec3f PivotPosition, Mat4f PivotSpace){
		pivot = PivotPosition;
		pivotSpace = PivotSpace;
	}
	//void set

	///virtual transformation functions

	virtual void Translate(Vec3f offsetVector);
	virtual void Rotate(Vec3f angles, Vec3f axis);
	//virtual void Rotate(Quaternion rQuaternion);
	//virtual void Rotate(Eular_Angle rAngles);

	virtual void Scale(Vec3f scaleVector);
	virtual void Reset();
	virtual void Initate();  //set all matrix to identity
	virtual void resetTransformationMatrix();

	virtual ~Transformation();

	
	Vec3f HomeGenTransform(Vec3f vector, Mat4f TransformMatrix){  //Homogenius transformation(3d to 4d)
		Vec4f Homo_vector(vector.x(), vector.y(), vector.z(), 1);
		Homo_vector = TransformMatrix*Homo_vector;
		Vec3f result_vector = Vec3f(Homo_vector.x(), Homo_vector.y(), Homo_vector.z());
		return result_vector;
	}

	//check status
	bool IsIdentity();
	bool IsUniformScale();
};

#endif 