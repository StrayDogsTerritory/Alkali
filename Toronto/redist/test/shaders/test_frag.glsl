#version 410 

layout(location=0) in vec4 vColour;
layout(location=0) out vec4 vFragColour;

void main()
{
     vFragColour = vec4(vColour);
}