#pragma once
//#include "stdafx.h"
class Phong_Material:public Material
{
private:
	//shader names
	const char* vertexshadername = "vertexshader1.glsl";
	const char* fragmentshadername = "fragmentshader.glsl";
	//parameter
	Vec3f ka, kd, ks;

	//texture
	bool useAmbientTexture;
	bool useDiffuseTexture;
	bool useSpecularTexture;
	bool useNormalMap;
	bool useParallexMap;
public:
	Phong_Material();
	~Phong_Material();
	void setColor(Vec3f Ka, Vec3f Kd, Vec3f Ks){ ka = Ka, kd = Kd, ks = Ks; }
	void LoadPhongShader();
	inline void useShader();
};

