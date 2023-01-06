#shader vertex
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, 0.0, 1.0);//ֻ��ģ�ͱ任
    TexCoords = aTexCoords;
}
#shader fragment
#version 330 core//330��glsl�İ汾coreָ���ǲ��÷������ķ���
out vec4 FragColor;

in vec2 TexCoords;
const float offset = 1.0 / 960.0;//Ӧ�ó�����д��
uniform sampler2D u_Texture;
uniform bool antiphase;
uniform bool grayscale;
uniform bool convolution;
uniform bool sobel;
uniform bool blur;
void main()
{
    FragColor = texture(u_Texture, TexCoords);
    if (antiphase)
        FragColor = vec4(vec3(1.0 - texture(u_Texture, TexCoords)), 1.0);

    if (grayscale)
    {
        FragColor = texture(u_Texture, TexCoords);
        float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
        FragColor = vec4(average, average, average, 1.0);
    }

    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // ����
        vec2(0.0f, offset), // ����
        vec2(offset, offset), // ����
        vec2(-offset, 0.0f),   // ��
        vec2(0.0f, 0.0f),   // ��
        vec2(offset, 0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2(0.0f, -offset), // ����
        vec2(offset, -offset)  // ����
        );//������
    float kernel[9] = float[](
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
        );//������

    if(convolution || blur || sobel)
    {
        if (blur)
        {
            kernel = float[9](
                1.0 / 16, 2.0 / 16, 1.0 / 16,
                2.0 / 16, 4.0 / 16, 2.0 / 16,
                1.0 / 16, 2.0 / 16, 1.0 / 16
            );
        }
        if(sobel)//ֻ����x����1�ף�ֻ��Ϊ�˾����ӣ�����д�㷨�ġ�
        {
            kernel = float[9](
                -1.0, 0.0, 1.0,
                -2.0, 0.0, 2.0,
                -1.0, 0.0, 1.0
            );
        }
        vec3 sampleTex[9];
        for (int i = 0; i < 9; i++)
        {
            sampleTex[i] = vec3(texture(u_Texture, TexCoords.st + offsets[i]));//��ÿ��������Χ3x3�����ز������󲿷ֶ���3x3��
        }
        vec3 col = vec3(0.0);
        for (int i = 0; i < 9; i++)
            col += sampleTex[i] * kernel[i];

        FragColor = vec4(col, 1.0);
    }
}