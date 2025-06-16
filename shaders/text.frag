#version 330 core

in vec2 TexCoords;

out vec4 fragColor;

uniform sampler2D uText;

void main()
{
    fragColor = texture(uText, TexCoords);
}