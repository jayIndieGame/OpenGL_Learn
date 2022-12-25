#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

layout(location = 0)in vec4 position;
layout(location = 1)in vec2 texcoord;

out vec2 v_texcoord;
uniform mat4 u_MVP;

void main()
{

	v_texcoord = texcoord;

	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法
out vec4 FragColor;
in vec2 v_texcoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;


void main()
{
	vec4 texColor = texture(u_Texture, v_texcoord);
	FragColor =  mix(texColor, u_Color, 0.2);

};