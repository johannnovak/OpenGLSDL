#version 400

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

// in parameters
in vec3 pos;
in vec3 color;
in vec3 normal;

// out parameters
out vec3 vEye;
out vec3 nEye;

out vec3 fColor;

void main()
{
	gl_Position = P * V * W * vec4(pos, 1.0f);
	
	vEye = vec3(V * W * vec4(pos, 1.0));
	nEye = vec3(transpose(inverse(W)) * vec4(normal, 1));
	fColor = color;
}