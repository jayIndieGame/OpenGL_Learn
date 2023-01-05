#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, 0.0, 1.0);//只做模型变换
    TexCoords = aTexCoords;
}
#shader fragment
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, TexCoords);
}