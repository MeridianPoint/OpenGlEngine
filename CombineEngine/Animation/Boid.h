
#ifndef BOID_H_
#define BOID_H_
#include "stdafx.h"
class Boid
{
private:
	Model *pModel; //model for pBoid
	Vec3f velocity;
	float NeighboorDistance; //distance of neighbor checking
	float BehaviorRate[4]; //weight for behavior : preserveing, force field, velocity matching,centering, sum up to one(perhaps?)
public:
	Boid();
	Boid(Model* model, Vec3f initVelocity);
	~Boid();

	//movement control
	void ForceField(Boid &pOther); //use forcefield
	void VelocityMatching(Boid &pOther);

	//get member
	Vec3f initeVelocity(Vec3f newVelocity); //set velocity--before simulation


	Vec3f SetNeighboorDistance(float dis);

	void alignVelocity(Vec3f newVelocity);
	Vec3f getPosition();
	Vec3f getVelocity();
	float Distance(Boid *pOther);
	float Distance_square(Boid *pOther);

	//control related
	bool isNeighboor(Boid *pOther); //check if target is neighboor
	bool ActiveForceField(Boid *pOther); //check if forcefield is needed;
	Vec3f getRepulsiveAcceleration(Boid *pOther);

	float getPreservingWeight(){ return BehaviorRate[0]; }
	float getForceFieldWeight(){ return BehaviorRate[1]; }
	float getVeocityMatchingWeight(){ return BehaviorRate[2]; }
	float getFloackCenteringWeight(){ return BehaviorRate[3]; }

	//transformation
	void Translate(Vec3f translateVector);
	void Rotation(Vec3f NewDirection);
	void SetWeights(float *weights);
};


#endif // !BOID_H_
