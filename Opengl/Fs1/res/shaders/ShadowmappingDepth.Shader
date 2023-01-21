#shader vertex
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

layout(location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core//330是glsl的版本core指的是不用废弃掉的方法

//out vec4 FragColor;

void main()
{
    //gl_FragDepth = gl_FragCoord.z;
    //FragColor = vec4(vec3(gl_FragDepth), 1.0);
}