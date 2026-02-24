#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec2 v_UV;
in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 FragColor;
uniform vec3 u_ViewPos;

uniform Material u_Material;
uniform Light u_Light;

void main()
{
    

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.position - v_FragPos);

    vec3 diffTexCol = texture(u_Material.diffuse,v_UV).rgb;


    vec3 ambient = u_Light.ambient * diffTexCol;

    // diffuse
    float diff = max(dot(norm,lightDir),0.0);
    
    vec3 diffuse = u_Light.diffuse * (diff * diffTexCol);
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),u_Material.shininess);  // specular factor

    vec3 specularTexCol = texture(u_Material.specular,v_UV).rgb;
    vec3 specular = u_Light.specular * (spec * specularTexCol);
    
    // final object color
    vec3 result = ambient + diffuse + specular;
    
    FragColor = vec4(result,1.0);
}
