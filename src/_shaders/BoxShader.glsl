#version 330 core

in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;
in vec3 fragPos;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 lColor;
uniform vec3 lPos;

void main()
{
    // calculate diffuse component
    vec3 norm = normalize(vNormal);
    vec3 lDir = normalize(lPos - fragPos);
    float diffuseIntensity = max(dot(norm, lDir), 0.0f);
    vec3 diffuseLight = diffuseIntensity * lColor;

    float ambientIntensity = 0.1f;
    vec3 ambientLight = ambientIntensity * lColor;
    FragColor = vec4(ambientLight + diffuseLight, 1.0f) * mix(texture(tex1, vTexCoord), texture(tex2, vec2(1.0 - vTexCoord.x, vTexCoord.y)), 0.2);
}