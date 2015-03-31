#version 140

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

in vec3 pos;

void main()
{
	gl_Position = P * V * W * vec4(pos, 1.0f);
}