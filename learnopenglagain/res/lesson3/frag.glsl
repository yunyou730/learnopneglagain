#version 330 core
in vec3 vColor;
in vec2 vUV;

out vec4 FragColor;

uniform sampler2D u_MainTex;

void main()
{
    vec4 texCol = texture(u_MainTex,vUV);
    FragColor = vec4(vUV,0.0,1.0) + texCol;
}
