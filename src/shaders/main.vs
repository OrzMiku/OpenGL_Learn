#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float time;
out vec3 ourColor;
void main()
{
   mat3 rotation = mat3(
       vec3(cos(time * 2), -sin(time), 0.0),
       vec3(sin(time), cos(time), 0.0),
       vec3(0.0, 0.0, 1.0)
   );
   gl_Position = vec4(rotation * aPos, 1.0);
   ourColor = aColor;
}