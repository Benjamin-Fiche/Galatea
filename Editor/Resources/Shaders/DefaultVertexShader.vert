#version 450 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec3 vTangent;

layout (std140) uniform ViewProj
{
    mat4 viewProj;
};

uniform mat4 TRS;
uniform vec3 viewPos;

out VS_OUT
{
    vec2 uv;
    vec3 normal;
    vec3 vertPos;
    vec3 viewDir;
    mat3 reverseTBN;
} vs_out;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(TRS)));
    //Calcul pour la normal map
    vec3 T = normalize(vec3(normalMatrix * vTangent));
    vec3 N = normalize(vec3(normalMatrix * vNormal));

    T = normalize(T - dot(T,N) * N);    //Realignement de la tangent pour eviter les derives
    vec3 B = cross(N, T);               //Calcul de la Bitangent
    mat3 TBN = mat3(T, B, N);           //On ne transpose pas car au lieu de tout passer dans le repert de la tangent, on passe la tangent dans le repert du monde

    vs_out.uv = vTex;
    vs_out.normal = normalize(vec3(transpose(inverse(TRS)) * vec4(vNormal, 1.0)));
    vs_out.vertPos = vec3(TRS * vec4(vPos, 1.0));
    vs_out.reverseTBN = TBN;
    vs_out.viewDir = normalize(viewPos - vs_out.vertPos);

    gl_Position = viewProj * TRS * vec4(vPos, 1.0);
}