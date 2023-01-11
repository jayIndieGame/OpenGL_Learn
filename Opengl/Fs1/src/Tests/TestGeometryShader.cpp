#include "TestGeometryShader.h"

#include "HelperLibrary.h"
#include "VertexBufferLayout.h"
#include "imGui/imgui.h"

test::TestGeometryShader::TestGeometryShader()
{
	m_shader = std::make_unique<Shader>("res/shaders/TestGeometry.Shader");
	m_modelshaderBoom = std::make_unique<Shader>("res/shaders/GeometryBoomEffect.Shader");
	m_modelshaderNormal = std::make_unique<Shader>("res/shaders/GeometryNormalEffect.Shader");
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	vbo = std::make_unique<VertexBuffer>(m_points, 5 * 4 * sizeof(float));
	ibo = std::make_unique<IndexBuffer>(m_indexs, 4);
	vao = std::make_unique<VertexArray>();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao->AddBuffer(*vbo, layout);
	m_shader->Bind();

	m_model = std::make_unique<Model>("res/Model/nanosuit/nanosuit.obj");

	scene_label = "Change to nanosuit";
	blow_label = "enable boom effect";
	normal_label = "enable normal";
	m_Camera->Position = glm::vec3(0, 13, 24);
	glEnable(GL_DEPTH_TEST);

}

test::TestGeometryShader::~TestGeometryShader()
{

}

void test::TestGeometryShader::OnUpdate(float deltaTime, GLFWwindow* window)
{
	//Test::OnUpdate(deltaTime, window);
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);
}

void test::TestGeometryShader::OnRender()
{
	Test::OnRender();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	Renderer renderer;
	renderer.Clear();
	if(nano_enable)
	{
		if (normal_enable) {
			m_model->Draw(*m_modelshaderNormal);
			m_modelshaderNormal->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
			m_modelshaderNormal->SetUniform4fMat("view", m_Camera->GetViewMatrix());
			m_modelshaderNormal->SetUniform4fMat("model", glm::mat4(1.0f));

		}
		m_model->Draw(*m_modelshaderBoom);
		m_modelshaderBoom->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
		m_modelshaderBoom->SetUniform4fMat("view", m_Camera->GetViewMatrix());
		m_modelshaderBoom->SetUniform4fMat("model", glm::mat4(1.0f));
		m_modelshaderBoom->SetUniform1f("time", GetTime());

	}
	else 
	{
		renderer.DrawPoints(*vao, *ibo, *m_shader);
	}
}

void test::TestGeometryShader::OnImGUIRender()
{

	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 8, 50.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);
	ImGui::Text("time:%f", GetTime());
	if(ImGui::Button(scene_label.c_str()))
	{
		nano_enable = !nano_enable;
		if(nano_enable)
		{
			scene_label = "Change to basic";
		}
		else
		{
			scene_label = "Change to nanosuit";
		}
	}

	if(nano_enable)
	{
		if (ImGui::Button(blow_label.c_str()))
		{
			blow_enable = !blow_enable;
			if (blow_enable)
			{
				blow_label = "disable blow";
				normal_enable = false;
				normal_label = "enable normal";
			}
			else
			{
				blow_label = "enable blow";
			}
		}

		if (ImGui::Button(normal_label.c_str()))
		{
			normal_enable = !normal_enable;
			if (normal_enable)
			{
				normal_label = "disable normal";
				blow_enable = false;
				blow_label = "enable blow";
			}
			else
			{
				normal_label = "enable normal";
			}
		}

	}
}

void test::TestGeometryShader::OnExit()
{
	Test::OnExit();
}

float test::TestGeometryShader::GetTime()
{
	if (blow_enable)
		return static_cast<float>(glfwGetTime());
	return glm::pi<float>()*3/2;
}
