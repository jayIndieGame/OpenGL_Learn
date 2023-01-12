#shader vertex
#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 atexcoords;
layout(location = 2) in vec2 aOffset;

out vec2 texcoords;
uniform mat4 model;

void main()
{
    vec2 pos = aPos * (gl_InstanceID/100.0);
    texcoords = atexcoords;
    gl_Position = model * vec4(pos + aOffset,0.0,1.0);
}

#shader fragment
#version 330 core

in vec2 texcoords;
out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, texcoords);
}
