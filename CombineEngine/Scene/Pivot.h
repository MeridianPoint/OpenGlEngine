//filename: pivot.h
//usage pivot for rotation
#ifndef PIVOT_H_
#define PIVOT_H_

#include "Spatial.h"
class Pivot :
	public Spatial
{
public:
	Pivot();
	~Pivot();
	//transformation
	void setPosition(Vec3f posvec);
	void Translate(Vec3f translateVector);
	//void Rotation(Vec3f Angles);
	void Rotation(Mat4f RotationMat);

	void AlignToWorld();
};

#endif