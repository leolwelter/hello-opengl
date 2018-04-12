#version 330 core
# define NR_POINT_LIGHTS 1

struct Material {
    float shininess;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 playerPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;

vec3 lightCalc(PointLight);

void main()
{
    // for each light source, calculate contribution
    vec3 lightOutput = vec3(0.0f);
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        lightOutput += lightCalc(pointLights[i]);
    }

    FragColor = vec4(lightOutput, 1.0f) * mix(texture(tex1, vTexCoord), texture(tex2, vec2(1.0 - vTexCoord.x, vTexCoord.y)), 0.2);
}

vec3 lightCalc(PointLight light) {
    // direction vectors
    vec3 norm = normalize(vNormal);
    vec3 lDir = normalize(light.position - fragPos);
    vec3 playerDir = normalize(playerPos - fragPos);
    vec3 lReflect = reflect(-lDir, norm);

    // simple ambient constant
    vec3 ambientLight = light.ambient * material.ambient;

    // calculate diffuse component
    float diffuseIntensity = max(dot(norm, lDir), 0.0f);
    vec3 diffuseLight = diffuseIntensity * light.diffuse * material.diffuse;

    // calculate specular component
    float specularIntensity = pow(max(dot(playerDir, lReflect), 0.0f), material.shininess);
    vec3 specularLight = specularIntensity * light.specular * material.specular;

    // attenuate all light based on distance
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    ambientLight *= attenuation;
    diffuseLight *= attenuation;
    specularLight *= attenuation;


    return diffuseLight + specularLight + ambientLight;
}