#include "stdafx.h"
#include "Phong_Material.h"


Phong_Material::Phong_Material()
{
}


Phong_Material::~Phong_Material()
{
}

void Phong_Material::LoadPhongShader(){
	ProgramID = LoadShaders(vertexshadername, fragmentshadername);
}