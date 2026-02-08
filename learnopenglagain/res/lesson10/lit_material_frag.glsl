#version 330 core
in vec2 vUV;

out vec4 FragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;

uniform vec3 u_ViewPos;

in vec3 v_Normal;
in vec3 v_FragPos;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_FragPos);

    float diff = max(dot(norm,lightDir),0.0);
    
    // diffuse
    vec3 diffuse = diff * u_LightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),128);  // specular factor
    vec3 specular = specularStrength * spec * u_LightColor;
    
    // final object color
    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    
    FragColor = vec4(result,1.0);
}
