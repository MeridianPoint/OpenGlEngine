#include "stdafx.h"
#include "Pivot.h"


Pivot::Pivot()
{
}


Pivot::~Pivot()
{
}

void Pivot::Translate(Vec3f translateVector){
	//
	Mat4f transMat = Mat4f(
		1.0f, 0.0f, 0.0f, translateVector.x(),
		0.0f, 1.0f, 0.0f, translateVector.y(),
		0.0f, 0.0f, 1.0f, translateVector.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		);
}
//void Pivot::Rotation(Vec3f Angles){
//	//Rotation
//	World.Rotation_Matrix=
//}

void Pivot::Rotation(Mat4f RotationMat){
	World.Rotation_Matrix = RotationMat;
}

void Pivot::AlignToWorld(){
	//
	World.Rotation_Matrix = Mat4f(
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
		);
}