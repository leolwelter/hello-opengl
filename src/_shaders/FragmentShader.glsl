#version 330 core
# define NR_POINT_LIGHTS 2


struct PointLight {
    vec3 position;
    vec3 color;
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


vec3 lightCalc(PointLight);

void main()
{
    vec3 lightOutput = vec3(0.0f);
    float specularStrength = 0.5;

    // for each light source, calculate contribution
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

    // calculate diffuse component
    float diffuseIntensity = max(dot(norm, lDir), 0.0f);
    vec3 diffuseLight = diffuseIntensity * light.color;

    // calculate specular component
    float specularIntensity = pow(max(dot(playerDir, lReflect), 0.0f), 64);
    vec3 specularLight = specularIntensity * light.color;

    // simple ambient constant
    float ambientIntensity = 0.1f;
    vec3 ambientLight = ambientIntensity * light.color;

    return diffuseLight + specularLight + ambientLight;
}