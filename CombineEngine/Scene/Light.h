//light.h
//basic class for light creation
#ifndef LIGHT_H_
#define LIGHT_H_
#include "stdafx.h"
#include "Spatial.h"

enum light_type {LT_AMBIENT,LT_POINT, LT_SPOT,LT_DIRECTION};
enum Attenuation_type {NONE,INVERSE,INVERSE_SQUARE};

class Light:public Spatial
{
protected:
	Vec3f color;
	float Intensity;
	Vec3f Position;
	int light_type;

	//spot light
	float angle;
	Vec3f direction;
public:
	Light();
	Light(Vec3f Color, float Ie,Vec3f pos) :color(Color),Intensity(Ie),Position(pos){}
	//virtual void pass2Shader();
	virtual ~Light();
	//set/get functions
	void setColor(Vec3f Color){
		color = Color;
	}

	Vec3f getPosition(){
		return Position;
	}
	
	float getIntensity(){
		return Intensity;
	}
	Vec3f getColor(){
		return color;
	}

	int getType(){
		return light_type;
	}
};

class LightCreator
{
protected:
	Light *LightInstance;
public:
	LightCreator();
	Light *getLight(){
		return LightInstance;
	}
	virtual void CreateLight(Vec3f Color, float Ie, Vec3f pos){
		LightInstance = new Light(Color,Ie,pos);
	}
	virtual ~LightCreator();
};

#endif //LIGHT_H_