#version 410 

#extension GL_ARB_explicit_uniform_location : enable

layout(location=2) in vec4 avColour;

out vec4 vFragColour;

layout(location=1) uniform sampler2D Test;

void main()
{
     vFragColour = vec4(avColour);

}