#version 330 core //Koju verziju GLSL jezika da koristim (za programabilni pipeline: GL verzija * 100) i koji profil (core - samo programabilni pajplajn, compatibility - core + zastarjele stvari)

//Kanali (in, out)
in vec4 chCol; //Kanal iz Verteks sejdera - mora biti ISTOG IMENA I TIPA kao u vertex sejderu
out vec4 outCol; //Izlazni kanal koji ce biti zavrsna boja tjemena

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec4 objectColor;
uniform float ambientStrength;


void main() //Glavna funkcija sejdera
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * vec3(objectColor.xyz);
    outCol = vec4(result, objectColor.a);
}

