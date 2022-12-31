#include "TestModelLoading.h"

#include "HelperLibrary.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "imGui/imgui.h"

test::TestModelLoading::TestModelLoading()
{
	glEnable(GL_DEPTH_TEST);
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_shader = std::make_unique<Shader>("res/shaders/ModelLoading.shader");
	m_model = std::make_unique<Model>("res/Model/backpack/backpack.obj");

}

test::TestModelLoading::~TestModelLoading()
{
	glDisable(GL_DEPTH_TEST);
	m_shader->UnBind();
}

void test::TestModelLoading::OnUpdate(float deltaTime, GLFWwindow* window)
{
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window,*m_Camera,deltaTime);
	//Test::OnUpdate(deltaTime, window);
}

void test::TestModelLoading::OnRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader->Bind();

	m_shader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_shader->SetUniform4fMat("view", m_Camera->GetViewMatrix());

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0, 0, -400.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));	// it's a bit too big for our scene, so scale it down

	m_shader->SetUniform4fMat("model", model);
	m_model->Draw(*m_shader);

	//Test::OnRender();
}

void test::TestModelLoading::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 8, 50.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x );
	ImGui::Text("camera Location Y %f", m_Camera->Position.y );
	ImGui::Text("camera Location Z %f", m_Camera->Position.z );
	//Test::OnImGUIRender();
}

void test::TestModelLoading::OnExit()
{
	//Test::OnExit();
}
