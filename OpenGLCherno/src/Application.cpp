#include <iostream>

#include "Vector4f.h"
#include "Matrix3x3f.h"
#include "Matrix4x4f.h"
#include "render.h"
#include "ShaderProgramSource.h"
#include <GLFW/glfw3.h>

int main()
{
	render renderer = render(640, 480);
	InputManager inputManager = InputManager();

	renderer.initGL();

	Object3D triangulo = Object3D();
	triangulo.createTriangle();

	renderer.putObject(&triangulo);

	ShaderProgramSource source = source.ParseShader("shaders/Basic.shader");
	unsigned int shader = source.CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	GLint location = glGetUniformLocation(shader, "u_Color");
	glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

	renderer.mainLoop();

	return 0;
}






