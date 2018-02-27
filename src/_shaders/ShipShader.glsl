#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D tex1;
void main()
{
    FragColor = texture(tex1, vTexCoord);
}