#ifndef PHYSICAL_OBJECT_H_
#define PHYSICAL_OBJECT_H_
//#include "stdafx.h"
class Physical_Object
{
protected:
	Model * object;
	std::vector<Physical_Force*> pForces;
	float mass;
	Velocity velocity;
	VolumeType vt;
	BoundingSphere *BoundingSphere;
public:
	Physical_Object();
	Physical_Object(Model *pModel, float fmass, Velocity initialVelocity);
	~Physical_Object();

	//
	void ComputeBoundingVolume();


	//set get ///////////////////////////////////
	void AddForce(Physical_Force* force);
	std::vector<Physical_Force*> getALLForces();

	void SetMass(float Mass){ mass = Mass; };
	float GetMass(){ return mass; }
	
	void SetVelocity(Velocity v){ velocity = v; }
	Velocity GetVelovity(){ return velocity; }
	VolumeType GetVolumeType(){ return vt; }
	Vec3f getPosition();
	//bounding sphere
	Abstract_BoundingBox GetboundingVolume();
	void GetBoudingSphere(); //compute bounding sphere for 
	void UpdateBoudingSphere();
	float GetBoudningSphereRadius();

	//transformation
	void Translate(Vec3f TranslateVector);
	void Rotation(float angle);
};

#endif //PHYSICAL_OBJECT_H_