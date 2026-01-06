#version 330 core
in vec3 vColor;

out vec4 FragColor;

void main()
{
//    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = vec4(vColor,1.0);
}
