#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture/Texture.h"


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

    //�������ĳ�ʼ����ɺ��ʼ��glew
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW INIT ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
        //position  //color        //texture coordinates
        -0.5f,-0.5f,1.0f,0.0f,1.0f,0.0f,0.0f,
        0.5f,-0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,
        0.5f,0.5f,1.0f,1.0f,0.0f,1.0f,1.0f,
        -0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,1.0f
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    VertexArray vao;

    VertexBuffer vb(vertices,4*7*sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vb,layout);

    IndexBuffer ibo(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/Texture/awesomeface.png");
	texture.Bind(1);
	shader.SetUniform1i("u_Texture", 1);//bind ������ʹ�������ѡ��ڼ���slot


    Renderer renderer;

    float r = 0;
    float interval = 0.05;

    //������Ϻ����opengl״̬
    vao.UnBind();
    shader.UnBind();
    vb.UnBind();
    ibo.UnBind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        shader.Bind();
        //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        renderer.Draw(vao,ibo,shader);


        r += interval;
        if (r > 1)
            interval = -0.05f;
        if (r < 0)
            interval = 0.05f;
		GLCALL(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCALL(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}