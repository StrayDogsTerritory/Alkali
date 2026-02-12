#version 410

layout(location=0) in vec4 vVertexPosition;
layout(location=1) in vec3 vVertexNormal;
layout(location=2) in vec4 vVertexColour;
layout(location=3) in vec3 vUv;

layout(location=0) out vec4 vColour;

layout(location=1) out vec3 avUV;


void main()
{
	vColour = vVertexColour;
	avUV = vUv;

	gl_Position = vec4(vVertexPosition);
}