//class to define force
#ifndef PHYSICAL_FORCE_H_
#define PHYSICAL_FORCE_H_

#include "stdafx.h"

class Physical_Force
{
protected:
	float intensity;
	Vec3f direction; //normalized


	//
	
public:
	Physical_Force();
	~Physical_Force();

	Physical_Force(float Intensity, Vec3f normalizeDirection) :intensity(Intensity), direction(normalizeDirection){}
	Physical_Force(Vec3f unifiedVector) :intensity(unifiedVector.length()), direction(unifiedVector.getNorm()){}

	//calculation
	Physical_Force &  operator+(const Physical_Force & rhs);
	Physical_Force &  operator-(const Physical_Force & rhs);
	//Physical_Force & operator*(const float & rhs);
	//Physical_Force & operator/(const float & rhs);

	Physical_Force & operator+=(const Physical_Force  rhs);
	Physical_Force & operator-=(const Physical_Force  rhs);

	//Physical_Force & operator*(float scale);
	//Physical_Force & operator/(float scale);

	friend class Acceleration;
	Acceleration & operator/(const float mass);


	//get set
	void setIntensity(float fIntensity){ intensity = fIntensity; }
	Vec3f GetDirection(){ return direction; }
	float GetIntensity(){ return intensity; }
	Vec3f getIntegratedVector() const{
		Vec3f i = direction;
		Vec3f UnifiedVector = i*intensity;
		return UnifiedVector;
	}
	                                                                                                                                          
};

#endif //PHYSICAL FORCE_H_