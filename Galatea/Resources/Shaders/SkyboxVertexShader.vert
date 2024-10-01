#version 450 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;
layout(location = 2) in vec3 vNormal;

layout (std140) uniform ViewProj
{
    mat4 viewProj;
};

uniform mat4 TRS;

out vec2 uv;

void main()
{
    vec4 pos = viewProj * TRS * vec4(vPos.xyz, 1.0);
    gl_Position = pos.xyww;
    uv = vTex;
}