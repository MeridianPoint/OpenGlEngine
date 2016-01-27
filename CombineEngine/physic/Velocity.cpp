#include "stdafx.h"
#include "Velocity.h"


Velocity::Velocity()
{
}

Velocity::Velocity(Vec3f unifiedVector){
	direction = unifiedVector.getNorm();
	magnitude = unifiedVector.length();
}

Velocity::~Velocity()
{
}




Vec3f Velocity::getunifiedVector() const{
	//
	Vec3f unified = direction;
	return unified*magnitude;
}


///////Acceleration functions /////////////////////////////////////
Acceleration::Acceleration(){
}

Acceleration::Acceleration(Physical_Force* pTotalForce, float mass){
	//
	Vec3f unifiedvector = pTotalForce->getIntegratedVector()/mass;
	direction = unifiedvector.getNorm();
	magnitude = unifiedvector.length();
}

Acceleration::Acceleration(Vec3f unifiedVector){
	//
	direction = unifiedVector.getNorm();
	magnitude = unifiedVector.length();
}

Acceleration::~Acceleration(){
}

