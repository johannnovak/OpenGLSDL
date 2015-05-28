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
	float localTime = t - spawnTime;
	vec4 pos = vec4(acceleration * localTime * localTime + speed * localTime + position, 1.0f);
	gl_Position = P * V * W * pos;
	
	float intensity = -localTime/ttl + 1.0f;
	fColor = vec4(color, intensity);
}