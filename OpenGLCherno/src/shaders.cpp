#include "shaders.h"

GLuint shaders::getShaders()
{
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = R"(
        #version 460
        in vec2 vp;
        void main() {
            gl_Position = vec4(vp, 0, 1);
        }
    )";
    glShaderSource(vs, 1, &vertexSource, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragSource = R"(
        #version 460
        out vec4 color;
        void main() {
            color = vec4(1, 0, 0, 1);
        }
    )";
    glShaderSource(fs, 1, &fragSource, nullptr);
    glCompileShader(fs);

    GLuint sp = glCreateProgram();
    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);

	return sp;
}
