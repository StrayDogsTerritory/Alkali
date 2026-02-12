#version 410 

#extension GL_ARB_explicit_uniform_location : enable

 layout(location=2) in vec4 Colour;
 layout(location=3) in vec3 UV;

out vec4 vFragColour;

layout(location=0) uniform sampler2D Test;

void main()
{
    // vFragColour = texture(Test, UV.xy);
	 
	// vFragColour = texture2D(Test, UV.xy);
	 vFragColour *= Colour;

}