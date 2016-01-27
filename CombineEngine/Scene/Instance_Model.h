//Instance.h
//Instance of model
#include "Spatial.h"
#ifndef INSTANCE_MODEL_H_
#define INSTANCE_MODEL_H_
class Instance_Model :
	public Model
{
private:
	Model *ModelData;

public:
	Instance_Model();
	Instance_Model(Model *pModelReference);
	~Instance_Model();

	void Translate(Vec3f TranslateVector);
	void Rotation();
	void ClassicDraw(int drawType, int uv_type);
};
#endif // !INSTANCE_MODEL_


