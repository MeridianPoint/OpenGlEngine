#ifndef VELOCITY_H_
#define VELOCITY_H_

//#include "stdafx.h"

class Acceleraion;

class Velocity
{
private:
	Vec3f direction;
	float magnitude;
public:
	Velocity();
	Velocity(Vec3f unifiedVector);
	~Velocity();

	void Update(Acceleraion *pAcceleration, float fDuranceTime);

	Velocity& operator+ (const Velocity &rhs);
	Velocity& operator- (const Velocity &rhs);
	Velocity& operator> (const Velocity &rhs);

	Vec3f& operator*(const float time); //distance 

	//set
	void SetDirection(Vec3f direc){ direction = direc; }
	void SetMagnitude(float magn){ magnitude = magn; }
	Vec3f getunifiedVector() const;
	float getMagnitude(){ return magnitude; }
	Vec3f getDirection(){ return direction; }
};

class Acceleration
{
private:
	Vec3f direction;
	float magnitude;
public:
	Acceleration();
	Acceleration(Physical_Force* pTotalForce, float mass);
	Acceleration(Vec3f unifiedVector);
	~Acceleration();

	//calculation
	/*Acceleration& operator*(const float Scale);
	Acceleration& operator/(const float Scale);*/

	friend class Velocity;
	Velocity & operator*(const float time);

};


//Acceleration operator


inline Velocity& Velocity::operator+ (const Velocity  &rhs){
	//
	Vec3f rhsVector = rhs.getunifiedVector();
	Velocity *result = new Velocity(direction*magnitude + rhsVector);
	return *result;
}

inline Velocity& Velocity::operator- (const Velocity &rhs){
	//
	Vec3f rhsVector = rhs.getunifiedVector();
	Velocity result = Velocity(direction*magnitude - rhsVector);
	return result;
}


inline Vec3f& Velocity::operator*(const float time){
	//
	Vec3f distance = direction*magnitude*time;
	return distance;
}


inline Velocity & Acceleration::operator*(const float time){
	//
	Vec3f i = direction*magnitude*time;
	Velocity *accerlated = new Velocity(i);
	return *accerlated;
}


#endif

