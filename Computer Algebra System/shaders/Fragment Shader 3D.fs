#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor;
in vec3 normal;

void main()
{
    vec3 lightDirection1 = normalize(vec3(1, 2, 1.5));
    float diffuseLight1 = max(dot(normal, lightDirection1), 0.0);
    vec3 lightDirection2 = normalize(vec3(-1, -2, -1.5));
    float diffuseLight2 = max(dot(normal, lightDirection2), 0.0) * 0.5f;
    
    FragColor = vec4(vertexColor.xyz * (diffuseLight1 + diffuseLight2 + 0.2f), vertexColor.w);
}