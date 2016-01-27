#include "stdafx.h"
#include "PathFollowController.h"


PathFollowController::PathFollowController()
{
}


PathFollowController::~PathFollowController()
{
}

void PathFollowController::AddKeyframe(float time, Vec3f position, Interp_Type InterType){
	//
	if (translationTimes.size() == 0){ //no key frame
		//
		translationTimes.push_back(time);
		TransitionData.push_back(position);
	}
	else if (time >= translationTimes[translationTimes.size() - 1]) // extend active frame
	{
		translationTimes.push_back(time);
		TransitionData.push_back(position);
	}
	else{// insert frame in the middle
		std::vector<float>::iterator it1 = translationTimes.begin();
		std::vector<Vec3f>::iterator it2 = TransitionData.begin();
		while (time > *it1)
		{
			it1++;
			it2++;
		}
		translationTimes.insert(it1 - 1, time);
		TransitionData.insert(it2 - 1, position);
	}
	//set initial direction
	if (translationTimes.size() >= 4){
		if (InterpType == IT_CATMULL_ROM){
			InitialDirection = inter.Catmull_RomInterpolationDeprivative(TransitionData[0], TransitionData[1], TransitionData[2], TransitionData[3],.0);
		}
		if (InterpType == IT_B_SPLINE){
			InitialDirection = inter.BSplineInterpolationDeprivative(TransitionData[0], TransitionData[1], TransitionData[2], TransitionData[3], .0);
		}
	}
	//set active range
	if (translationTimes.size() >= 4){
		//set active range
		setActiveLength(translationTimes[1], translationTimes[translationTimes.size() - 2]);
	}
}

Mat4f PathFollowController::VectorRotation(Vec3f Prev, Vec3f Post){
	//
	Vec3f vec = Prev.cross(Post);
	float sine = vec.length();
	float cose = Prev.dot(Post);

	Mat4f vec_mat = Mat4f(
		0.0, -vec.z(), vec.y(),0.0,
		vec.z(), 0.0, -vec.x(),0.0,
		-vec.y(), vec.x(), 0.0, 0.0,
		0.0,.0,.0,1.0
		);
	Mat4f Rotation_matrix = Mat4f(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	//Rotation_matrix += vec_mat + vec_mat*vec_mat*(1 - cose) / (sine*sine);

	Rotation_matrix = Rotation_matrix+vec_mat + vec_mat*vec_mat*(1 - cose) / (sine*sine);

	return Rotation_matrix;
}

bool PathFollowController::Update(float time){

	//clamp time
	time = time + MinTime;
	if (time > MaxTime){
		while (time > MaxTime){
			time = time - MaxTime;
		}
		time += MinTime;
	}
	if (translationTimes.size() == 0){
		return false;
	}

	//
	float tblendfactor = 0.0f; //blend between two frames
	float rblendfactor = 0.0f;

	float tblendElasp = 0.0f; //blend time
	float rblendElasp = 0.0f;

	Vec3f cur_direction; //current moving direction
	//

	if (translationTimes.size() >= 4) //transition keyframe exist
	{
		//
		if (time < translationTimes[0])//before first keyframe
		{
			cur_Pos = TransitionData[1];
		}
		else if (translationTimes.size()>1 && time<translationTimes[translationTimes.size() - 2]){ //before last keyframe
			unsigned int keyIndex = 0; //index of current key
			while (time >= translationTimes[keyIndex + 1])
			{
				//iterate through key 
				keyIndex++;
			}
			if (keyIndex == translationTimes.size() - 2){
				keyIndex=1;
			}
			tblendElasp = translationTimes[keyIndex + 1] - translationTimes[keyIndex];
			tblendfactor = (time - translationTimes[keyIndex]) / tblendElasp;

			//blend
			if (InterpType == IT_CATMULL_ROM){
				//catulm rome interpolation
				cur_Pos = inter.Catmull_RomInterpolation(TransitionData[keyIndex - 1], TransitionData[keyIndex], TransitionData[keyIndex + 1], TransitionData[keyIndex + 2], tblendfactor);
			}
			if (InterpType == IT_B_SPLINE){
				//b-spline
				cur_Pos = inter.BSplineInterpolation(TransitionData[keyIndex - 1], TransitionData[keyIndex], TransitionData[keyIndex + 1], TransitionData[keyIndex + 2], tblendfactor);
			}


		}
		else{
			//after last keyframe
		}

		//update model info
		pModel->DirectTranslate(cur_Pos);
	}
	if (translationTimes.size() >= 4) //rotation keyframe exist
	{
		//
		if (time<translationTimes[0]) //before first ket frame
		{
			//get first frame status
			//if (RType == RT_FIXED)
			//{
			//	cur_Rotation = RotationData[1].getRotationMatrix();
			//}
			//else if (RType == RT_QUATERNION){
			//	cur_Rotation = qRotationData[1].getRotationMatrix();
			//}
			//else{
			//	//other inplementation
			//}

		}
		else if (time >= translationTimes[0] && time <= translationTimes[translationTimes.size() - 1]){
			//during trasition
			unsigned int keyIndex = 0; //index of current key
			if (time >= translationTimes[keyIndex + 1])
			{
				//iterate through key 
				keyIndex++;
			}
			if (keyIndex == translationTimes.size() - 2){
				keyIndex=1;
			}
			tblendElasp = translationTimes[keyIndex + 1] - translationTimes[keyIndex];
			tblendfactor = (time - translationTimes[keyIndex]) / tblendElasp;
			//calculate rotation matrix /////////////////////////////////
			if (InterpType == IT_CATMULL_ROM){
				//catulm rome interpolation
				
				cur_direction = inter.Catmull_RomInterpolationDeprivative(TransitionData[keyIndex - 1], TransitionData[keyIndex], TransitionData[keyIndex + 1], TransitionData[keyIndex + 2], tblendfactor);
				cur_speed = cur_direction;
				cur_direction.normalize();
				InitialDirection.normalize();
				cur_Rotation = VectorRotation(InitialDirection,cur_direction);
			}
			if (InterpType == IT_B_SPLINE){
				//b-spline
				cur_direction = inter.BSplineInterpolationDeprivative(TransitionData[keyIndex - 1], TransitionData[keyIndex], TransitionData[keyIndex + 1], TransitionData[keyIndex + 2], tblendfactor);
				cur_speed = cur_direction;
				cur_direction.normalize();
				InitialDirection.normalize();
				cur_Rotation = VectorRotation(InitialDirection, cur_direction);
			}
			///////////////////////////////////////////////////

			//update model info
			pModel->Rotate(cur_Rotation);
		}
		else{// not enough frames
			//std::cerr << "not enough key frame" << std::endl;
		}
	}
return true;
}

Vec3f PathFollowController::getSpeed(float time){
	return cur_speed;
}
