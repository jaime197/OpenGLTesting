#include "Object3D.h"

void Object3D::createTriangle()
{
    vertexList.clear();  // clear the current vertex list

    Vertex v1, v2, v3;
    Vector4f vec1, vec2, vec3;

    v1.position = vec1.make_vector4f(0.0, 1.0, 0.0, 0.0);
    v2.position = vec2.make_vector4f(0.87, -0.5, 0.0, 0.0);
    v3.position = vec3.make_vector4f(-0.87, -0.05, 0.0, 0.0);

    // add the vertices to the vertex list
    vertexList.push_back(v1);
    vertexList.push_back(v2);
    vertexList.push_back(v3);

    // Generate and bind a new vertex buffer object (VBO)
    glGenBuffers(1, &vbo);
}

void Object3D::move(double timeStep)
{
    rotation.reset();
    scale.reset();
    position.reset();

    // Check if the 'D' key is pressed
    if (InputManager::getKeyState(GLFW_KEY_D)) {
        double rotationSpeed = 45.0; // degrees per second
        double rotationAmount = rotationSpeed * timeStep;
        rotation.y += rotationAmount;
        std::cout << "right" << std::endl;
    }

    // Check if the 'A' key is pressed
    if (InputManager::getKeyState(GLFW_KEY_A)) {
        double rotationSpeed = 45.0; // degrees per second
        double rotationAmount = rotationSpeed * timeStep;
        rotation.y -= rotationAmount;
        std::cout << "left" << std::endl;
    }

    // Update the model matrix
    updateModelMatrix();
    updateVertexPositions();
}

void Object3D::updateModelMatrix()
{
    // Create the translation matrix
    Matrix4x4f transMatrix = Matrix4x4f().make_translate(position.x, position.y, position.z);

    // Create the rotation matrix
    Matrix4x4f  rotationMatrix = Matrix4x4f().make_rotate(rotation.x, rotation.y, rotation.z);

    // Create the scale matrix
    Matrix4x4f scaleMatrix = Matrix4x4f().make_scale(scale.x, scale.y, scale.z);

    // Combine the transformations in the desired order
    //modelMatrix = transMatrix * rotationMatrix * scaleMatrix;
}

void Object3D::updateVertexPositions() {
    // Update the positions of the vertices in the vertexList based on the model matrix
    for (Vertex& vertex : vertexList) {
        vertex.position = modelMatrix * vertex.position;
    }
}

void Object3D::loadVertexData()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Get the size of the vertex data in bytes
    size_t dataSize = vertexList.size() * sizeof(Vertex);

    //printPositions(vertexList.data(), vertexList.size());

    // Copy the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, dataSize, vertexList.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
}

int Object3D::getVertexCount()
{
    return vertexList.size();
}
