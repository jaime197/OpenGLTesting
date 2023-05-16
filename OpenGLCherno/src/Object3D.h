#pragma once
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector4f.h"
#include "Matrix4x4f.h"
#include "Vertex.h"
#include "InputManager.h"

class Object3D
{
public:
	Vector4f position;
	Vector4f rotation;
	Vector4f scale;
	Matrix4x4f modelMatrix;
	std::vector<Vertex> vertexList;
	std::vector<int> idList;
	GLuint vbo;


	Object3D() {
		position = Vector4f();
		rotation = Vector4f();
		scale = Vector4f();
		modelMatrix = Matrix4x4f().make_identify();
		vbo = 0;
	}
	void createTriangle();
	void move(double timeStep);
	void updateModelMatrix();
	void updateVertexPositions();
	void loadVertexData();
	GLuint getVBO() { return vbo; };
	int getVertexCount();
	
	


	//debugging methods
	void printMatrix(const Matrix4x4f& matrix) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << matrix.m[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void printVertexList(const std::vector<Vertex>& vertexList) {
		for (const Vertex& vertex : vertexList) {
			std::cout << "Vertexlist Position: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ", " << vertex.position.w << ")" << std::endl;
		}
	}
	void printObject() const {
		std::cout << "Object3D Information:\n";
		std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
		std::cout << "Rotation: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ")\n";
		std::cout << "Scale: (" << scale.x << ", " << scale.y << ", " << scale.z << ")\n";
		std::cout << "vbo: (" << vbo << ")\n";

		std::cout << "Model Matrix:\n";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << modelMatrix.m[i][j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "Vertex List:\n";
		for (const Vertex& vertex : vertexList) {
			std::cout << "Position: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ")\n";
		}
	}
	void printPositions(const Vertex* positions, size_t count)
	{
		std::cout << "Positions Contents: ";
		for (size_t i = 0; i < count; ++i)
		{
			std::cout << "(" << positions[i].position.x << ", " << positions[i].position.y << ", "
				<< positions[i].position.z << ", " << positions[i].position.w << ") ";
		}
		std::cout << std::endl;
	}

};

