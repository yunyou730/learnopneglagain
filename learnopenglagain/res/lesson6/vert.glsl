#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;

out vec3 vColor;
out vec2 vUV;

//uniform mat4 u_Transform;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
    vColor = aColor;
    vUV = aUV;
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos,1.0);
}
