#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "Vertex.h"
#include "Vector4f.h"
#include "render.h"
#include "Object3D.h"
#include "shaders.h"



int main()
{
    std::vector<Vertex> vertexList;
    Vertex v1, v2, v3;
    Vector4f vec1, vec2, vec3;
    v1.position = vec1.make_vector4f(0.0, 1.0, 0.0, 0.0);
    v2.position = vec2.make_vector4f(0.87, -0.5, 0.0, 0.0);
    v3.position = vec3.make_vector4f(-0.87, -0.5, 0.0, 0.0);

    vertexList.push_back(v1);
    vertexList.push_back(v2);
    vertexList.push_back(v3);

    Object3D triangulo = Object3D(vertexList);

    render renderer = render(640, 480, triangulo);
    renderer.initGL();

    // -----------------------------------------------------------------------------

    //Object3D triangulo = Object3D();
    //triangulo.createTriangle();

    //el siguiente codigo deberia ser usado desde createTriangle(). 
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexList.size(), triangulo.vertexList.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(0);
    //Codigo de createTriangle() acaba aqui


    // -----------------------------------------------------------------------------

    shaders s;
    GLuint sp = s.getShaders();

    renderer.putObject(&triangulo);
    renderer.mainLoop(vao, sp);

    glfwDestroyWindow(renderer.window);
    glfwTerminate();
}