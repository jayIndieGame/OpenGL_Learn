#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Renderer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imGui/imgui.h"
#include "imGui/imgui_impl_opengl3.h"
#include "imGui/imgui_impl_glfw.h"
#include "Camera/Camera.h"
#include "Tests/Test.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "TestBasicLighting.h"


static void checkGLFW(GLFWwindow* window);
static void initGUI(GLFWwindow* window);
static void processInput(GLFWwindow* window,Camera& camera);




float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        std::cout << "GLEW INIT ERROR" << std::endl;
    window = glfwCreateWindow(1280, 960, "OpenGl", NULL, NULL);
    checkGLFW(window);
    initGUI(window);
    Renderer renderer;

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    testMenu->Register<test::TestClearColor>("Clear Color");
    testMenu->Register<test::TestTexture2D>("Test Texture2D");
    testMenu->Register<test::TestBasicLighting>("Basic Lighting");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(currentTest)
        {
            currentTest->OnUpdate(deltaTime,window);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if(currentTest!= testMenu&&ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
                GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            }
            currentTest->OnImGUIRender();
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
    	glfwPollEvents();
    }
    if (currentTest != testMenu)
        delete testMenu;
    delete currentTest;

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

static void processInput(GLFWwindow* window,Camera& camera)
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

