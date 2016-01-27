#include "stdafx.h"
#include "Physical_Object.h"


Physical_Object::Physical_Object()
{
}


Physical_Object::~Physical_Object()
{
	delete object;
}

Physical_Object::Physical_Object(Model *pModel, float fmass, Velocity initialVelocity){
	//
	object = pModel;
	mass = fmass;
	velocity = initialVelocity;
	GetBoudingSphere();
	BoundingSphere->SetPosition(object->GetPosition());

}

void Physical_Object::ComputeBoundingVolume(){
	//
	if (object != NULL){
		//
		switch (vt){
		case VT_AABB: break;
		case VT_SPHERE: break;
		}
	}
	else{
		//
		std::cerr << "No object aligned" << std::endl;
	}
}

void Physical_Object::Translate(Vec3f TranslateVector){
	//
	if (object != NULL){
		//
		object->Translate(TranslateVector);
		UpdateBoudingSphere();
	}
}
void Physical_Object::Rotation(float angle){
	//
	//object->Rotation(angle，Vec3f(0.0,0.0,1.0));
	object->Rotation(angle, Vec3f(0.0, .0, 1.0));
}

void Physical_Object::AddForce(Physical_Force* force){
	//
	pForces.push_back(force);
}

std::vector<Physical_Force*> Physical_Object::getALLForces(){
	//
	return pForces;
}

void Physical_Object::GetBoudingSphere(){
	//BoundingSphere = object->CalculateBoudingSphere();
}

Vec3f Physical_Object::getPosition(){
	//
	return object->GetPosition();
}

void Physical_Object::UpdateBoudingSphere(){
	//
	BoundingSphere->SetPosition(object->GetPosition());
	int i = 1;
}

float Physical_Object::GetBoudningSphereRadius(){
	//
	return BoundingSphere->GetRadius();
}