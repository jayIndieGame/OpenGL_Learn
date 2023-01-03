#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

layout(location = 0)in vec3 position;
layout(location = 1)in vec2 texcoord;
layout(location = 2)in vec3 anormal;

out vec2 v_texcoord;
out vec3 Normal;
out vec3 worldPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_project;

void main()
{
	worldPos = vec3(u_model * vec4(position, 1.0));
	v_texcoord = texcoord;
	Normal = mat3(transpose(inverse(u_model))) * anormal;

	gl_Position = u_project * u_view * vec4(worldPos, 1.0);
};

#shader fragment
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


in vec2 v_texcoord;
in vec3 Normal;
in vec3 worldPos;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, v_texcoord).rgb;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - worldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, v_texcoord).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - worldPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, v_texcoord).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

};