#include "stdafx.h"
#include "KeyFrameController.h"


//KeyFrameController::KeyFrameController()
//{
//}


KeyFrameController::~KeyFrameController()
{
}

bool KeyFrameController::Update(float time){
	//constrain time
	time = time + MinTime;
	if (time > MaxTime){
		while (time > MaxTime){
			time = time - MaxTime;
		}
		time += MinTime;
	}
	

	//
	if (translationTimes.size() >= 0 || RotationTimes.size() >= 0){ //check if keyframe exist

		float tblendfactor = 0.0f; //blend between two frames
		float rblendfactor = 0.0f;

		float tblendElasp = 0.0f; //blend time
		float rblendElasp = 0.0f;

		//

		if (translationTimes.size() >= 4) //transition keyframe exist
		{
			//
			if (time < translationTimes[0])//before first keyframe
			{
				cur_Pos = TransitionData[1];
			}
			else if (translationTimes.size()>1 && time<translationTimes[translationTimes.size()-2]){ //before last keyframe
				unsigned int keyIndex = 0; //index of current key
				while (time >= translationTimes[keyIndex + 1])
				{
					//iterate through key 
					keyIndex++;
				}
				if (keyIndex == translationTimes.size() - 2){
					keyIndex = 1;
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
			//pModel->DirectTranslate(cur_Pos);

			pModel->Translate(cur_Pos, TransCoord, TT_SET);

			//coordiante based
			//pSpatial->
		}
		if (RotationTimes.size() >= 4) //rotation keyframe exist
		{
			//
			if (time<RotationTimes[0]) //before first ket frame
			{
				//get first frame status
				if (RType == RT_FIXED)
				{ 
					cur_Rotation = RotationData[1].getRotationMatrix();
				}
				else if (RType==RT_QUATERNION){
					cur_Rotation = qRotationData[1].getRotationMatrix();
				}
				else{
					//other inplementation
				}
				
			}
			else if (time >= RotationTimes[0] && time <= RotationTimes[RotationTimes.size() - 1]){
				//during trasition
				unsigned int keyIndex = 0; //index of current key
				while (time >= RotationTimes[keyIndex + 1])
				{
					//iterate through key 
					keyIndex++;
				}
				if (keyIndex == RotationTimes.size() - 2){
					keyIndex = 1;
				}
				tblendElasp = RotationTimes[keyIndex + 1] - RotationTimes[keyIndex];
				tblendfactor = (time - RotationTimes[keyIndex]) / tblendElasp;
				if (InterpType == IT_CATMULL_ROM){ //catum rom interpolation
					if (RType == RT_FIXED)
					{
						Fixed_Angle cur_angle = inter.Catmull_RomInterpolation(RotationData[keyIndex - 1], RotationData[keyIndex], RotationData[keyIndex + 1], RotationData[keyIndex + 2], tblendfactor);
						cur_Rotation = cur_angle.getRotationMatrix();
						
					}
					else if (RType == RT_QUATERNION){
						Quaternion cur_quaternion = inter.Catmull_RomInterpolation(qRotationData[keyIndex - 1], qRotationData[keyIndex], qRotationData[keyIndex + 1], qRotationData[keyIndex + 2], tblendfactor);
						cur_quaternion.normalize();
						cur_Rotation = cur_quaternion.getRotationMatrix();
					}
				}
				else if (InterpType == IT_B_SPLINE){
					//
					if (RType == RT_FIXED)
					{
						Fixed_Angle cur_angle = inter.BSplineInterpolation(RotationData[keyIndex - 1], RotationData[keyIndex], RotationData[keyIndex + 1], RotationData[keyIndex + 2], tblendfactor);
						cur_Rotation = cur_angle.getRotationMatrix();
					}
					else if (RType == RT_QUATERNION){
						Quaternion cur_quaternion = inter.BSplineInterpolation(qRotationData[keyIndex - 1], qRotationData[keyIndex], qRotationData[keyIndex + 1], qRotationData[keyIndex + 2], tblendfactor);
						cur_quaternion.normalize();
						cur_Rotation = cur_quaternion.getRotationMatrix();
					}
				}

				//update model info
				//pModel->Rotate(cur_Rotation);
				//
				pModel->Rotate(cur_Rotation, TransCoord, TT_SET);
			}
			else{
			}
		}
	}
	return true;
}

void KeyFrameController::AddKeyframe(float time, Vec3f position, Fixed_Angle fixed_angles){
	setRotation_Type(RT_FIXED);
	////handling translation
	//if (translationTimes.size() == 0){    //no previous data
	//	translationTimes.push_back(time);
	//	TransitionData.push_back(position);
	//}
	//else if (time>=translationTimes[translationTimes.size() - 1]) // extend active frame
	//{
	//	translationTimes.push_back(time);
	//	TransitionData.push_back(position);
	//}
	//else{// insert frame in the middle
	//	std::vector<float>::iterator it1 = translationTimes.begin();
	//	std::vector<Vec3f>::iterator it2=TransitionData.begin();
	//	while (time>*it1)
	//	{
	//		it1++;
	//		it2++;
	//	}
	//	translationTimes.insert(it1 - 1, time);
	//	TransitionData.insert(it2-1,position);
	//}


	//handling rotation
	if (RotationTimes.size() == 0) //no previous data
	{
		RotationTimes.push_back(time);
		RotationData.push_back(fixed_angles);
	}
	else if (time>=translationTimes[translationTimes.size() - 1]){
		RotationTimes.push_back(time);
		RotationData.push_back(fixed_angles);
	}
	else //insert
	{
		std::vector<float>::iterator it1 = RotationTimes.begin();
		std::vector<Fixed_Angle>::iterator it2 = RotationData.begin();
		while (time>*it1 && it1 != RotationTimes.end())
		{
			it1++;
			it2++;
		}
		RotationTimes.insert(it1 - 1, time);
		RotationData.insert(it2 - 1, fixed_angles);
	}
	//set active range when apply
	if (translationTimes.size() >= 4){
		//set active range
		setActiveLength(translationTimes[1], translationTimes[translationTimes.size() - 2]);
	}
}
void KeyFrameController::AddKeyframe(float time, Vec3f position, Quaternion quaternion){
	setRotation_Type(RT_QUATERNION);
	quaternion.normalize();
	//handling translation
	if (translationTimes.size() == 0){    //no previous data
		translationTimes.push_back(time);
		TransitionData.push_back(position);
	}
	else if (time>=translationTimes[translationTimes.size()-1]) // extend active frame
	{
		translationTimes.push_back(time);
		TransitionData.push_back(position);
	}
	else{// insert frame in the middle
		std::vector<float>::iterator it1=translationTimes.begin();
		std::vector<Vec3f>::iterator it2=TransitionData.begin();
		while (time>*it1&&it1!=translationTimes.end())
		{
			it1++;
			it2++;
		}
		translationTimes.insert(it1 - 1, time);
		TransitionData.insert(it2-1,position);
	}


	//handling rotation
	if (RotationTimes.size() == 0 || time>=translationTimes[translationTimes.size() - 1]) //no previous data
	{
		RotationTimes.push_back(time);
		qRotationData.push_back(quaternion);
	}
	else //insert
	{
		std::vector<float>::iterator it1 = RotationTimes.begin();
		std::vector<Quaternion>::iterator it2=qRotationData.begin();
		while (time>*it1 && it1!=RotationTimes.end())
		{
			it1++;
			it2++;
		}
		RotationTimes.insert(it1 - 1, time);
		qRotationData.insert(it2 - 1, quaternion);
	}
	//set active range when apply
	if (translationTimes.size()>=4){
		//set active range
		setActiveLength(translationTimes[1], translationTimes[translationTimes.size() - 2]);
	}
}

void KeyFrameController::setActiveLength(float initate, float end){
	if (translationTimes.size()>0)
	{
		if (initate >= translationTimes[0] && end <= translationTimes[translationTimes.size() - 1]){
			//set time constrain
			MinTime = initate;
			MaxTime = end;

			//shift time
			/*for (int i = 0; i < translationTimes.size(); i++){
			translationTimes[i] -= MinTime;
			RotationTimes[i] -= MinTime;
			}*/
		}
	}
	else if (RotationTimes.size() > 0)
	{
		if (initate >= RotationTimes[0] && end <= RotationTimes[RotationTimes.size() - 1]){
			//set time constrain
			MinTime = initate;
			MaxTime = end;

			//shift time
			/*for (int i = 0; i < translationTimes.size(); i++){
			translationTimes[i] -= MinTime;
			RotationTimes[i] -= MinTime;
			}*/
		}
	}
	else{
		std::cerr << "Too little keyframes!" << std::endl;
	}
	
	
}

void KeyFrameController::AddKeyframe(float time, Fixed_Angle fixed_angles){
	setRotation_Type(RT_FIXED);
	if (RotationTimes.size() == 0) //no previous data
	{
		RotationTimes.push_back(time);
		RotationData.push_back(fixed_angles);
	}
	else if (time >= translationTimes[translationTimes.size() - 1]){
		RotationTimes.push_back(time);
		RotationData.push_back(fixed_angles);
	}
	else //insert
	{
		std::vector<float>::iterator it1 = RotationTimes.begin();
		std::vector<Fixed_Angle>::iterator it2 = RotationData.begin();
		while (time>*it1 && it1 != RotationTimes.end())
		{
			it1++;
			it2++;
		}
		RotationTimes.insert(it1 - 1, time);
		RotationData.insert(it2 - 1, fixed_angles);
	}
	//set active range when apply
	if (RotationTimes.size() >= 4){
		//set active range
		setActiveLength(RotationTimes[1], RotationTimes[RotationTimes.size() - 2]);
	}

}
void KeyFrameController::AddKeyframe(float time, Quaternion quaternion){
	setRotation_Type(RT_QUATERNION);
	if (RotationTimes.size() == 0 || time >= RotationTimes[RotationTimes.size() - 1]) //no previous data
	{
		RotationTimes.push_back(time);
		qRotationData.push_back(quaternion);
	}
	else //insert
	{
		std::vector<float>::iterator it1 = RotationTimes.begin();
		std::vector<Quaternion>::iterator it2 = qRotationData.begin();
		while (time>*it1 && it1 != RotationTimes.end())
		{
			it1++;
			it2++;
		}
		RotationTimes.insert(it1 - 1, time);
		qRotationData.insert(it2 - 1, quaternion);
	}
	//set active range when apply
	if (RotationTimes.size() >= 4){
		//set active range
		setActiveLength(RotationTimes[1], RotationTimes[RotationTimes.size() - 2]);
	}
}
