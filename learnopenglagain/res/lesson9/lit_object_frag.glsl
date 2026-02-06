#version 330 core
in vec2 vUV;

out vec4 FragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;


uniform vec3 u_LightPos;

in vec3 v_Normal;
in vec3 v_FragPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * u_LightColor;

    vec3 result = (ambient + diffuse) * u_ObjectColor;
    

    //result = normalize(v_Normal);
    //result = v_FragPos;

    FragColor = vec4(result,1.0);
}
