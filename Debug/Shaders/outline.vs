#version 140

uniform mat4 W;
uniform mat4 P;
uniform mat4 V;

in vec3 position;
in vec3 normal;

void main()
{
	float thickness = 0.01f;
	gl_Position = P * V * W * vec4(position + (normalize(normal) * thickness), 1.0);
}