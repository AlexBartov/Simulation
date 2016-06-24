#version 450 core
in vec3 ourColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 uColor;
uniform bool affect;

out vec4 color;


void main()
{
    float ambientStrength = 0.2f;
    float specularStrength = 0.6f;
    const int shininess = 32;

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(lightPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse + specular) * uColor;
    if(affect)
    {
    color = vec4(result, 1.0f);
    }
    else
    {
    color = vec4(uColor, 1.0f);
    }
}
