#shader vertex
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aNormal;

out vec3 TexCoords;//cubemap��vec3
out vec3 Normal;
out vec3 Position;
out vec2 TexCoords2Dout;


uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform bool skybox;

void main()
{
    Position = vec3(model * vec4(aPos, 1.0));
    if (skybox) {
        TexCoords = aPos / 50;//�ҵĶ��������ǰ���-50,50���ģ�Ҫ��λ��������д������50�����������������Ȳ�Ӱ�죬���Բ���Ҳ����ν
        vec4 pos = projection * view * model * vec4(aPos / 50, 1.0);
        gl_Position = pos.xyww;//z��Զ���ӿ�����Զ����
    }
    else
    {

        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
    TexCoords2Dout = aTexCoords;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}

#shader fragment
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���
out vec4 FragColor;
in vec3 TexCoords;
in vec2 TexCoords2Dout;
in vec3 Normal;
in vec3 Position;


uniform samplerCube u_Texture;
uniform sampler2D u_Diffuse;
uniform vec3 cameraPos;
uniform bool skybox;
uniform bool refrac;


void main()
{
    FragColor = texture(u_Texture, TexCoords);
    if (!skybox)
    {
        if (!refrac) {
            vec3 I = normalize(Position - cameraPos);
            vec3 R = reflect(I, normalize(Normal));
            FragColor = texture(u_Texture, R) * vec4(texture(u_Diffuse, TexCoords2Dout).r);
        }
        else{
            float ratio = 1.00 / 1.52;
            vec3 I = normalize(Position - cameraPos);
            vec3 R = refract(I, normalize(Normal), ratio);
            FragColor = texture(u_Texture, R) * vec4(texture(u_Diffuse, TexCoords2Dout).r);
        }
    }

    //FragColor = vec4(TexCoords, 1.0);
}