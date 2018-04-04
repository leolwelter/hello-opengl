#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D tex1;
uniform vec3 lColor;

void main()
{
    float ambientIntensity = 0.1f;
    vec3 ambientLight = ambientIntensity * lColor;
    FragColor = vec4(ambientLight * vColor, 1.0f);
}