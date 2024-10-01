#version 330 core

layout(location = 0) in vec4 vPosTex;

layout (std140) uniform Orthogonal
{
    mat4 OrthogonalMatrix;
};

out vec2 uv;

void main()
{
	gl_Position = OrthogonalMatrix * (vec4(vPosTex.xy, 0.0, 1.0));

	uv = vPosTex.zw;
}