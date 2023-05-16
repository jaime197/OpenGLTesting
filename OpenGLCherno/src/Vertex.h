#pragma once
#include "Vector4f.h"

struct Vertex {
	Vector4f position;

	void printVertex() {
		std::cout << "Vertex Position: (" << position.x << ", " << position.y << ", "
			<< position.z << ", " << position.w << ")" << std::endl;
	}
};