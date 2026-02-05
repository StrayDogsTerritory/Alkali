#version 410

layout(location=0) in vec4 vVertexPosition;
layout(location=2) in vec4 vVertexColour;
layout(location =3) in vec3 avUV;

layout(location=2) out vec4 vColour;

void main()
{
	vColour = vVertexColour;
	
	gl_Position = vec4(vVertexPosition);
}