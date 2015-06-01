#version 110

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform float t;

attribute vec3 position;
attribute vec3 speed;
attributen vec3 acceleration;
attribute vec3 color;

attribute float spawnTime;
attribute float ttl;

varying vec4 fColor;

void main()
{
	float localTime = t-spawnTime;
	vec4 pos = vec4(localTime * localTime * acceleration + localTime * speed + position, 1.0f);
	gl_Position = P * V * W * pos;
	
	float intensity = -4.0f/(ttl*ttl) * localTime * localTime + 4.0f/ttl * localTime;
	fColor = vec4(color, intensity);
}
