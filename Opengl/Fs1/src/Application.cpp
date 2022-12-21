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

struct ImGui_ImplGlfw_Data;
static void checkGLFW(GLFWwindow* window);
static void initGUI(GLFWwindow* window);
void processInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ImGuiMouse(GLFWwindow* window);


float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float cameraSpeed = 10.0f;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;


int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        std::cout << "GLEW INIT ERROR" << std::endl;
    window = glfwCreateWindow(1280, 960, "OpenGl", NULL, NULL);
    checkGLFW(window);
    initGUI(window);

	//glfwSetCursorPosCallback(window,mouse_callback); //用imGui接管
    //glfwSetScrollCallback(window, scroll_callback);

    // cube
    Cube cube;
    VertexArray vao;
    VertexBufferLayout layout;
    Shader shader("res/shaders/Basic.shader");
    Texture texture("res/Texture/awesomeface.png");
    Renderer renderer;

    cube.SetRenderState(shader, texture, layout, vao, 1);


    //设置完毕后清空opengl状态
    vao.UnBind();
    shader.UnBind();

    glm::vec3 objectLocation(0, 0, 0);
    glm::vec3 InitLocation(0, 0, -200);
    ImVec4 face_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
    glm::mat4 proj = glm::perspective(glm::radians(90.0f),4.0f/3.0f,0.1f,1000.0f);

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
        processInput(window);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiMouse(window);


        {//render cube one
            renderer.Draw(vao, ib, shader);//这里不能调用cube.GetIndexBuffer();会循环在栈上构造对象，导致内存溢出
            shader.SetUniform4f("u_Color", face_color.x, face_color.y, face_color.z, 1);
            glm::mat4 model = cube.GetModelMatrix();
            glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            cube.SetLocation(objectLocation + InitLocation);
            //view = glm::translate(glm::mat4(1.0f), cameraTranslation);
            glm::mat4 mvp = proj * view * model;
            shader.SetUniform4fMat("u_MVP", mvp);
        }

        {//render ui
            ImGui::SliderFloat3("Cube Offset", &objectLocation.x, -300.0f, 300.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("Face color", (float*)&face_color);
            ImGui::SliderFloat("Camera Speed", &cameraSpeed, 8, 50.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            //ImGui::GetIO().WantCaptureMouse = true;
            //ImGui::GetIO().AddMouseButtonEvent(0, true);
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


static void checkGLFW(GLFWwindow* window)
{
    /* Initialize the library */


    ;
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

void imGUICallBack()
{
	
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float camspeed = static_cast<float>(cameraSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += camspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= camspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camspeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camspeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += camspeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= camspeed * cameraUp;

}


void ImGuiMouse(GLFWwindow* window)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
    {
        float xpos = static_cast<float>(ImGui::GetIO().MousePos.x);
        float ypos = static_cast<float>(ImGui::GetIO().MousePos.y);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }
    else if(state == GLFW_RELEASE)
    {
        firstMouse = true;
	    
    }

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}