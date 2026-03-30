#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool enabled; // Bandera para prender/apagar
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;

// Declaramos nuestras dos luces
uniform Light light1; // El Sol
uniform Light light2; // La Luna

// Usamos el nombre estándar que usa Assimp/Model.h para las texturas
uniform sampler2D texture_diffuse1; 

// Función para calcular la luz individualmente
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if(!light.enabled) {
        return vec3(0.0); // Si la luz está apagada, no aporta color
    }

    // Ambiente
    vec3 ambient = light.ambient * material.diffuse;

    // Difusa
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;

    // Especular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    return (ambient + diffuse + specular);
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Sumamos el impacto del Sol y la Luna
    vec3 result = CalcLight(light1, norm, FragPos, viewDir);
    result += CalcLight(light2, norm, FragPos, viewDir);

    vec4 texColor = texture(texture_diffuse1, TexCoords);
    if(texColor.a < 0.1) discard; // Descartar transparencias

    color = vec4(result, 1.0f) * texColor;
}