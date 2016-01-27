#ifndef Material_h__
#define Material_h__
//#include "stdafx.h"

enum TextureTYPE {TT_DIFFUSE,TT_SPECULAR,TT_NORMAL,TT_PARALLEX};

class Material
{
protected:
	
	GLuint ProgramID;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
    //texture map
	//std::list<Texture_Map> MapList;
public:
	Material();
	Material(std::string vertexshader,std::string fragmentshader);
	virtual ~Material();
	void alignTexture();
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

	//specified functions
	void setColor(Vec3f color);
	void setID(GLint ID);
};



#endif // Material_h__


