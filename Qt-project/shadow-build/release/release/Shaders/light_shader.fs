#version 400

in vec3 vEye;
in vec3 nEye;

in vec3 fColor;

out vec4 fragColor;

// Light Constant
vec3 ambiantColors = vec3(1, 1, 1);
float ambiantIntensity = 0.33f;

vec3 diffusePosition = vec3(0, 20, 0);
vec3 diffuseColors = vec3(1, 1, 1);
float diffuseIntensity = 0.33f;

vec3 specularColors = vec3(1, 1, 1);
float specularIntensity = 0.33f;

void main()
{
	vec3 L = normalize(diffusePosition - vEye);
	vec3 E = normalize(-vEye);
	vec3 R = normalize(-reflect(L, nEye));

	vec3 ambiant = ambiantIntensity * ambiantColors;
	vec3 diffuse = max(dot(nEye, L), 0.0) * diffuseIntensity * diffuseColors;
	diffuse = clamp(diffuse, 0.0, 1.0);
	vec3 specular = specularColors * pow(max(dot(R, E), 0.0), 10*0.3);
	specular = clamp(specular, 0.0, 1.0);
	fragColor = vec4(fColor + ambiant + diffuse + specular, 1.0f);
}