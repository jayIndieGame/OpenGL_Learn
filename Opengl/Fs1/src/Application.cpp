#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

enum class ShaderType
{
    NONE = -1,VERTEX =0,FRAGMENT = 1

};

struct ShaderProgramSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

static ShaderProgramSource ParseShader(const std::string filepath)
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream,line))
    {
        if(line.find("#shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment")!=std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(),ss[1].str() };
}

//表示类型的参数类型是GLenum,也是typedef unsigned int GLenum;写无符号整形避免其他地方调用该函数时需要引入glew
static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);//根据id生成source文件，1是一份，src是shader文件，nullptr是读取到nullptr就停止
    glCompileShader(id);

    //检查
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));//在栈上申请固定长度存放info
        glGetShaderInfoLog(id, length, &length, message);//存进去,需要两种length，原因未知
        std::cout << message << std::endl;
        glDeleteShader(id);

        return 0;
    }


    return id;
}

static int CreateShader(const std::string VertextShader,const std::string FragmentShader)
{
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertextShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);

	glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "OpenGl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    //在上下文初始化完成后初始化glew
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW INIT ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float position[] = {
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vb(position,4*2*sizeof(float));

    //unsigned int Buffer;
    //glGenBuffers(1, &Buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    //glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        

    IndexBuffer ibo(indices, 6);
	//unsigned int ibo;
	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    std::cout << "vertex shader" << std::endl;
    std::cout << source.vertexShader << std::endl;
    std::cout << "fragment shader" << std::endl;
    std::cout << source.fragmentShader << std::endl;

    unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
    glUseProgram(shader);
    
    int location = glGetUniformLocation(shader, "u_Color");

    float r = 0;
    float interval = 0.05;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 6);

        GLCALL(glUseProgram(shader));
        GLCALL(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCALL(glBindVertexArray(vao));
        ibo.Bind();

        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        r += interval;
        if (r > 1)
            interval = -0.05f;
        if (r < 0)
            interval = 0.05f;

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteShader(shader);

    glfwTerminate();
    return 0;
}