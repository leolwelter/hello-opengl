#version 330 core
# define NR_POINT_LIGHTS 5
# define NR_DIR_LIGHTS 1
# define NR_SPOT_LIGHTS 1

struct Material {
    float shininess;
    vec3 ambient;
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

struct DirectionalLight {
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 spotDir;
    float cutoffAngle;
    float cutoffOuter;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec3 fragPos;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 FragColor;

uniform vec3 playerPos;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform Material material;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionalLight dirLights[NR_DIR_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

vec3 pointLightCalc(PointLight);
vec3 dirLightCalc(DirectionalLight);
vec3 spotLightCalc(SpotLight);

void main()
{
    // for each light source, calculate contribution
    vec3 lightOutput = vec3(0.0f);
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        lightOutput += pointLightCalc(pointLights[i]);
    }
    for (int j = 0; j < NR_DIR_LIGHTS; j++) {
        lightOutput += dirLightCalc(dirLights[j]);
    }
    for (int k = 0; k < NR_DIR_LIGHTS; k++) {
        lightOutput += spotLightCalc(spotLights[k]);
    }
//    FragColor = vec4(vTexCoord.xyx, 1.0f); // debug textures
//    FragColor = vec4(fragPos.zzz, 1.0f);
    FragColor = vec4(lightOutput, 1.0f) * texture(texture_diffuse, vTexCoord) * texture(texture_specular, vTexCoord);
}

vec3 pointLightCalc(PointLight light) {
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

vec3 dirLightCalc(DirectionalLight light) {
    // direction vectors
    vec3 norm = normalize(vNormal);
    vec3 lDir = normalize(-light.direction);
    vec3 playerDir = normalize(playerPos - fragPos);
    vec3 lReflect = reflect(-lDir, norm);

    // calculate diffuse component
    float diffuseIntensity = max(dot(norm, lDir), 0.0f);
    vec3 diffuseLight = diffuseIntensity * light.diffuse * material.diffuse;

    // calculate specular component
    float specularIntensity = pow(max(dot(playerDir, lReflect), 0.0f), material.shininess);
    vec3 specularLight = specularIntensity * light.specular * material.specular;

    return diffuseLight + specularLight;
}


vec3 spotLightCalc(SpotLight light) {
    // direction vectors
    vec3 norm = normalize(vNormal);
    vec3 lDir = normalize(light.position - fragPos);
    vec3 spotDir = normalize(-light.spotDir);
    vec3 playerDir = normalize(playerPos - fragPos);
    vec3 lReflect = reflect(-lDir, norm);

    // calculate diffuse component
    float diffuseIntensity = max(dot(norm, lDir), 0.0f);
    vec3 diffuseLight = diffuseIntensity * light.diffuse * material.diffuse;

    // calculate specular component
    float specularIntensity = pow(max(dot(playerDir, lReflect), 0.0f), material.shininess);
    vec3 specularLight = specularIntensity * light.specular * material.specular;

    // attenuate all light based on distance
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    diffuseLight *= attenuation;
    specularLight *= attenuation;


    // calculate interpolation of fragments on the spotlight border
    float theta = dot(lDir, spotDir);
    float epsilon = light.cutoffAngle - light.cutoffOuter;
    float fade = clamp((theta - light.cutoffOuter) / epsilon, 0.0, 1.0);
    diffuseLight *= fade;
    specularLight *= fade;
    return diffuseLight + specularLight;
}