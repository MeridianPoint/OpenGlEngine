// CombineEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//miacro and 
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

//static variables
Scene Main_Scene;



void Initiate();

int _tmain(int argc, _TCHAR* argv[])
{
	//------------------Initate OpenGL ---------------
	
	//init glfw
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	//Iniate OpenGL using glfw

	GLFWwindow* window;
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Lab2: Heirachy animation", NULL, NULL);

	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental = true; // Needed in core profile 
	//Initate glew
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//--end of opengl Initation -------------------

	//---initate scene--------------------------

	//function to modify scene
	Initiate();


	//--end of scene initation------------

	//---OpenGL main Loop-------------

	// get start time for animation
	double start_time = glfwGetTime();

	//main loop
	do{
		//main
		double cur_time = glfwGetTime();
		double elapse_time = cur_time - start_time;
		//update main scene --if animation is used
		Main_Scene.Update(elapse_time);
		//draw main scene
		Main_Scene.Draw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);
	//----end of main loop------------------


	return 0;
}


//funciton to add object and fucntions to scene
void Initiate(){
	//Initate
}
