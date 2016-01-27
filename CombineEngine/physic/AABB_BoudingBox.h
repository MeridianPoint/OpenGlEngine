#pragma once
#include "Abstract_BoundingBox.h"
class AABB_BoudingBox :
	public Abstract_BoundingBox
{
private:
	//
	Vec3f m_Min;
	Vec3f m_Max;
public:
	AABB_BoudingBox();
	AABB_BoudingBox(Vec3f Min_coord, Vec3f Max_coord) :m_Min(Min_coord), m_Max(Max_coord){}
	~AABB_BoudingBox();

	//
	void ComputeBoudingBox();

};

