#include "stdafx.h"
#include "Crowd.h"


Crowd::Crowd()
{
	repulsiveScale = 0.001;
}


Crowd::~Crowd()
{
	while (pboids.size() > 0){
		//delete 
		Boid* temp = pboids[pboids.size()-1];
		pboids.pop_back();
		delete temp;
	}
}

void Crowd::AddBoid(Boid* pNewBoid){
	pboids.push_back(pNewBoid);
}
void Crowd::SelectLeader(unsigned int index){
	pLeader = pboids[index];
}

void Crowd::AlignToLeaderVelocity(float influence){
	for (auto boid : pboids){
		if (boid == pLeader)
			continue;
		boid->alignVelocity(boid->getVelocity()*(1 - influence) + pLeader->getVelocity()*influence);
	}
}

void Crowd::Update(double time){
	//
	double frametime = time - current_time;
	current_time = time;
	accumulator += frametime;
	//time step
	while (accumulator >= dt)
	{
		//
		CrowdControl();
		accumulator -= dt;
	}
}
void Crowd::CrowdControl(){
	
	//parameters for
	std::vector<Boid*> neighboors;
	std::vector<Vec3f> centers;
	Vec3f Reulsiveforce;
	Vec3f centerPosition;
	Vec3f CenteringVelocity;
	Vec3f neighboorVelocity;
	int notIgnoreCenter = 1;
	int count = 0;
	int travecount = 0;

	bool useForceField = false;

	for (auto Boid : pboids){ //traverse all boids
		//traverse other
		count = 0;
		notIgnoreCenter = 1;
		for (auto pBoid : pboids){
			useForceField = false;
			travecount = 0;
			if (Boid == pBoid){//check if the same object
				continue;
			}

			////////////////repulsize field
			if (Boid->ActiveForceField(pBoid)){ //check if repulsive feild is active
				if (!useForceField){ //initialize 
					Reulsiveforce = Boid->getRepulsiveAcceleration(pBoid);
				}
				else
					Reulsiveforce += Boid->getRepulsiveAcceleration(pBoid);
				useForceField = true;
			}
			
			////floack centering & velocity matching ///////////////////////////
			if (Boid->isNeighboor(pBoid)){ //check if new boid is in the neighborhood
				//velocity matching
				if (count == 0){ //initialize 
					neighboorVelocity = pBoid->getVelocity();
				}
				else{
					neighboorVelocity = neighboorVelocity +pBoid->getVelocity();
					neighboorVelocity = neighboorVelocity/2;
				}
					
				//floack centering
				neighboors.push_back(pBoid);
				centers.push_back(pBoid->getPosition());
				count++;
			}
		}
		//end of traverse others


		//calculate/////////////////////////////

		//forcefield 
		if (useForceField){
			Vec3f RepulsiveAcceleration = Reulsiveforce*repulsiveScale;
			Boid->alignVelocity(Boid->getVelocity() + RepulsiveAcceleration*dt*Boid->getForceFieldWeight());
		}

		if (neighboors.size() > 0){

		//floack centering
		
			centerPosition = getCenter(centers);
			Vec3f test = centerPosition - Boid->getPosition();
			if (test.length() == 0.0)
				notIgnoreCenter = 0;
			CenteringVelocity = (centerPosition - Boid->getPosition()).getNorm()*Boid->getVelocity().length();

			//velocity matching added

			Vec3f newVelocity;
			//update
			if (notIgnoreCenter){
				newVelocity = Boid->getVelocity()*Boid->getPreservingWeight() + CenteringVelocity*Boid->getFloackCenteringWeight()+ neighboorVelocity*Boid->getVeocityMatchingWeight();
			}
			else{ //ignore center
				newVelocity = Boid->getVelocity()*Boid->getPreservingWeight()  + neighboorVelocity*Boid->getVeocityMatchingWeight();
			}
			//Vec3f newVelocity = Boid->getVelocity()*Boid->getPreservingWeight() + CenteringVelocity*Boid->getFloackCenteringWeight()*(float)notIgnoreCenter + neighboorVelocity*Boid->getVeocityMatchingWeight();
			//Boid->Rotation(newVelocity);
			Boid->alignVelocity(newVelocity);
		}
		//update////////////////////////////////////
		Boid->Translate(Boid->getVelocity()*dt);
		//Boid->Rotation(Boid->getVelocity());
		//clean parameters
		neighboors.clear();
		centers.clear();
	}
}

Vec3f Crowd::getCenter(std::vector<Vec3f> &Positions){
	//check xmin
	auto x_min_elem = std::min_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.x() < s2.x();
	});
	float x_min = x_min_elem->x();

	auto x_max_elem = std::max_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.x() < s2.x();
	});
	float x_max = x_max_elem->x();
	//check ymin
	auto y_min_elem = std::min_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.y() < s2.y();
	});
	float y_min = y_min_elem->y();

	auto y_max_elem = std::max_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.y() < s2.y();
	});
	float y_max = y_max_elem->y();

	auto z_min_elem = std::min_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.z() < s2.z();
	});
	float z_min = z_min_elem->z();

	auto z_max_elem = std::max_element(Positions.begin(), Positions.end(), [](Vec3f const& s1, Vec3f const& s2)
	{
		return s1.z() < s2.z();
	});
	float z_max = z_max_elem->z();

	return Vec3f((x_min + x_max) / 2, (y_min + y_max) / 2, (z_min + z_max) / 2);
}

void Crowd::clear(){
	while (pboids.size() != 0){
		Boid *temp = pboids[pboids.size() - 1];
		pboids.pop_back();
		delete temp;
	}
	
}