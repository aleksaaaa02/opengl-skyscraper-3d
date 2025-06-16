#version 330 core //Koju verziju GLSL jezika da koristim (za programabilni pipeline: GL verzija * 100) i koji profil (core - samo programabilni pajplajn, compatibility - core + zastarjele stvari)

//Kanali (in, out)
in vec3 Normal; //Kanal iz Verteks sejdera - mora biti ISTOG IMENA I TIPA kao u vertex sejderu
in vec3 FragPos;
out vec4 outCol; //Izlazni kanal koji ce biti zavrsna boja tjemena

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec4 objectColor;
uniform float ambientStrength;


void main() //Glavna funkcija sejdera
{
    // Ambient
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vec3(objectColor);
    outCol = vec4(result, objectColor.a);
}

