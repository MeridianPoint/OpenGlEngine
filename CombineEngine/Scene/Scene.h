//Scene.h
/*Usage: maain scene object handle all major operations and restore all objects
*/ 
#ifndef SCENE_H_
#define SCENE_H_

#include "stdafx.h"

class Scene
{
public:
	//item lists
	std::vector<Spatial*> Spatials;
	std::vector<Light*> LightList;
	std::vector<Model*> ModelList;
	std::vector<Material*> MaterialList;
	std::vector<Controller*> AnimationControllerList;
	std::vector<Camera*> CameraList;

	std::vector<GLint> ProgramIDlist;
	Crowd *crowdControl;

	Camera* render_Camera;

	RigidBodySimulator *simulator;

	//Vec3f Ka; //ambient 


public:
	Scene();
	~Scene();

	bool haveLight(){
		if (LightList.size() > 0){//light n
			return true;
		}
		else{
			return false;
		}
	}
	bool haveMaterials(){
		if (MaterialList.size() > 0){
			return true;
		}
		else{
			return false;
		}
	}
	bool haveAnimation(){
		if (AnimationControllerList.size() > 0){
			return true;
		}
		else{
			return false;
		}
	}

	///////////// access 
	void AddLight(Light *light){
		LightList.push_back(light);
	}
	void AddModel(Model *model){
		ModelList.push_back(model);
	}

	/*void AddController(Controller *controller){
		AnimationControllerList.push_back(controller);
	}*/

	void AddCamera(Camera &camera){
		CameraList.push_back(&camera);
	}

	void SetRenderCamera(unsigned int index){
		render_Camera = CameraList[index];
	}

	void AddSaptial(Spatial *pSpatial){
		Spatials.push_back(pSpatial);
	}
	/*void setAmbient(Vec3f ka){
		Ka = ka;
	}*/

	//bind light parameter
	void BindLight(GLint ProgramID,Light *light){
		if (light->getType() == LT_POINT){
			/*GLuint LightPosition = glUniform3fv(light);*/
		}
	}

	void BindLights(GLint ProgramID){
		if (haveLight()){
			//load light numbers
			int lightNumberLoc = glGetUniformLocation(ProgramID, "LightNumber");
			glUniform1i(lightNumberLoc, LightList.size());

			for (unsigned int i = 0; i < LightList.size(); i++){
					//
				BindLight(ProgramID,LightList[i]);
			}
		}
	}

	//drawn scene
	void Draw(){
		//refresh
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_BLEND);

		//load parameters
		for (unsigned int i = 0; i < MaterialList.size(); i++){
			//MaterialList[i].initiate();
		}

		//classic projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(-600, 600, -600, 600, -900, 900);

		int fov = 2 * atan(render_Camera->h()*render_Camera->Aspect() / render_Camera->n()) / PI * 180;
		gluPerspective(fov, render_Camera->Aspect(), render_Camera->n(), render_Camera->f());

		gluLookAt(render_Camera->getPosx(), render_Camera->getPosy(), render_Camera->getPosz(),
			render_Camera->getPosx() + render_Camera->getDircetx(), render_Camera->getPosy() + render_Camera->getDircety(), render_Camera->getPosz() + render_Camera->getDircetz(),
			render_Camera->getUpVectorx(), render_Camera->getUpVectory(), render_Camera->getUpVectorz());


		/*glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();*/
//draw ///////////////////////////////////////////////
		if (ModelList.size() > 0){ //scene not empty
			for (unsigned int i = 0; i < ModelList.size(); i++){
				//MaterialList[ModelList[i].getMaterialID()].bind
				glUseProgram(ModelList[i]->getMaterialID());
				BindLights(ModelList[i]->getMaterialID());
#ifdef modernDraw
				ModelList[i]->getCameraParameters(render_Camera);
				ModelList[i]->VBODraw();
#endif
				ModelList[i]->ClassicDraw(SMOOTH, UV_LACK);
			}
		}
	}


	//Update for animation
	void Update(double time){
		/*for (unsigned int i = 0; i < AnimationControllerList.size(); i++){
			AnimationControllerList[i]->Update((float)time);
		}*/
		crowdControl->Update(time);
	}

	void AddCrowdControl(Crowd* pCrowControl){
		crowdControl = pCrowControl;
	}

	void Clear(){
		for (int i = ModelList.size() - 1; i > 0; i--){
			Model* temp;
			temp = ModelList[i];
			ModelList.pop_back();
			delete temp;
		}
	}
};

#endif // SCENE_H_