#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out VS_OUT{
    vec3 normal;
} vs_out;

//删掉透视矩阵，在之后的几何着色器中计算
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0);
    mat3 normalMatrix = mat3(transpose(inverse( view * model)));
    vs_out.normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));
}

#shader fragment
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}


#shader geometry
#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT{
    vec3 normal;
}gs_in[];
const float MAGNITUDE = 0.4;
uniform mat4 projection;

void GenerateLine(int index)
{
    gl_Position = projection * gl_in[index].gl_Position;//当前点
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position +
        vec4(gs_in[index].normal, 0.0) * MAGNITUDE);//按法线延长的点
    EmitVertex();
    EndPrimitive();
}

void main() 
{
    //对每个三角面的每个顶点都执行这个操作
    GenerateLine(0);
    GenerateLine(1); 
    GenerateLine(2); 
}