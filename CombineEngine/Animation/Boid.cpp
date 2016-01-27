#include "stdafx.h"
#include "Boid.h"


Boid::Boid()
{
}

Boid::Boid(Model* model, Vec3f initVelocity){
	pModel = model;
	velocity = initVelocity;
	NeighboorDistance = 80;
	BehaviorRate[0] = 0.95;
	//BehaviorRate[0] = 0.5;
	BehaviorRate[1] = 0.003;
	BehaviorRate[2] = 0.2;
	BehaviorRate[3] = 0.6;

	//initial rotation
	Vec3f inital_direction = Vec3f(0.0, 1.0, 0.0);
	Vec3f vec = inital_direction.getNorm().cross(initVelocity.getNorm());
	float sine = vec.length();
	float cose = inital_direction.getNorm().dot(initVelocity.getNorm());

	Mat4f vec_mat = Mat4f(
		0.0, -vec.z(), vec.y(), 0.0,
		vec.z(), 0.0, -vec.x(), 0.0,
		-vec.y(), vec.x(), 0.0, 0.0,
		0.0, .0, .0, 1.0
		);
	Mat4f Rotation_matrix = Mat4f(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	//Rotation_matrix += vec_mat + vec_mat*vec_mat*(1 - cose) / (sine*sine);

	Rotation_matrix = Rotation_matrix + vec_mat + vec_mat*vec_mat*(1 - cose) / (sine*sine);
	pModel->SetRotation(Rotation_matrix);
}

Boid::~Boid()
{
	delete pModel;
}



void Boid::alignVelocity(Vec3f newVelocity){
	float epsilon = 0.002;
	if (newVelocity.length() <= epsilon)
		return;

	if (abs(velocity.length()-newVelocity.length())>epsilon)
		Rotation(newVelocity);
	velocity = newVelocity;
	//align direction
	
}

Vec3f Boid::getPosition(){
	if (pModel != nullptr){
		return pModel->GetPosition();
	}
}

Vec3f Boid::getVelocity(){
	return velocity;
}

float Boid::Distance(Boid *pOther){
	Vec3f disVector = getPosition() - pOther->getPosition();
	return disVector.length();
}

float Boid::Distance_square(Boid *pOther){
	Vec3f disVector = getPosition() - pOther->getPosition();
	return disVector.lengthsq();
}

bool Boid::isNeighboor(Boid *pOther){ //check if target is neighboor
	if (Distance(pOther) <= NeighboorDistance){
		return true;
	}
	else
		return false;
}
bool Boid::ActiveForceField(Boid *pOther){ //check if forcefield is needed;
	Vec3f disVector = pOther->getPosition() - getPosition();
	if (disVector.dot(velocity) <= 0 || disVector.length()>NeighboorDistance){
		return false;
	}
	else return true;
}


Vec3f Boid::getRepulsiveAcceleration(Boid *pOther){
	Vec3f direction = getPosition()-pOther->getPosition();
	Vec3f acceleration = direction.getNorm() / direction.lengthsq();
	return acceleration;
}

/////transformation  //////////////////////////////////////
void Boid::Translate(Vec3f translateVector){
	if (pModel!=nullptr)
	{
		pModel->Translate(translateVector);
	}
}
void Boid::Rotation(Vec3f NewDirection){
	if (velocity == NewDirection){
		return;
	}

	Vec3f old_v = velocity;
	Vec3f new_v = NewDirection;
	old_v.normalize();
	new_v.normalize();
	Vec3f vec = old_v.cross(new_v);
	float sine = vec.length();
	float cose = old_v.dot(new_v);

	Quaternion result;
	float epsilon = 0.02;

	/*// if dot == 1, vectors are the same
  if (ei_isApprox(c,Scalar(1)))
  {
    // set to identity
    this->w() = 1; this->vec().setZero();
    return *this;
  }
  // if dot == -1, vectors are opposites
  if (ei_isApprox(c,Scalar(-1)))
  {
    this->vec() = v0.unitOrthogonal();
    this->w() = 0;
    return *this;
  }

  Vector3 axis = v0.cross(v1);
  Scalar s = ei_sqrt((Scalar(1)+c)*Scalar(2));
  Scalar invs = Scalar(1)/s;
  this->vec() = axis * invs;
  this->w() = s * Scalar(0.5);

  return *this;*/

	if (abs(cose-1)<=epsilon){//vectors are the same
		result = Quaternion(1, 0.0, 0.0, 0.0);
		return;
	}
	if (abs(cose + 1) <= epsilon){ //opposite
		//result = Quaternion(0,)
		return;
	}

	Mat4f vec_mat = Mat4f(
		0.0, -vec.z(), vec.y(), 0.0,
		vec.z(), 0.0, -vec.x(), 0.0,
		-vec.y(), vec.x(), 0.0, 0.0,
		0.0, .0, .0, 1.0
		);
	Mat4f Rotation_matrix = Mat4f(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	//Rotation_matrix += vec_mat + vec_mat*vec_mat*(1 - cose) / (sine*sine);

	Rotation_matrix = Rotation_matrix + vec_mat*sine + vec_mat*vec_mat*(1 - cose) /*/ (sine*sine)*/;
	Rotation_matrix = Mat4f(
		Rotation_matrix.xx(), Rotation_matrix.xy(), Rotation_matrix.xz(), 0.0,
		Rotation_matrix.yx(), Rotation_matrix.yy(), Rotation_matrix.yz(), 0.0,
		Rotation_matrix.zx(), Rotation_matrix.zy(), Rotation_matrix.zz(), 0.0,
		0.0, 0.0, 0.0, 1.0
		);
	pModel->SetRotation(Rotation_matrix);
	//Quaternion rotateQuaternion = Quaternion(sine, vec);
	//rotateQuaternion.normalize();
	float s = (1 + cose) * 2;

	result = Quaternion(0.5*s, vec / s);
	result.normalize();
	pModel->Rotate(result);
}

void Boid::SetWeights(float *weights){
	BehaviorRate[0] = weights[0];
	BehaviorRate[1] = weights[1];
	BehaviorRate[2] = weights[2];
	BehaviorRate[3] = weights[3];                                                                                                                                                                                                                                                                                                             
}