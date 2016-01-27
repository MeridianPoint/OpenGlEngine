#ifndef PATHFOLLOWCONTROLLER_H_
#define PATHFOLLOWCONTROLLER_H_
#include "KeyFrameController.h"


class PathFollowController :
	public KeyFrameController
{
private:
	Vec3f InitialDirection;
	Mat4f cur_Rotation;
	Vec3f cur_speed; //speed

	Mat4f VectorRotation(Vec3f Prev, Vec3f Post); //get the rotation from two vectors
public:
	PathFollowController();
	~PathFollowController();

	void AddKeyframe(float time, Vec3f position, Interp_Type InterType); //addKeyframe By 
	bool Update(float time);
	Vec3f getSpeed(float time); //get speed at time
};

#endif