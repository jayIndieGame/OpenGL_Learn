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
const float offset = 1.0 / 960.0;//应该长宽都写下
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
        vec2(-offset, offset), // 左上
        vec2(0.0f, offset), // 正上
        vec2(offset, offset), // 右上
        vec2(-offset, 0.0f),   // 左
        vec2(0.0f, 0.0f),   // 中
        vec2(offset, 0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2(0.0f, -offset), // 正下
        vec2(offset, -offset)  // 右下
        );//采样点
    float kernel[9] = float[](
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
        );//卷积核

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
        if(sobel)//只做了x方向1阶，只是为了举例子，不是写算法的。
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
            sampleTex[i] = vec3(texture(u_Texture, TexCoords.st + offsets[i]));//对每个像素周围3x3个像素采样，大部分都是3x3的
        }
        vec3 col = vec3(0.0);
        for (int i = 0; i < 9; i++)
            col += sampleTex[i] * kernel[i];

        FragColor = vec4(col, 1.0);
    }
}