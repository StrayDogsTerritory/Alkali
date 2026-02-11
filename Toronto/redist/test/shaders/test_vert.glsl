#version 410

layout(location=0) in vec4 avVertexPosition;
layout(location=2) in vec4 avVertexColour;
layout(location=3) in vec3 avUV;

layout(location=2) out vec4 ovColour;
layout(location=3) out vec3 ovUV;

void main()
{
	ovColour = avVertexColour;
	ovUV = avUV;	

	gl_Position = vec4(avVertexPosition);
}