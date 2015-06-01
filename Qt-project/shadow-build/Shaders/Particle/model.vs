#version 400

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform float t;

in vec3 position;
in vec3 speed;
in vec3 acceleration;
in vec3 color;

in float spawnTime;
in float ttl;

out vec4 fColor;

void main()
{
	vec4 pos = 
	gl_Position = P * V * W * pos;
	
	float intensity = 
	fColor = vec4(color, intensity);
}