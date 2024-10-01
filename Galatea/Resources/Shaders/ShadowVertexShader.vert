#version 450 core
layout (location = 0) in vec3 vPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 TRS;

void main()
{
    gl_Position = lightSpaceMatrix * TRS * vec4(vPos, 1.0);
}  