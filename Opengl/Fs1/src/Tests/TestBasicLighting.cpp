#include "TestBasicLighting.h"
#include "HelperLibrary.h"

test::TestBasicLighting::TestBasicLighting():
objectLocation(0,0,0),initLocation(0,0,-200),
objectRotation(0,0,0), m_Color(0.8f, 0.3f, 0.8f, 1.0f),
lightPos(100.0f, 100.0f, -300.0f), lightColor(1.0f, 1.0f, 1.0f, 1.00f)
{

	m_Cube = std::make_unique<Cube>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Shader = std::make_unique<Shader>("res/shaders/BasicLight.shader");
	m_Texture = std::make_unique<Texture>("res/Texture/awesomeface.png");
	m_VAO = std::make_unique<VertexArray>();
	VertexBufferLayout layout;

	m_Cube->SetRenderState(*m_Shader, *m_Texture, layout, *m_VAO, 1);
	m_Cube->SetLocation(initLocation);
}

test::TestBasicLighting::~TestBasicLighting()
{

}

void test::TestBasicLighting::OnUpdate(float deltaTime, GLFWwindow* window)
{
	m_Camera->ImGuiMouse(window);
    Helper::processInput(window, *m_Camera, deltaTime);
}

void test::TestBasicLighting::OnRender()
{
    GLCALL(glClearColor(0, 0, 0, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    Renderer render;
    render.Draw(*m_VAO, *m_Cube->GetIndexBufferPointer(), *m_Shader);
    m_Shader->SetUniform4f("u_Color", m_Color.x, m_Color.y, m_Color.z, 1);
    m_Cube->SetLocation(objectLocation + initLocation);
    m_Cube->SetRotation(objectRotation);
    //view = glm::translate(glm::mat4(1.0f), cameraTranslation);
    //glm::mat4 mvp = proj * view * model;
    m_Shader->SetUniform4fMat("u_model", m_Cube->GetModelMatrix());
    m_Shader->SetUniform4fMat("u_view", m_Camera->GetViewMatrix());
    m_Shader->SetUniform4fMat("u_project", m_Camera->GetProjMatrix());
    m_Shader->SetUniform3f("lightPos", lightPos);
    m_Shader->SetUniform3f("viewPos", m_Camera->Position);
    m_Shader->SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
}

void test::TestBasicLighting::OnImGUIRender()
{
    ImGui::SliderFloat3("Cube Offset", &objectLocation.x, -300.0f, 300.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3("Cube Rotation", &objectRotation.x, 0, 2 * glm::pi<float>());
    ImGui::SliderFloat3("Light Position", &lightPos.x, -1000.0f, 500.0f);
    ImGui::ColorEdit3("Light Color", (float*)&lightColor);
    ImGui::ColorEdit3("Face color", (float*)&m_Color);
    ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 8, 50.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
