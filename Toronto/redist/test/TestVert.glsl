#version 460 

layout (location = 0) in vec3 avPos;

void main()
{
    gl_position = vec4(avPos.x, avPos.y, avPos.z. , 1.0);
}