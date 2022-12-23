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
in vec2 v_texcoord;
in vec3 Normal;
in vec3 worldPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
	vec4 texColor = texture(u_Texture, v_texcoord);
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	// diffuse 
	vec3 norm = normalize(Normal);

	vec3 lightNDir = normalize(lightPos-worldPos);
	float diff = max(dot(norm, lightNDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - worldPos);
	vec3 halfDir = normalize(lightNDir + viewDir);
	float spec = pow(max(dot(norm, halfDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) ;
	FragColor = vec4(result,1.0f) * mix(texColor, u_Color, 0.2);

};