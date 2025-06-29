#version 330 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 projection;

out vec2 TexCoords;


void main()
{
    gl_Position = projection * vec4(inPosition.xy, 0.0, 1.0);
    TexCoords = inTexCoords;
}
