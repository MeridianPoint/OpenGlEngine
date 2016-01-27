#ifndef COLLSION_DETECTION_H_
#define COLLSION_DETECTION_H_

//#include "stdafx.h"

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();

	bool SphereCollision(BoundingSphere *pSphere1, BoundingSphere *pSphere2); //sphere to sphere collison
	//bool SpherePlaneCollision(BoundingSphere *pSphere, PlaneBounding *pPlane);  //sphere to plane collision
	bool AABBCollision();
};

#endif //COLLSION_DETECTION_H_