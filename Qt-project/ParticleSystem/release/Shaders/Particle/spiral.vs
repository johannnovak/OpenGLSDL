#version 400

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform float t;
uniform float rMin;
uniform float rMax;
uniform float height;

in vec3 color;

in float spawnTime;
in float ttl;

out vec4 fColor;

float r(in float time)
{
	return (rMax - rMin) / ttl * time + rMin;
}

void main()
{
	float localTime = t-spawnTime;

	vec4 pos = vec4(r(localTime) * cos(localTime), height / ttl * localTime, r(localTime) * sin(localTime), 1.0f);
	gl_Position = P * V * W * pos;
	
	float intensity = step(spawnTime, t);
	fColor = vec4(color, intensity);
}