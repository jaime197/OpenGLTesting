#include <iostream>
#include "render.h"

render::render(int _x, int _y, Object3D _triangulo) {
	x = _x;
	y = _y;
	window = nullptr;
	triangulo = _triangulo;
}

void render::initGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(x, y, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	InputManager::initInputManager(window);
}

void render::putObject(Object3D* obj)
{
	objectList.push_back(obj);
}

void render::mainLoop(GLuint vao, GLuint sp)
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		//for (Object3D* object : getObjectList())
		//{
		//	object->move(0.016); // Example timeStep value of 0.016 seconds
		//}

		triangulo.move(0.016);

		drawGL();

		glUseProgram(sp);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
}

void render::drawGL()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * triangulo.vertexList.size(), triangulo.vertexList.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
