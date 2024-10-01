#version 450 core

out vec4 gl_FragColor;

in vec2 uv;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{    
    gl_FragColor = vec4(textColor,  texture(tex, uv).r);
}  