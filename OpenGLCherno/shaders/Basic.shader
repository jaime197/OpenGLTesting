#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, position.w);;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
};