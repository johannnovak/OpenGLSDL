#version 140

in float fIntensity;

out vec4 fragColor;

void main()
{
	fragColor = fIntensity*vec4(1.0f, 1.0f, 1.0f, 1.0f);
}