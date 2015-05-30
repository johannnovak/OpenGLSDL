#version 400

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

uniform float t;

in vec3 position;
in vec3 speed;
in vec3 color;

in float spawnTime;
in float ttl;

out vec4 fColor;

void main()
{
	vec4 pos = vec4((t-spawnTime) * speed + position, 1.0f);
	gl_Position = P * V * W * pos;
	
	gl_PointSize = 50.0f;
	float intensity = -1.0f *(t - spawnTime) / ttl + 1.0f;
	// fColor = clamp(intensity * color, 0, 1);
	fColor = vec4(color, intensity);
}