#version 120 

#extension GL_ARB_texture_rectangle : enable
#extension GL_ARB_draw_buffers : enable

varying out vec4 vFinalColour;

void main()
{
     vFinalColour = vec4(1.0, 1.0, 1.0, 1.0);
}