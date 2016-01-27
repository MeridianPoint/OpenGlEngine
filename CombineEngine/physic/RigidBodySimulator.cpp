#include "stdafx.h"
#include "RigidBodySimulator.h"


RigidBodySimulator::RigidBodySimulator()
{
	haveGravity = false;
	isCollide = false;
}


RigidBodySimulator::~RigidBodySimulator()
{
}


void RigidBodySimulator::Update(float time){  //update 
	//dt = 0.12;
	double frametime = time - current_time;
	current_time = time;
	accumulator += frametime;
	//time step
	while (accumulator>=dt)
	{
		//
		Simulate();
		accumulator -= dt;
	}	
}

void RigidBodySimulator::Simulate(){
	//
	//check item number
	if (pObjectList.size() == 0 || pForceList.size() == 0){ //not enough items
		//cannot preceed
		std::cerr << "not enough object/force!" << std::endl;
	}

	else{               // able to simulate
		//traverse objects
		for (auto item : pObjectList){
			//traverse forces
			isCollide = false;
			//collision detection
			for (auto other_item : pObjectList){
				
				if (other_item == item) //same item
					continue;
				else{
					//check coll8ison 
					if (CheckObjectCollision(item, other_item)){
						//handle collision
						HandleCollision(item, other_item);
						isCollide = true;
					}
				}
			}//end travere other objects

			//sumarize all forces
			//if (item->getALLForces().size() == 0){ //check if no force apply
			//	continue;
			//}
			
			std::vector<Physical_Force*>forces = item->getALLForces();
			Physical_Force totalForce = *forces[0];
			if (forces.size() > 1){
				for (int i = 0; i < forces.size(); i++){
					if (i = 0){
						continue;
					}
					totalForce += *forces[i];
				}
			}
			
			//if (haveGravity){ //gravity applied
			//	totalForce += Physical_Force(Vec3f(0.0, 0.0, -9.8)*item->GetMass());
			
			//for (auto force : item->getALLForces()){
			//	//
			//	totalForce += *force;
			//}
			//update accleration ///////////////////////
			
			if (true/*!isCollide*/){  //applyforce only when no collision
				Acceleration acclerate = Acceleration(&totalForce, item->GetMass());

				//update velocity ////////////////////////////
				Vec3f inspedct = (acclerate*dt).getunifiedVector();
				Velocity vincre = acclerate*dt;
				//Velocity vincre = Velocity(inspedct);
				//Velocity i = item->GetVelovity() + vincre;
				item->SetVelocity(item->GetVelovity() + vincre);
			}
			

			//update transition //////////////////////////////////
			Vec3f dis = item->GetVelovity().getunifiedVector()*dt;
			//item->Translate(item->GetVelovity()*dt);
			item->Translate(dis);
			item->Rotation(0.5);
			
		}
	}
}

bool RigidBodySimulator::CheckObjectCollision(Physical_Object * first, Physical_Object * last){
	//

		//collisionHandler.SphereCollision(first->GetboundingVolume(), last->GetboundingVolume());
		//
		//collisionHandler.SphereCollision(first->GetVolumeType(),last->GetVolumeType());
		/*Physical_Force *collisionforce = new Physical_Force();
		first->AddForce(collisionforce);
		last->AddForce(-collisionforce);*/
	Vec3f disVector = first->getPosition() - last->getPosition();
		float distance = (first->getPosition() - last->getPosition()).length();
		float radius = first->GetBoudningSphereRadius();
		if (distance <= first->GetBoudningSphereRadius() + last->GetBoudningSphereRadius()){
			return true;
		}
		else{
			//if (disVector)
			return false;
		}
			

}


void RigidBodySimulator::AddObject(Physical_Object * pObject){
	pObjectList.push_back(pObject);
}
void RigidBodySimulator::AddForceTo(Physical_Force *force, unsigned int index){
	//
	if (index <= pObjectList.size() - 1){
		pObjectList[index]->AddForce(force);
		if (std::count(pForceList.begin(), pForceList.end(), force) == 0){//check if force exist
			//
			pForceList.push_back(force);
		}
	}
	else{
		//no enough item
	}
}


void RigidBodySimulator::SetTimegap(float TimeGap){
	dt = TimeGap;
}
void RigidBodySimulator::SetFrameRate(unsigned int fps){ //set time gap
	dt = 1 / (double)fps;
}

void RigidBodySimulator::SetStartTime(double time){
	current_time = time;
}

void RigidBodySimulator::CalculateCollisionForce(Physical_Object * first, Physical_Object * last){ //calculate the force of the collison
	//
	Vec3f momentumFirstBefore = first->GetVelovity()*first->GetMass();
	Vec3f momentumSecondBefore = last->GetVelovity()*last->GetMass();
	/*Vec3f momentumFirstAtfer = 
	Vec3f momentumSecondAfter =*/
}

void RigidBodySimulator::HandleCollision(Physical_Object * first, Physical_Object * last){
	//
	Vec3f momentumFirstBefore = first->GetVelovity()*first->GetMass();
	Vec3f momentumSecondBefore = last->GetVelovity()*last->GetMass();

	Vec3f dis = first->getPosition() - last->getPosition();
	dis.normalize();

	float firstAfterSpeed = first->GetVelovity().getunifiedVector().length()*(first->GetMass() - last->GetMass()) / (first->GetMass() + last->GetMass()) + last->GetVelovity().getunifiedVector().length()*(last->GetMass() * 2) / (first->GetMass() + last->GetMass());
	float lastAfterSpeed = last->GetVelovity().getunifiedVector().length()*(first->GetMass() - last->GetMass()) / (first->GetMass() + last->GetMass()) + first->GetVelovity().getunifiedVector().length()*(first->GetMass() * 2) / (first->GetMass() + last->GetMass());

	Vec3f firstAftervelocity = (first->GetVelovity().getunifiedVector() - dis*first->GetVelovity().getunifiedVector().dot(dis) * 2).getNorm()*firstAfterSpeed;
	Vec3f lastAftervelocity = (last->GetVelovity().getunifiedVector() - dis*last->GetVelovity().getunifiedVector().dot(dis) * 2).getNorm()*lastAfterSpeed;

	first->SetVelocity(Velocity(firstAftervelocity));
	last->SetVelocity(Velocity(lastAftervelocity));
}

//bool RigidBodySimulator::CheckPlaneCollision(Physical_Object *object, Physical_Plane *Plane){
//	//
//	Vec3f distanceVector = object->getPosition() - Plane->getPosition();
//	float distance = Plane->getNormal().dot(distanceVector);
//	if (distance <= object->GetBoudningSphereRadius())
//		return true;
//	else
//		return false;
//}

//void RigidBodySimulator::HandlePlaneColiison(Physical_Object *object, Physical_Plane *Plane){
//	Vec3f norm=Plane->getNormal();
//	Vec3f inverse = norm * 2 - object->GetVelovity().getDirection();
//	Vec3f velocityAfter = object->GetVelovity().getunifiedVector() - norm*object->GetVelovity().getunifiedVector().dot(norm) * 2;
//		//
//	object->SetVelocity(velocityAfter);
//}

void RigidBodySimulator::ApplyGravity(){
	haveGravity = true;
}

//void RigidBodySimulator::AddPlane(Physical_Plane* plane){
//	PlaneList.push_back(plane);
//}