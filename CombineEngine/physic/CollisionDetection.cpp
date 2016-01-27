#include "stdafx.h"
#include "CollisionDetection.h"


CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}


bool CollisionDetection::SphereCollision(BoundingSphere *pSphere1, BoundingSphere *pSphere2){ //sphere to sphere collison
	float distance_square = (pSphere1->GetPos().x() - pSphere2->GetPos().x())*(pSphere1->GetPos().x() - pSphere2->GetPos().x()) + (pSphere1->GetPos().y() - pSphere2->GetPos().y())*(pSphere1->GetPos().y() - pSphere2->GetPos().y()) + (pSphere1->GetPos().z() - pSphere2->GetPos().z())*(pSphere1->GetPos().z() - pSphere2->GetPos().z());
	if ((pSphere1->GetRadius() + pSphere2->GetRadius())*(pSphere1->GetRadius() + pSphere2->GetRadius()) <= distance_square){ //check
		//collied
		return true;
	}
	return false;
}
//bool CollisionDetection::SpherePlaneCollision(BoundingSphere *pSphere, PlaneBounding *pPlane){  //sphere to plane collision
//	//
//	float distance= (pSphere->GetPos() - pPlane->getPos()).dot(pPlane->getNormal());
//	if (pSphere->GetRadius()<distance){
//		//ccollied
//		return true;
//	}
//	return false;
//}

