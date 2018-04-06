#version 330 core

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 lColor;
uniform vec3 mColor;
uniform vec3 lPos;
uniform vec3 mPos;
uniform vec3 playerPos;

void main()
{
    // direction vectors
    vec3 norm = normalize(vNormal);
    vec3 lDir = normalize(lPos - fragPos);
    vec3 mDir = normalize(mPos - fragPos);
    vec3 playerDir = normalize(playerPos - fragPos);
    vec3 lReflect = reflect(-lDir, norm);
    vec3 mReflect = reflect(-mDir, norm);

    // calculate diffuse component
    float sunDiffInt = max(dot(norm, lDir), 0.0f);
    float moonDiffInt = max(dot(norm, mDir), 0.0f);
    vec3 diffuseLight = sunDiffInt * lColor + moonDiffInt * mColor;

    // calculate specular component
    float specularStrength = 0.5;
    float sunSpecular = pow(max(dot(playerDir, lReflect), 0.0f), 64);
    float moonSpecular = pow(max(dot(playerDir, mReflect), 0.0f), 64);
    vec3 specularLight = sunSpecular * lColor + moonSpecular * mColor;

    // simple ambient constant
    float ambientIntensity = 0.1f;
    vec3 ambientLight = ambientIntensity * lColor;

    FragColor = vec4(ambientLight + diffuseLight + specularLight, 1.0f) * mix(texture(tex1, vTexCoord), texture(tex2, vec2(1.0 - vTexCoord.x, vTexCoord.y)), 0.2);
}