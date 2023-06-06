#version 460 core

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 fragColor;

void main()
{
    gl_Position = vec4(inPosition.x, inPosition.y, inPosition.z, 1.0);
    fragColor   = vec3(0.2, 1.0, 0.2);
}