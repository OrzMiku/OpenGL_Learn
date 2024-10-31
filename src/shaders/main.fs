#version 330 core
in vec3 ourColor;
out vec4 FragColor;
uniform float time;

void main()
{
    FragColor = vec4(sin(ourColor.r + time), sin(ourColor.g + time * 2), sin(ourColor.b + time * 3), 1.0f);
}