#include "TestInstancing.h"

#include "VertexBufferLayout.h"
#include "imGui/imgui.h"

test::TestInstancing::TestInstancing()
{
	int index = 0;
	float offset = 2.0f;
	for (int i = -10; i < 10; i+=2)
	{
		for (int j =-10;j<10;j+=2)
		{
			glm::vec2 translation;
			translation.x = float(j) * 2 + offset;
			translation.y = float(i) * 2 + offset;
			translations[index++] = translation;
		}
	}
	instanceVb = std::make_unique<VertexBuffer>(translations, sizeof(glm::vec2)*100);
	m_quad = std::make_unique<Quad2D>();
	shader = std::make_unique<Shader>("res/shaders/InstancingQuad.Shader");
	m_texture = std::make_unique<Texture>("res/Texture/window.png");
	VertexBufferLayout layout;
	vao = std::make_unique<VertexArray>();
	m_quad->SetScale(glm::vec3(0.05f));
	m_quad->SetRenderState(*shader, *m_texture, layout, *vao, 0);
	vao->AddInstance(*instanceVb, 2, 2, 1);
	glEnable(GL_DEPTH_TEST);
}

test::TestInstancing::~TestInstancing()
{

}

void test::TestInstancing::OnUpdate(float deltaTime, GLFWwindow* window)
{

}

void test::TestInstancing::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	Renderer renderer;
	renderer.Clear();
	renderer.DrawInstance(*vao, *m_quad->GetIndexBufferPointer(), *shader,100);
	shader->SetUniform4fMat("model", m_quad->GetModelMatrix());

}

void test::TestInstancing::OnImGUIRender()
{
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void test::TestInstancing::OnExit()
{
	//Test::OnExit();
	m_texture->TextureRelease();
}
