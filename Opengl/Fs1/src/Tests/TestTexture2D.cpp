#include "TestTexture2D.h"
#include "TestClearColor.h"
#include "..//Renderer.h"
#include "imGui/imgui.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include  "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "Shader.h"

namespace test
{
	TestTexture2D::TestTexture2D():
		m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(0,0,0),
		m_Color(0.8f, 0.3f, 0.8f, 1.0f)
	{
		float vertices[] = {
				//position      //texture coordinates
				-0.5f,-0.5f,	0.0f,0.0f,
				0.5f,-0.5f,		1.0f,0.0f,
				0.5f,0.5f,		1.0f,1.0f,
				-0.5f,0.5f,		0.0f,1.0f
		};

		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		GLCALL(glEnable(GL_BLEND))
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shaders/TestTexture.shader");
		//m_Texture = std::make_unique<Texture>("res/Model/backpack/diffuse.jpg", "u_Texture", true);
		m_Texture = std::make_unique<Texture>("res/Texture/awesomeface.png");
		m_VAO = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
        //VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);
        //IndexBuffer ibo(indices, 6);


		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
		
	}

	TestTexture2D::~TestTexture2D()
	{
		GLCALL(glDisable(GL_BLEND))
		//GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void TestTexture2D::OnUpdate(float deltaTime, GLFWwindow* window)
	{

	}

	void TestTexture2D::OnRender()
	{
		//Test::OnRender();
		GLCALL(glClearColor(0, 0, 0, 1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		Renderer render;
		m_Texture->Bind();



		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniform4fMat("u_MVP", mvp);
			m_Shader->SetUniform4f("u_Color", m_Color.x, m_Color.y, m_Color.z, 1.0f);
			render.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImGUIRender()
	{
		ImGui::ColorEdit3("Texture Color", (float*)&m_Color);
		ImGui::SliderFloat3("Texture Offset", &m_Translation.x, -1.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void TestTexture2D::OnExit()
	{
		//Test::OnExit();
		m_Texture->TextureRelease();
	}
}

