#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

layout(location = 0)in vec4 position;
layout(location = 1)in vec3 aColor;
layout(location = 2)in vec2 texcoord;
out vec3 outColor;
out vec2 v_texcoord;

uniform mat4 u_MVP;


void main()
{
	gl_Position = u_MVP * position;
	outColor = aColor;
	v_texcoord = texcoord;
};

#shader fragment
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

layout(location = 0) out vec4 color;
in vec3 outColor;
in vec2 v_texcoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 texColor = texture(u_Texture, v_texcoord);
	color = (vec4(outColor,1.0) + texColor) * u_Color;
	//color = vec4(1.0, 1.0, 1.0,1.0);
};