#ifndef KEY_CONTROLLER_H_
#define KEY_CONTROLLER_H_

#include "stdafx.h"
#include "Controller.h"

enum Interp_Type { IT_CATMULL_ROM, IT_B_SPLINE };
enum Rotation_Type{ RT_FIXED, RT_QUATERNION };

class KeyFrameController :
	public Controller
{
private:
	Mat4f getTranslationMatrix(Vec3f relat_Pos);
public:
	KeyFrameController(){
		TransCoord = TC_WORLD;
	}
	~KeyFrameController();

	//translation data
	std::vector<float> translationTimes;
	std::vector<Vec3f> TransitionData;

	//rotation data
	std::vector<float> RotationTimes;
	std::vector<Fixed_Angle> RotationData;
	std::vector<Quaternion> qRotationData;


	//store status
	Vec3f cur_Pos;  //current position
	Mat4f Pos_trans_Mat;
	Mat4f cur_Rotation;
	Quaternion cur_qRotation;

	Interpolation inter;

	virtual bool Update(float time);

	void setActiveLength(float initate, float end);

	//key frame adding
	void AddKeyframe(float time, Vec3f position, Fixed_Angle fixed_angles);
	void AddKeyframe(float time, Vec3f position, Quaternion quaternion);
	void AddKeyframe(float time, Fixed_Angle fixed_angles);
	void AddKeyframe(float time, Quaternion quaternion);

	//void AddKeyframe(float time, Vec3f position, Fixed_Angle fixed_angles, TranslateCoordinate coord=TC_WORLD);
	//void AddKeyframe(float time, Vec3f position, Quaternion quaternion, TranslateCoordinate coord = TC_WORLD);
	//void AddKeyframe(float time, Fixed_Angle fixed_angles, TranslateCoordinate coord = TC_WORLD);
	//void AddKeyframe(float time, Quaternion quaternion, TranslateCoordinate coord = TC_WORLD);

	//setModel
	void SetModel(Model *pkModel){ pModel = pkModel; }
	void SetSpatial(Spatial *Spatial){ pSpatial = Spatial; };
	void SetTransitionCoordinate(TranslateCoordinate TranslateCoord){
		TransCoord = TranslateCoord;
	}

	
protected:
	//enum settings
	TransformationType translationType;
	Interp_Type InterpType;
	Rotation_Type RType;
	TranslateCoordinate TransCoord;
	//
	static void GetKeyInfo(float fControlTime, int iQuantity, float* atime, int&lastIndex, float& rfNormaTime, int& ri0, int& ri1);

	
	void setRotation_Type(Rotation_Type rt){ RType = rt; }

	//Add key
	

	Mat4f GetTranslation(float NormalTime, int i0, int i1);
	Mat4f GetROtation(float NormalTime, int i0, int i1);

	int tLastIndex;

public:
	void setInterType(Interp_Type it){ InterpType = it; }
};

#endif