/*
 *  PolyModel.cpp
 *
 *  Created by Robert Falk
 *
 */
#include "stdafx.h"
#include "PolyModel.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>


#include <GL/glut.h>

using namespace std;

//compute face/polygon normal for shading
void PolyModel::computeFaceNormals()
{
	m_face_norms.resize(m_polys.size());
	m_face_con.resize(m_verts.size());
	//traverse polygons
	for (int i = 0; i < m_polys.size(); i++){
		for (int j = 0; j < m_polys[i].size(); j++){
			m_face_con[m_polys[i][j]-1].push_back(i);
		}
		//get 2 vectors from one polygon
		Vec3f vector1 = m_verts[m_polys[i][1]-1] - m_verts[m_polys[i][0]-1];
		Vec3f vector2 = m_verts[m_polys[i][m_polys[i].size()-1] - 1] - m_verts[m_polys[i][0] - 1];
		//get cross product
		Vec3f normal = vector1.cross(vector2);

		normal.normalize();
		m_face_norms[i] = normal;
	}
}

//compute vertex normal for shading --phong shading and more advanced shading
void PolyModel::computeVertexNormals()
{
	m_vert_norms.resize(m_verts.size());
	//traverse verteces
	for (int iVer = 0; iVer < m_face_con.size(); iVer++){
		Vec3f ver_norm = Vec3f(0, 0, 0);
		for (int j = 0; j < m_face_con[iVer].size(); j++){
			ver_norm += m_face_norms[m_face_con[iVer][j]];
		}
		ver_norm.normalize();
		m_vert_norms[iVer] = ver_norm;
	}
	//for (int iVer = 0; iVer < m_verts.size(); iVer++){
	//	//restore face normals temperaly
	//	vector<Vec3f> face_norms;
	//	for (int i = 0; i < m_polys.size(); i++){
	//		for (int j = 0; j < m_polys[i].size(); j++){
	//			if (m_polys[i][j] == iVer){
	//				face_norms.push_back(m_face_norms[i]);
	//			}
	//		}
	//	}
	//	Vec3f ver_norm = Vec3f(0, 0, 0);
	//	for (int n = 0; n < face_norms.size(); n++){
	//		ver_norm += face_norms[n];
	//	}
	//	ver_norm.normalize();
	//	m_vert_norms[iVer] = ver_norm;
	//}
}

void PolyModel::translate(const Vec3f& o)
{
	//translate Matrix
	glTranslatef(o.x(),o.y(),o.z());
	/*glPushMatrix();
	glPopMatrix();*/
}

void PolyModel::rotate(float z)
{
	glRotatef(z,0.0f,0.0f,1.0f);
}

void PolyModel::debugdraw(){
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
		for (unsigned int i = 0; i < m_polys.size();i++){
			for (unsigned int j = 0; j < m_polys[i].size(); j++){
				glVertex3f(m_verts[m_polys[i][j] - 1].x(), m_verts[m_polys[i][j] - 1].y(), m_verts[m_polys[i][j] - 1].z());
			}
			
		}
	glEnd();
}
float* PolyModel::dataArray(){
	float *fResult;
	vector<float> VBO;
	for (int i = 0; i < m_polys.size(); i++)
	{
		//check back facing
		if (!m_face_dir[i]){
			continue;
		}
		//traverse lines in each polygon
		for (unsigned int j = 0; j < m_polys[i].size(); j++){
			if (j == (m_polys[i].size() - 1)){
				VBO.push_back(m_verts[m_polys[i][j] - 1].x());
				VBO.push_back(m_verts[m_polys[i][j] - 1].y());
				VBO.push_back(m_verts[m_polys[i][j] - 1].z());

				VBO.push_back(m_verts[m_polys[i][0] - 1].x());
				VBO.push_back(m_verts[m_polys[i][0] - 1].y());
				VBO.push_back(m_verts[m_polys[i][0] - 1].z());
				continue;
			}
			VBO.push_back(m_verts[m_polys[i][j] - 1].x());
			VBO.push_back(m_verts[m_polys[i][j] - 1].y());
			VBO.push_back(m_verts[m_polys[i][j] - 1].z());

			VBO.push_back(m_verts[m_polys[i][j+1] - 1].x());
			VBO.push_back(m_verts[m_polys[i][j+1] - 1].y());
			VBO.push_back(m_verts[m_polys[i][j + 1] - 1].z());
		}
	}
	fResult = &VBO[0];
	return fResult;
}

void PolyModel::draw()
{
	glLineWidth(1.0f);

    // Draw each triangle... //GL_LINE_LOOP
	glPointSize(1.2f);
	//draw all points
	/*glBegin(GL_POINTS);
	for (int i = 0; i < m_verts.size(); i++)
	{
		glVertex3f(m_verts[i].x(), m_verts[i].y(), m_verts[i].z());
	}
	glEnd();*/

	//draw all lines
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1.2f);
	//travese polygons
	for (int i = 0; i < m_polys.size();i++)
	{
		//check back facing
		if (!m_face_dir[i]){
			continue;
		}
		//traverse lines in each polygon
		for (int j = 0; j < m_polys[i].size(); j++){
			if (j ==( m_polys[i].size() - 1)){
				glVertex3f(m_verts[m_polys[i][j] - 1].x(), m_verts[m_polys[i][j] - 1].y(), m_verts[m_polys[i][j] - 1].z());
				glVertex3f(m_verts[m_polys[i][0] - 1].x(), m_verts[m_polys[i][0] - 1].y(), m_verts[m_polys[i][0] - 1].z());
				continue;
			}
			glVertex3f(m_verts[m_polys[i][j]-1].x(), m_verts[m_polys[i][j]-1].y(), m_verts[m_polys[i][j]-1].z());
			glVertex3f(m_verts[m_polys[i][j+1] - 1].x(), m_verts[m_polys[i][j+1] - 1].y(), m_verts[m_polys[i][j+1] - 1].z());
		}
	}
	glEnd();
}


void PolyModel::draw2d(){
	glLineWidth(1.0f);

	// Draw each triangle... //GL_LINE_LOOP
	glPointSize(1.2f);
	//glBegin(GL_POINTS);
	//for (int i = 0; i < m_2dverts.size(); i++)
	//{
	//	glVertex2f(m_2dverts[i].x(), m_2dverts[i].y());
	//}
	//glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(1.2f); for (int i = 0; i < m_polys.size(); i++)
	{
		if (!m_face_dir[i]){
			continue;
		}
		for (int j = 0; j < m_polys[i].size(); j++){
			if (j == (m_polys[i].size() - 1)){
				glVertex2f(m_2dverts[m_polys[i][j] - 1].x(), m_2dverts[m_polys[i][j] - 1].y());
				glVertex2f(m_2dverts[m_polys[i][0] - 1].x(), m_2dverts[m_polys[i][0] - 1].y());
				continue;
			}
			glVertex2f(m_2dverts[m_polys[i][j] - 1].x(), m_2dverts[m_polys[i][j] - 1].y());
			glVertex2f(m_2dverts[m_polys[i][j+1] - 1].x(), m_2dverts[m_polys[i][j+1] - 1].y());
		}
	}
	glEnd();
}

bool PolyModel::loadModel(std::istream& istr, bool reverse)
{
	int vertex_count;
	int face_count;
	string data;

	if (!istr.good())
		return false;

	char line[1024];
	istr.getline(line, 1024);

	std::istringstream sstr(line);
	sstr >> data >> vertex_count >> face_count;

	//store readbuffer
	std::streambuf* backup;
	backup = sstr.rdbuf();
	//get position
	sstr.seekg(0, sstr.cur);
	int cur = sstr.tellg();

	std::string attrib_type;
	bool has_texcoords = false;
	while (!sstr.eof() && sstr.good()) {
		sstr >> attrib_type;
		if (attrib_type == "tex-coords1")
			has_texcoords = true;
	}
	sstr.seekg(cur-1, sstr.beg);
	string test;
	sstr >> test;
	
	m_verts.resize(vertex_count);
	m_polys.resize(face_count);

	m_center = 0.0f;
	m_max_bounding = -numeric_limits<float>::max();
	m_min_bounding = numeric_limits<float>::max();
    
    // Read in all the points
	//sstr << backup;
	
	float x, y, z;
	for (int i=0; i < vertex_count;i++){
		char new_line[1024];
		istr.getline(new_line, 1024);
		std::istringstream new_sstr(new_line);
		new_sstr >> x >> y >> z;
		m_verts[i] = Vec3f(x, y, z);
	}
    // Read in all the polygons (triangles)
	int vertex_p_poly;
	for (int i=0; i < face_count; i++){
		char new_line[1024];
		istr.getline(new_line, 1024);
		std::istringstream new_sstr(new_line);
		new_sstr >> vertex_p_poly;
		vector<int> vTemp(vertex_p_poly);
		for (int j=0; j < vertex_p_poly; j++){
			new_sstr >> vTemp[j];
		}
		m_polys[i]=vTemp;
	}
	// Read in all texture coordinates
	if (has_texcoords){
		int Num_cord;
		while (!istr.eof() && istr.good()){
			char new_line[1024];
			istr.getline(new_line, 1024);
			std::istringstream new_sstr(new_line);
			new_sstr >> Num_cord;
			vector<float> fTemp(Num_cord);
			for (int j = 0; j < Num_cord; j++){
				new_sstr >> fTemp[j];
			}
			m_tex_cord.insert(m_tex_cord.end(), fTemp);
		}
	}
	//compute 
	computeFaceNormals();
	computeVertexNormals();

	//set rotation to identity
	//SetRotationIndentity();
	//SetTransformIndentity();
	//TranslateMatrix = Mat4f(
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//	);
	
	return true;
}

//protected funcitons
//void PolyModel::SetRotationIndentity(){
//	Rotation_M = Mat4f(
//		1.0f, 0.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//		);
//}
//
//void PolyModel::SetTransformIndentity(){
//	TransformMatrix = Mat4f(
//		1.0f, 0.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//		);
//}


/////////material //////////////
//add ligh to light list
void PolyModel::AddLight(Light &light){
	lightlist.push_back(light);
}

//material
//void PolyModel::setMaterial(Vec3f diff_col, Vec3f spec_col, int Specular_Level, int Specular_strength){
//	material.setDiffuseColor(diff_col);
//	material.setSpecularColor(spec_col);
//	material.setSpecularLevel(Specular_Level);
//}
//void PolyModel::AssignMaterial(Material &newMaterial){
//	material = newMaterial;
//}

//Material PolyModel::*getMaterial(){
//	return &material;
//}

//// set attribute //////////////////
//void PolyModel::setColor(Vec3f Am_col, Vec3f Dif_col, Vec3f Spe_col){  //set the color of the assigned material
//	material.setColor(Am_col,Dif_col,Spe_col);
//}
//void PolyModel::setSpecularLevel(int SpecularLevel){
//	material.setSpecularLevel(SpecularLevel);
//}


//////////////get attributes from material ////////////////////

//Vec3f PolyModel::getDiffuseColor(){
//	return material.GetDiffuseColor();
//}
//Vec3f PolyModel::getSpecularColor(){
//	return material.GetSpecularColor();
//}
//Vec3f PolyModel::getkd(){
//	return material.getKd();
//}
//Vec3f PolyModel::getks(){
//	return material.getKs();
//}

void PolyModel::reAlignIndex(){ //realign index in polygon vector ==for transformation to model
	//
	for (int i = 0; i < m_polys.size(); i++){
		for (int j = 0; j < m_polys[i].size(); j++){
			m_polys[i][j]--;
		}
	}
}