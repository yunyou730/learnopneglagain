#version 330 core
in vec2 vUV;

out vec4 FragColor;

uniform sampler2D u_MainTex;
uniform sampler2D u_SecondTex;

void main()
{
    vec4 texCol = texture(u_MainTex,vUV);
    vec4 texCol2 = texture(u_SecondTex,vUV);
    FragColor = mix(texCol,texCol2,0.5);
}
