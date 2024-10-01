#version 330 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 vTex;

layout (std140) uniform Orthogonal
{
    mat4 OrthogonalMatrix;
};

uniform mat4 TRS;

out vec2 uv;

void main()
{
	gl_Position = OrthogonalMatrix * (vec4(vPos, 0.0, 1.0) * TRS);

	uv = vTex;
}