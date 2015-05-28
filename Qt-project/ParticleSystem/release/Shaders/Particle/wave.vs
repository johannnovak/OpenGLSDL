#version 400

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform float amplitude;
uniform float t;

in vec3 position;
in float phase;
in vec3 color;

in float spawnTime;
in float ttl;

out vec4 fColor;

void main()
{
	vec4 pos = vec4(position.x, amplitude*sin(t-spawnTime +phase), position.z, 1.0f);
	gl_Position = P * V * W * pos;
	
	float intensity = 1;
	fColor = vec4(color, intensity);
}