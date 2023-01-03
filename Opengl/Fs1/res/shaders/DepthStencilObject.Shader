#shader vertex
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#shader fragment
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, TexCoords);
}