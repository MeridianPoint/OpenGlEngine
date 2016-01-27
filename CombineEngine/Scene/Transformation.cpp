#include "stdafx.h"
#include "Transformation.h"


Transformation::Transformation()
{
	Translate_Matrix.Identity();
	Rotation_Matrix.Identity();
	Scale_Matrix.Identity();
}

void Transformation::Translate(Vec3f offsetVector){
	Mat4f Trans_Mat(
		1.0f, 0.0f, 0.0f, offsetVector.x(),
		0.0f, 1.0f, 0.0f, offsetVector.y(),
		0.0f, 0.0f, 1.0f, offsetVector.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		);
}
void Transformation::Rotate(Vec3f angles, Vec3f axis){
}
void Transformation::Scale(Vec3f scaleVector){
	Mat4f Scale_Mat(
		scaleVector.x(), 0.0f, 0.0f, 0.0f,
		0.0f, scaleVector.y(), 0.0f, 0.0f,
		0.0f, 0.0f, scaleVector.z(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
}
void Transformation::Reset(){
	Mat4f Identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	Translate_Matrix = Identity;
	Rotation_Matrix = Identity;
	Scale_Matrix = Identity;
	Transformation_Matrix = Identity;
}

void Transformation::Initate(){
	Mat4f Identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	Translate_Matrix = Identity;
	Rotation_Matrix = Identity;
	Scale_Matrix = Identity;
	Transformation_Matrix = Identity;
}

Transformation::~Transformation()
{
}

void Transformation::resetTransformationMatrix(){
	//
	Transformation_Matrix = Translate_Matrix*Rotation_Matrix*Scale_Matrix;
}