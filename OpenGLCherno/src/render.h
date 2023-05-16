#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Object3D.h"
#include "InputManager.h"

class render
{
public:
	GLFWwindow* window = nullptr;
	std::vector<Object3D*> objectList;

	render(int x, int y);
	void initGL();
	void putObject(Object3D* obj);
	void drawGL();
	void mainLoop();

	std::vector<Object3D*> getObjectList() { return objectList;	};

	GLFWwindow* createWindow();

};

