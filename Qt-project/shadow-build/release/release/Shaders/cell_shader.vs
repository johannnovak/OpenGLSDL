#version 140

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform int pass;

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 fColor;

void main()
{
	float thickness = 0.5f;

	if(pass == 0)
	{
		gl_Position = P * V * W * vec4(position + normal*thickness, 1.0f);
		fColor = vec3(0, 0, 0);
	}
	
	if(pass == 1)
	{
		gl_Position = P * V * W * vec4(position, 1.0f);
		fColor = color;
	}
}