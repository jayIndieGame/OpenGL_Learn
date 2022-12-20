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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imGui/imgui.h"
#include "imGui/imgui_impl_opengl3.h"
#include "imGui/imgui_impl_glfw.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "OpenGl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//主版本为openGL3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);//次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);

    //在上下文初始化完成后初始化glew
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW INIT ERROR" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    // cube
    float vertices[] = {


        //position              //vertex color      //texture coordinates
		-50.0f,50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,1.0f,//左上前
        50.0f,50.0f,50.0f,      1.0f,1.0f,1.0f,     1.0f,1.0f,//右上前
        -50.0f,-50.0f,50.0f,    1.0f,1.0f,1.0f,     0.0f,0.0f,//左下前
        50.0f,-50.0f,50.0f,     1.0f,1.0f,1.0f,     1.0f,0.0f,//右下前

    	50.0f,50.0f,50.0f,      1.0f,1.0f,1.0f,     0.0f,1.0f,//右上前
        50.0f,50.0f,-50.0f,     1.0f,1.0f,1.0f,     1.0f,1.0f,//右上后
    	50.0f,-50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,0.0f,//左下前
    	50.0f,-50.0f,-50.0f,    1.0f,1.0f,1.0f,     1.0f,0.0f,//左下后
    };

    unsigned int indices[] = {
		0,1,2,
        2,1,3,

        4,5,6,
        6,7,5,
    };

    VertexArray vao;

    VertexBuffer vb(vertices,8*8*sizeof(float));
    
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vb,layout);

    IndexBuffer ibo(indices, 12);



    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/Texture/awesomeface.png");
	texture.Bind(1);
	shader.SetUniform1i("u_Texture", 1);//bind 几这里就传几。即选择第几个slot

    Renderer renderer;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    float r = 0;
    float interval = 0.05;

    //设置完毕后清空opengl状态
    vao.UnBind();
    shader.UnBind();
    vb.UnBind();
    ibo.UnBind();

    glm::vec3 cameraTranslation(0, 0, 0);
    ImVec4 face_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    glm::mat4 proj = glm::perspective(glm::radians(80.0f),4.0f/3.0f,0.1f,1000.0f);
    glm::mat4 view;
    glm::mat4 model;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.Draw(vao, ibo, shader);
        shader.SetUniform4f("u_Color", face_color.x, face_color.y, face_color.z,1);

        view = glm::translate(glm::mat4(1.0f), cameraTranslation);
        model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, -300.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 mvp = proj * view * model;

        shader.SetUniform4fMat("u_MVP", mvp);


        r += interval;
        if (r > 1)
            interval = -0.05f;
        if (r < 0)
            interval = 0.05f;

        {

            ImGui::SliderFloat3("Translation", &cameraTranslation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("Face color", (float*)&face_color);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

        /* Poll for and process events */
    	glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}