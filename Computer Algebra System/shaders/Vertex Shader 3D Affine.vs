#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec4 vertexColor;
out vec3 normal;

uniform vec4 u_Colour;
uniform mat4 u_Transform;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Transform * u_Model * vec4(aPos, 1.0f);
    vertexColor = u_Colour;
    normal = normalize(vec3(u_Transform * u_Model * vec4(aNormal, 1.0f)));
}