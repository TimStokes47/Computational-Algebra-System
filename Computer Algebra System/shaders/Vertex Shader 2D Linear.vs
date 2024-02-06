#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

uniform vec4 u_Colour;
uniform mat2 u_Transform;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec3 modelPosition = vec3(u_Model * vec4(aPos, 1.0f));
    gl_Position = u_Projection * u_View * vec4(u_Transform * vec2(modelPosition.x, modelPosition.y), -1.0f, 1.0f);
    vertexColor = u_Colour;
}