#version 450 core

out vec4 gl_FragColor;

in vec2 uv;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, uv);
} 