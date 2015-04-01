#version 140

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

vec3 LightDirection1 = vec3(0, 0, -1);

in vec3 pos;
in vec3 normal;

out float fIntensity;

void main()
{
	gl_Position = P * V * W * vec4(pos, 1.0f);
	fIntensity = clamp(dot(LightDirection1, normal), 0, 1);
}