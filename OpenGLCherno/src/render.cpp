#include <iostream>
#include "render.h"

GLFWwindow* render::createWindow() {
	return glfwCreateWindow(640, 480, "My GLFW Window", NULL, NULL);
}

render::render(int x, int y) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	window = createWindow();
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
}

void render::initGL()
{
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}

	InputManager::initInputManager(window);
}

void render::putObject(Object3D* obj)
{
	objectList.push_back(obj);
}

void render::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Clear the framebuffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Update window events
		glfwPollEvents();

		// Update the state of objects by calling their "move" method
		for (Object3D* object : getObjectList())
		{
			object->move(0.016); // Example timeStep value of 0.016 seconds
		}

		// Draw objects on the screen
		drawGL();

		// Swap buffers to display the rendered image
		glfwSwapBuffers(window);
	}
}

void render::drawGL()
{
	// Iterate over the list of objects
	for (Object3D* object : objectList)
	{
		// Load object's vertex data onto the GPU
		object->loadVertexData();

		// Enable vertex attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Draw the object's geometry
		glDrawArrays(GL_TRIANGLES, 0, object->getVertexCount());

		// Disable vertex attributes
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


}
