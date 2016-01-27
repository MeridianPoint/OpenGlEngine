/*
 *  PolyModel.h
 *
 *  
 *
 */
#ifndef _POLY_MODEL_H_
#define _POLY_MODEL_H_

//#pragma once
#include "stdafx.h"
#include "Vec3.h"
#include "Vec2.h"
#include "Light.h"
#include "Material.h"

#include <vector>
#include <algorithm>
#include <iostream>

//using namespace std;
//template <class T>
//class Vec3;
//
//class Vecf3;

class PolyModel
{
public:
	PolyModel() {}
	
	//draw functions
	void draw();
	void draw2d();
	//draw for glfw
	float* dataArray();

	//use for debug
	void debugdraw();

	//compute face/polygon normal for shading
	void computeFaceNormals();

	//compute vertex normal for shading --phong shading and more advanced shading
	void computeVertexNormals();

	//load model from file
    bool loadModel(std::istream& istr, bool reverse=false);
    
    Vec3f getCenter() const { return m_center; }
    Vec3f getMinBounding() const { return m_min_bounding; }
    Vec3f getMaxBounding() const { return m_max_bounding; }
	void translate(const Vec3f& o);
	void rotate(float z);
	//get members

	void reAlignIndex(); //realign index in polygon vector ==for transformation to model


public:
    // All the points in the model///
	std::vector<Vec3f> m_verts;
	//2d vector
	std::vector<Vec2f> m_2dverts;
	//vertex connection 
	std::vector<std::vector<int>>m_face_con;
    
    // All the triangles in the model
	std::vector<std::vector<int> > m_polys;

	//texture coordinate in the model(if exist)
	std::vector<std::vector<float>> m_tex_cord;

	//vertex normals
	std::vector<Vec3f> m_vert_norms;
	//face normals
	std::vector<Vec3f> m_face_norms;
	//face direction
	std::vector<bool> m_face_dir;

	/*	ultility parameters  */

	//distance of vertices to camera ---used for z-buffer
	std::vector<float> m_vert_dist;

	//transformaiton matrix
	//Mat4f TransformMatrix;

	//translate matrix
	//Mat4f TranslateMatrix;

protected:
	//interior functions

	//set rotation matrix to identity matrix
	//void SetRotationIndentity();

	//set transformation matrix to identity matrix
	//void SetTransformIndentity();

protected:
	//lightlist 
	std::vector<Light> lightlist;

	//rotation matrix
	//Mat4f Rotation_M;
	//center pivot
    Vec3f m_center;
    Vec3f m_min_bounding;
    Vec3f m_max_bounding;

//shading related
protected:
	Material material;

public:
	///////shading related functions///////
	//add ligh to light list
	void AddLight(Light &light);

	//material
	void setMaterial(Vec3f diff_col,Vec3f spec_col, int Specular_Level, int Specular_strength);
	void AssignMaterial(Material &newMaterial);

	/*Material *getMaterial();*/
	
	//set material attributes
	void setColor(Vec3f Am_col, Vec3f Dif_col, Vec3f Spe_col);  //set the color of the assigned material
	void setSpecularLevel(int SpecularLevel);
	//void setGlossy(int GLoss){
	//	material.setGlossy(GLoss);
	//}

	//get material attributes
	//Vec3f getAmbientColor(){
	//	return material.GetAmbientColor();
	//}
	/*Vec3f getDiffuseColor();
	Vec3f getSpecularColor();
	Vec3f getkd();
	Vec3f getks();*/
	/*Vec3f getka(){ return material.getKa(); }
	int getSpecular_level(){
		return material.getSpecularLevel();
	}
	int getGlossy(){
		return material.getGLossy();
	}

	int getMaterialIllumination(){
		return material.getIlluminationType();*/
	//}

	//other illumination model
	/*void shiftTOWard(Vec3f eps,Vec2f Roughness){
		material.WardModel(eps, Roughness);
	}*/

	//Vec2f getRoughness(){
	//	return material.getRoughness();
	//}
	//Vec3f getEsp(){
	//	return material.getEspi();
	//}
};

#endif