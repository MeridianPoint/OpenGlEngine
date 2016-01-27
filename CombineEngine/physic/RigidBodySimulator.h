#ifndef RIGIDBODYSIMULATOR_H_
#define RIGIDBODYSIMULATOR_H_

#include "stdafx.h"

class RigidBodySimulator
{
private:
	//Velocity * initialVelocity;
	std::vector<Physical_Object*> pObjectList;
	std::vector<Physical_Force *> pForceList;
	//std::vector<Physical_Plane *> PlaneList;

	CollisionDetection collisionHandler;


	//time contorl parameters
	double accumulator = 0.0;
	double current_time;
	double newtime;
	unsigned int step; //time  step
	float dt;

	bool haveGravity;
	bool isCollide;

public:
	RigidBodySimulator();
	~RigidBodySimulator();



	void Update(float time); //simulation
	void Simulate(); //runsimulation

	//time control
	void SetInitalTime(double time);

	void CheckCollision();
	bool CheckObjectCollision(Physical_Object * first, Physical_Object * last); //handle collision between two objects
	void CalculateCollisionForce(Physical_Object * first, Physical_Object * last); //calculate the force of the collison
	void HandleCollision(Physical_Object * first, Physical_Object * last); 

	//bool CheckPlaneCollision(Physical_Object *object, Physical_Plane *Plane);
	//void HandlePlaneColiison(Physical_Object *object, Physical_Plane *Plane);

	///member access
	void SetTimegap(float TimeGap);
	void SetFrameRate(unsigned int fps); //set time gap
	void SetStartTime(double time); //set start up time

	void AddObject(Physical_Object * pObject);
	//void AddPlane(Physical_Plane* plane);
	void AddForceTo(Physical_Force *force, unsigned int index);
	void AddUniversalForce(Physical_Force *force);
	void ApplyGravity();
};

#endif