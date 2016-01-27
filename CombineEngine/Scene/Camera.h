

#ifndef CAMERA_H_
#define CAMERA_H_

//#include "stdafx.h"
//#include "Vec3.h"
#include "Transformation.h"

//parameters
const float Xmin = -2.353;
const float Xmax = 0.369;
const float Ymin = -1.546;
const float Ymax = 1.742;

class Camera: public Spatial
{
private:
	//basic parameters
	Vec3f pos;   //camera position
	Vec3f Up_vec; //up vector
	Vec3f view_dir; //viewing direction

	//projection parameters
	float near_clip;
	float far_clip;
	float height;
	float aspect;

	Mat4f ObjectSpace_Mat;

	
public:
	//constructors
	Camera() { pos = Vec3f(0, 0, 0); Up_vec = Vec3f(0, 0, 0); view_dir=Vec3f(0, 0, 0); 
		CalculateObjSpace();
		World.Reset();
	}
	Camera(Vec3f position, Vec3f up_vector, Vec3f Viewing_Direction) { 
		pos = position; Up_vec = up_vector; view_dir = Viewing_Direction; 
		CalculateObjSpace();
		World.Reset();
	}

	void CalculateObjSpace(){
		Vec3f obj_x, obj_y, obj_z;
		obj_z = view_dir;
		obj_z.normalize();
		obj_x = view_dir.cross(Up_vec);
		obj_x.normalize();
		obj_y = obj_z.cross(obj_x);
		ObjectSpace_Mat = Mat4f(
			obj_x.x(), obj_x.y(), obj_x.z(), 0.0f,
			obj_y.x(), obj_y.y(), obj_y.z(), 0.0f,
			obj_z.x(), obj_z.y(), obj_z.z(), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}
	
	//set
	void setPosition(Vec3f position){ pos = position;  }
	void setDirection(Vec3f dir){ view_dir = dir.normalize(); }
	void setUpVector(Vec3f Up_Vector){ Up_vec = Up_Vector; }
	void setTarget(Vec3f target){ 
		view_dir = target - pos;
		view_dir.normalize();
	}
	void viewing_direction(Vec3f direction){ view_dir=direction; }
	void SetFrustum(float near_clipping, float far_clipping, float _height, float _aspect){
		near_clip = near_clipping; far_clip = far_clipping; height = _height; aspect = _aspect;
	}
	void setAspect(float _aspect){
		aspect = _aspect;
	}

	//special overload
	void Rotate(float radius);

	////get functions///////////////

	//get position
	Vec3f getPosition(){ return pos; }
	float getPosx(){ return pos.x(); }
	float getPosy(){ return pos.y(); }
	float getPosz(){ return pos.z(); }

	//get viewing direction
	Vec3f getDirect(){ return view_dir; }
	float getDircetx(){ return view_dir.x(); }
	float getDircety(){ return view_dir.y(); }
	float getDircetz(){ return view_dir.z(); }

	//get up vector
	float getUpVectorx(){ return Up_vec.x(); }
	float getUpVectory(){ return Up_vec.y(); }
	float getUpVectorz(){ return Up_vec.z(); }

	//get frustum parameters
	float n(){ return near_clip; }
	float f(){ return far_clip; }
	float h(){ return height; }
	float Aspect(){return aspect;}

	//camera space
	Mat4f getCameraSpace(){
		return ObjectSpace_Mat;
	}
	//return projection matrix for newer version of glsl
	Mat4f getProjectionMatrix();
	Mat4f getViewMatrix();
	inline void BindMatrix();

	//override transformation
	void Translate(Vec3f offsetVector);
	//void Rotate(Vec3f angles, Vec3f axis);
	//void Scale(Vec3f scaleVector);
	bool MovementConstrainSquare(float xmin,float xmax,float ymin,float ymax, Vec3f direction,Vec3f position, float threashhold);
	void ConstrainedTranslate(Vec3f offsetVector);

	~Camera();
};

#endif //CAMERA_H_