#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    window = glfwCreateWindow(640, 480, "OpenGl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //在上下文初始化完成后初始化glew
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW INIT ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float position[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f
    };

    unsigned int Buffer;
    glGenBuffers(1, &Buffer);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"//330是glsl的版本core指的是不用废弃掉的方法
        "\n"
        "layout(location = 0)in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        " gl_Position = position;\n"
        "}\n";
        

	std::string fragShader =
		"#version 330 core\n"//330是glsl的版本core指的是不用废弃掉的方法
		"\n"
		"layout(location = 0)out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		" color = vec4(1.0,0.0,0.0,1.0);\n"
		"}\n";

    unsigned int shader = CreateShader(vertexShader, fragShader);
    glUseProgram(shader);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);



        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteShader(shader);

    glfwTerminate();
    return 0;
}