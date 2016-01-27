#include "stdafx.h"
#include "Physical_Force.h"


Physical_Force::Physical_Force()
{
}


Physical_Force::~Physical_Force()
{
}


Physical_Force & Physical_Force::operator+(const Physical_Force & rhs){
	Vec3f rhsVector = rhs.getIntegratedVector();
	return Physical_Force((direction*intensity + rhsVector));
}
Physical_Force & Physical_Force::operator-(const Physical_Force & rhs){
	Vec3f rhsVector = rhs.getIntegratedVector();
	return Physical_Force((direction*intensity - rhsVector));
}

Physical_Force & Physical_Force::operator+=(const Physical_Force rhs){
	Vec3f rhsVector = rhs.getIntegratedVector();
	Vec3f UnifiedVector = direction*intensity + rhsVector;
	Physical_Force *temp = new Physical_Force(UnifiedVector);
	direction = temp->GetDirection();
	intensity = temp->GetIntensity();
	return *this;
}

Physical_Force & Physical_Force::operator-=(const Physical_Force  rhs){
	Vec3f rhsVector = rhs.getIntegratedVector();
	Vec3f UnifiedVector = direction*intensity - rhsVector;
	Physical_Force *temp = new Physical_Force(UnifiedVector);
	direction = temp->GetDirection();
	intensity = temp->GetIntensity();
	return *this;
}

Acceleration & Physical_Force::operator/(const float mass){
	return Acceleration(direction*intensity / mass);
}