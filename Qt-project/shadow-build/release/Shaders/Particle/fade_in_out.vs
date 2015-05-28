#version 300 es

precision highp float;

uniform highp mat4 W;
uniform highp mat4 V;
uniform highp mat4 P;

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
	float localTime = t-spawnTime;
	highp vec4 pos = vec4(localTime * localTime * acceleration + localTime * speed + position, 1.0f);
	gl_Position = P * V * W * pos;
	
	float intensity = -4.0f/(ttl*ttl) * localTime * localTime + 4.0f/ttl * localTime;
	fColor = vec4(color, intensity);
}
