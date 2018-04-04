#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform vec3 lColor;

void main()
{
    float ambientIntensity = 0.1f;
    vec3 ambientLight = ambientIntensity * lColor;
    FragColor = vec4(ambientLight, 1.0f) * mix(texture(tex1, vTexCoord), texture(tex2, vec2(1.0 - vTexCoord.x, vTexCoord.y)), 0.2);
}