#version 410 

#extension GL_ARB_explicit_uniform_location : enable

layout(location=0) in vec4 vColour;
// new line to quickly test this
layout(location=1) in vec3 avUV;

layout(location=0) out vec4 vFragColour;

uniform sampler2D aTex_Diffuse;

void main()
{

	vec2 vTexCoord = avUV.xy;
	vFragColour = texture(aTex_Diffuse,avUV.xy);
	vFragColour *= vec4(vColour);
}