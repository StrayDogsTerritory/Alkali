#version 410 

#extension GL_ARB_explicit_uniform_location : enable

layout(location=0) in vec4 vColour;
layout(location=0) out vec4 vFragColour;

layout(location=1) uniform sampler2D Test;

void main()
{
     vFragColour = vec4(vColour);
}