#include "stdafx.h"
#include "Camera.h"


//Camera::Camera()
//{
//}

bool Camera::MovementConstrainSquare(float xmin, float xmax, float ymin, float ymax, Vec3f direction, Vec3f position, float threshold){
	if (position.x()-xmin<=threshold)//collide with minimum x
	{
		if (direction.dot(Vec3f(1.0,0.0,0.0))<0.0)
		{
			return false;
		}
	}
	if (position.y() - ymin <= threshold){//collide with minimum xy
		if (direction.dot(Vec3f(0.0, 1.0, 0.0)) < 0.0)
		{
			return false;
		}
	}
	if (xmax- position.x() <= threshold)//collide with maximum x
	{
		if (direction.dot(Vec3f(-1.0, 0.0, 0.0)) < 0.0)
		{
			return false;
		}
	}
	if (ymax-position.y() <= threshold)//collide with maximum y
	{
		if (direction.dot(Vec3f(0.0, -1.0, 0.0)) < 0.0)
		{
			return false;
		}
	}
	return true;
}

void Camera::ConstrainedTranslate(Vec3f offsetVector){
	Mat4f Trans_Mat(
		1.0f, 0.0f, 0.0f, offsetVector.x(),
		0.0f, 1.0f, 0.0f, offsetVector.y(),
		0.0f, 0.0f, 1.0f, offsetVector.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		);
	Mat4f Idenity(
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0
		);
	Trans_Mat = ObjectSpace_Mat.Inverse()*Trans_Mat*ObjectSpace_Mat*Idenity;
	Vec3f dir=Vec3f(Trans_Mat.xw(),Trans_Mat.yw(),Trans_Mat.zw());
	if (MovementConstrainSquare((Xmin + 0.131) * 16, (Xmax + 0.131) * 16, (Ymin -0.048)* 17, (Ymax -0.048)* 17, dir, pos, 0.8f))
	{
		Translate(offsetVector);
	}
}

void Camera::Translate(Vec3f offsetVector){
	//glTranslatef(offsetVector.x(), offsetVector.y(), offsetVector.z());
	Mat4f Trans_Mat(
		1.0f, 0.0f, 0.0f, offsetVector.x(),
		0.0f, 1.0f, 0.0f, offsetVector.y(),
		0.0f, 0.0f, 1.0f, offsetVector.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		);
	Mat4f Translate_Mat(
		1.0f, 0.0f, 0.0f, -pos.x(),
		0.0f, 1.0f, 0.0f, -pos.y(),
		0.0f, 0.0f, 1.0f, -pos.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		); //translate to origin
	//Translate_Matrix = Trans_Mat*Translate_Matrix;
	World.Transformation_Matrix = Translate_Mat.Inverse()*ObjectSpace_Mat.Inverse()*Trans_Mat*ObjectSpace_Mat*Translate_Mat*World.Transformation_Matrix;
	World.Translate_Matrix = Trans_Mat*World.Translate_Matrix;
	//pos = HomeGenTransform(pos, Translate_Mat.Inverse()*ObjectSpace_Mat.Inverse()*Trans_Mat*ObjectSpace_Mat*Translate_Mat*Trans_Matrix);
	pos = World.HomeGenTransform(pos, ObjectSpace_Mat.Inverse()*Trans_Mat*ObjectSpace_Mat);
	//CalculateObjSpace();
	//pos += view_dir*offsetVector.length();
}

//void Camera::Rotate(Vec3f angles, Vec3f axis){
/*Mat4f Rotat_Mat();
  Mat4f Translate _Mat(
  1.0f, 0.0f, 0.0f, -pos.x(),
  0.0f, 1.0f, 0.0f, -pos.y(),
  0.0f, 0.0f, 1.0f, -pos.z(),
  0.0f, 0.0f, 0.0f, 1.0f
  ); //translate to origin
  Rotation_Matrix=Rotat_Mat*Rotation_Matrix;
  view_dir=Rotation_Matrix*view_dir;
  Transform_Matrix=Translate _Mat.Inverse()*Rotation_Matrix*Translate _Mat*Transform;
  
*/
//}

void Camera::Rotate(float radius){
	/*Mat4f Rotat_Mat(
		cos(radius), 0.0f,-sin(radius),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin(radius), 0.0f, cos(radius),0.0f,
		0.0f,0.0f,0.0f,1.0f

		);*/
	Mat4f Rotat_Mat(
		cos(radius), -sin(radius), 0.0f, 0.0f,
		sin(radius), cos(radius), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f,1.0f
		);
	Mat4f Translate_Mat(
		1.0f, 0.0f, 0.0f, -pos.x(),
		0.0f, 1.0f, 0.0f, -pos.y(),
		0.0f, 0.0f, 1.0f, -pos.z(),
		0.0f, 0.0f, 0.0f, 1.0f
		); //translate to origin
	World.Rotation_Matrix = Rotat_Mat*World.Rotation_Matrix;
	view_dir = World.HomeGenTransform(view_dir, Rotat_Mat);
	Up_vec = World.HomeGenTransform(Up_vec, Rotat_Mat);
	World.Transformation_Matrix = Translate_Mat.Inverse()*World.Rotation_Matrix*Translate_Mat*World.Transformation_Matrix;
	//pos = HomeGenTransform(pos, Translate_Mat.Inverse()*Rotation_Matrix*Translate_Mat);
	CalculateObjSpace();
}

Camera::~Camera()
{

}

Mat4f Camera::getProjectionMatrix(){
	Mat4f Camera_Trans_Mat = Mat4f(
		1.0,0.0,0.0,-pos.x(),
		0.0,1.0,0.0,-pos.y(),
		0.0,0.0,1.0,-pos.z(),
		0.0,0.0,0.0,1.0
		);
	Mat4f Projection_Mat = Mat4f(
		near_clip / (height*aspect), 0.0, 0.0, 0.0,
		0.0, near_clip / height, 0.0, 0.0,
		0.0, 0.0, 2 * near_clip*far_clip / (near_clip+far_clip),0.0,
		0.0,0.0,-1,0.0
		);
	return Projection_Mat*Camera_Trans_Mat;
}

inline void Camera::BindMatrix(){
	//glB
	//apply id 
	GLint ProgramID;

	GLuint MatrixID = glGetUniformLocation(ProgramID, "ProjectionView");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, getProjectionMatrix().ToArray());
}