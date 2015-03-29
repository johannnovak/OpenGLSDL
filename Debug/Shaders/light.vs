#version 140

uniform mat4 W;
uniform mat4 V;
uniform mat4 P;

in vec3 pos;
in vec3 norm;
in vec3 col;

out vec3 fColor;

void main()
{
	vec3 LightDir = normalize(vec3(1.0f, 0.0f, -1.0f));
	vec3 LightColor = vec3(1.0f, 1.0f, 1.0f);

	gl_Position = P * V * W * vec4(pos, 1.0f);
	
	float intensity = clamp(dot(-LightDir, norm), 0, 1);
	fColor = intensity * vec3(col.r*LightColor.r, col.g*LightColor.g, col.b*LightColor.b);
}