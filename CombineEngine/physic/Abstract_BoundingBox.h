//class name : abstract bounding box
// funtion: abstract class of bounding box
#ifndef ABSTRACT_BOUNDINGBOX_H_
#define ABSTRACT_BOUNDINGBOX_H_
class Abstract_BoundingBox: public Spatial
{
public:
	Abstract_BoundingBox();
	virtual ~Abstract_BoundingBox();
	virtual void Moveto(Vec3f pos); //move bounding box 

	//virtual bool checkCollision(Abstract_BoundingBox* object);
};

#endif //ABSTRACT_BOUNDINGBOX_H_