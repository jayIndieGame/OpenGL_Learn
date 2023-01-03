#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

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
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法
out vec4 FragColor;

in vec2 TexCoords;
uniform bool Depth;
uniform bool stencil;
uniform sampler2D u_Texture;

float near = 0.1;
float far = 100.0;//camera深度是1000为了演示改成100

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    FragColor = texture(u_Texture, TexCoords);
    if(Depth)
    {
        float depth = LinearizeDepth(gl_FragCoord.z) / far;
        FragColor = vec4(vec3(depth), 1.0);
    }
    if(stencil)
    {
        FragColor = vec4(0.04, 0.28, 0.26, 1.0);
    }
    //FragColor = vec4(1.0);
}