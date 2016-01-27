//Spatial.h
//Base class for all objects that exist take up space

#ifndef SPATIAL_H_
#define SPATIAL_H_


#include "Object.h"
//#include "stdafx.h"
class Spatial :
	public Object
{
public:
	//friend class Transformation;
	Transformation World; //World transformation
	Transformation Local; //Local transformation
	Vec3f Position;
	Spatial *pParent; //parent
	Mat4f JointMatrix;
public:
	Spatial();
	virtual ~Spatial();
	
	void *SetParent(Spatial *pParent){ pParent = pParent; } //set Parent
protected:
	Spatial *GetParent(){ return pParent; }  //set 
	void SetJointPosition(Vec3f ParentSpacePosition, Mat4f ParentSpaceRotation);

	//update status
	//virtual void UpdateWorldData(double time);
};

#endif