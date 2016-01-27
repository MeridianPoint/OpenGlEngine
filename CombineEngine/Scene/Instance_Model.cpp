#include "stdafx.h"
#include "Instance_Model.h"


Instance_Model::Instance_Model()
{
}


Instance_Model::~Instance_Model()
{
}

Instance_Model::Instance_Model(Model *pModelReference){
	ModelData = pModelReference;
	World.Initate();
	Local.Initate();
}

void Instance_Model::Translate(Vec3f TranslateVector){
	Mat4f transMat = Mat4f(
		1.0, 0.0, 0.0, TranslateVector.x(),
		0.0, 1.0, 0.0, TranslateVector.y(),
		0.0, 0.0, 1.0, TranslateVector.z(),
		0.0, 0.0, 0.0, 1.0
		);
	World.Translate_Matrix = transMat*World.Translate_Matrix;
	//translate center
	World.Transformation_Matrix = transMat*World.Transformation_Matrix;
	m_center = HomoGenTransformation(transMat, m_center);
}
void Instance_Model::Rotation(){
}
void Instance_Model::ClassicDraw(int drawType, int uv_type){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(World.Transformation_Matrix.ToArray());
	ModelData->RawDraw(drawType, uv_type);
}