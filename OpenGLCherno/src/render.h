#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Object3D.h"
#include "InputManager.h"

class render
{
	int x;
	int y;
public:
	GLFWwindow* window;
	std::vector<Object3D*> objectList;
	Object3D triangulo;

	render(int x, int y, Object3D triangulo);
	void initGL();
	void putObject(Object3D* obj);
	void drawGL();
	void mainLoop(GLuint vao, GLuint sp);

	std::vector<Object3D*> getObjectList() { return objectList;	};
};

