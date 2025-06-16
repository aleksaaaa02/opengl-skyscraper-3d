#version 330 core //Koju verziju GLSL jezika da koristim (za programabilni pipeline: GL verzija * 100) i koji profil (core - samo programabilni pipeline, compatibility - core + zastarjele stvari)

//Kanali (in, out)
layout(location = 0) in vec3 inPos; //Pozicija tjemena
layout(location = 1) in vec3 inNormal; //Boja tjemena - ovo saljemo u fragment sejder

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() //Glavna funkcira sejdera
{
    FragPos = vec3(model * vec4(inPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * inNormal;
    gl_Position = projection * view * model * vec4(inPos.xyz, 1.0);
}
