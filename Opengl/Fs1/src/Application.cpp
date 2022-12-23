#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Renderer.h"
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
#include "BasicMesh/Cube.h"
#include "Camera/Camera.h"

static void checkGLFW(GLFWwindow* window);
static void initGUI(GLFWwindow* window);
void processInput(GLFWwindow* window,Camera& camera);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//lighting
glm::vec3 lightPos(100.0f, 100.0f, -300.0f);
ImVec4 lightColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        std::cout << "GLEW INIT ERROR" << std::endl;
    window = glfwCreateWindow(1280, 960, "OpenGl", NULL, NULL);
    checkGLFW(window);
    initGUI(window);

    // cube
    Cube cube;
    VertexArray vao;
    VertexBufferLayout layout;
    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/Texture/awesomeface.png");
    Renderer renderer;
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
    cube.SetRenderState(shader, texture, layout, vao, 1);


    //设置完毕后清空opengl状态
    vao.UnBind();
    shader.UnBind();

    glm::vec3 objectLocation(0, 0, 0);
    glm::vec3 InitLocation(0, 0, -200);
    glm::vec3 objectRotation(0, 0, 0);
    ImVec4 face_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    IndexBuffer ib = cube.GetIndexBuffer();
    cube.SetLocation(InitLocation);
    cube.SetRotation(glm::vec3(0.0f, 50.0f, 0.0f));
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window,camera);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        camera.ImGuiMouse(window);


        {//render cube one
            renderer.Draw(vao, ib, shader);//这里不能调用cube.GetIndexBuffer();会循环在栈上构造对象，导致内存溢出 先写draw是为了bindshader。
            shader.SetUniform4f("u_Color", face_color.x, face_color.y, face_color.z, 1);
            cube.SetLocation(objectLocation + InitLocation);
            cube.SetRotation(objectRotation);
            //view = glm::translate(glm::mat4(1.0f), cameraTranslation);
            //glm::mat4 mvp = proj * view * model;
            shader.SetUniform4fMat("u_model", cube.GetModelMatrix());
            shader.SetUniform4fMat("u_view", camera.GetViewMatrix());
            shader.SetUniform4fMat("u_project", camera.GetProjMatrix());
            shader.SetUniform3f("lightPos", lightPos);
            shader.SetUniform3f("viewPos", camera.Position);
            shader.SetUniform3f("lightColor", lightColor.x,lightColor.y,lightColor.z);

            renderer.Draw(vao, ib, shader);
            shader.SetUniform4fMat("u_model", glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, -600)));

        }

        {//render ui
            ImGui::Begin("Base Lighting");
        	ImGui::SliderFloat3("Cube Offset", &objectLocation.x, -300.0f, 300.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("Cube Rotation", &objectRotation.x, 0, 2*glm::pi<float>());
            ImGui::SliderFloat3("Light Position", &lightPos.x, -1000.0f, 500.0f);
            ImGui::ColorEdit3("Light Color", (float*)&lightColor);
            ImGui::ColorEdit3("Face color", (float*)&face_color);
            ImGui::SliderFloat("Camera Speed", &camera.MovementSpeed, 8, 50.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            //ImGui::GetIO().WantCaptureMouse = true;
            //ImGui::GetIO().AddMouseButtonEvent(0, true);
            ImGui::End();
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


static void checkGLFW(GLFWwindow* window)
{
    /* Initialize the library */

    if (!window)
        glfwTerminate();


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

}

static void initGUI(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    //ImGui_ImplGlfw_InstallCallbacks(window);
}

void processInput(GLFWwindow* window,Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam_Up, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(Cam_DOWN, deltaTime);

}

