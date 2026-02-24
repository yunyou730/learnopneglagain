#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Normal;
out vec2 v_UV;
out vec3 v_FragPos;


void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos,1.0);
    v_FragPos = (u_Model * vec4(aPos,1.0)).xyz;

    mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    v_Normal = normalMatrix * aNormal;

    v_UV = aUV;
}
