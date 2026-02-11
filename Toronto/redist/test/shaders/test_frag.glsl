#version 410 

#extension GL_ARB_explicit_uniform_location : enable

 in vec4 Colour;
 in vec3 UV;

out vec4 vFragColour;

uniform sampler2D Test;

void main()
{
     vFragColour = texture(Test, UV.xy);

}