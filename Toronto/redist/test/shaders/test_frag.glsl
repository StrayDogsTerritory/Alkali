#version 410 

#extension GL_ARB_explicit_uniform_location : enable

layout(location=0) in vec4 vColour;
// new line to quickly test this
layout(location=1) in vec3 avUV;

layout(location=0) out vec4 vFragColour;

uniform sampler2D aTex_Diffuse;

void main()
{
	float fFdx = dFdx(avUV.x);
	float fFdy = dFdy(avUV.y);

	vec2 vTexCoord = avUV.xy;
	//vFragColour = texture(aTex_Diffuse,avUV.xy);
	vFragColour = textureGrad(aTex_Diffuse, avUV.xy, vec2(fFdx), vec2(fFdy));
	vFragColour *= vec4(vColour);
}