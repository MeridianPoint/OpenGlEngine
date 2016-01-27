//Crowd.h
//control crowd animation
#ifndef CROWD_H_
#define CROWD_H_
class Crowd
{
private:
	std::vector<Boid*> pboids;
	Boid *pLeader; //leader to 
	float repulsiveScale; //scale of refulsive force

	//update 
	double dt;
	double current_time;
	double new_time;
	double accumulator;

	Vec3f getCenter(std::vector<Vec3f> &Positions);
public:
	Crowd();
	~Crowd();
	//time control
	void StartTime(double time){ current_time = time; }
	void SetFrameRate(unsigned int fps){ dt = 1 / (double)fps; }

	//initaltion
	void AlignToLeaderVelocity(float influence); //align the leader's velocity

	//update, control
	void Update(double time);
	void CrowdControl();

	//set get
	void AddBoid(Boid* pNewBoid);
	void SelectLeader(unsigned int index);
	void clear();
};
#endif // !1


