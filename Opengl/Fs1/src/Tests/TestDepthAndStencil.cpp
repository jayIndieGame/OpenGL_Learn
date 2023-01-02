#include "TestDepthAndStencil.h"

#include "HelperLibrary.h"

test::TestDepthAndStencil::TestDepthAndStencil():
cubeLocation(0,0,0),floorLocation(0,0,0)
{
	m_Cube = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CubeShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_PlaneShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_EdgeShader = std::make_unique<Shader>("res/shaders/DepthStencilEdge.shader");
	m_cubeTexture = std::make_unique<Texture>("res/Texture/metal.png");
	m_floorTexture = std::make_unique<Texture>("res/Texture/marble.png");
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();
	VertexBufferLayout cube_layout;
	VertexBufferLayout plane_layout;

	m_Cube->SetRenderState(*m_CubeShader, *m_cubeTexture,  cube_layout, *m_CubeVAO, 0);
	m_Plane->SetRenderState(*m_PlaneShader, *m_floorTexture, plane_layout, *m_PlaneVAO, 1);
}

test::TestDepthAndStencil::~TestDepthAndStencil()
{
}

void test::TestDepthAndStencil::OnUpdate(float deltaTime, GLFWwindow* window)
{
	//Test::OnUpdate(deltaTime, window);
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);
}

void test::TestDepthAndStencil::OnRender()
{
	GLCALL(glClearColor(0, 0, 0, 1.0f));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	Renderer render;
	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_CubeShader);
	render.Draw(*m_PlaneVAO, *m_Cube->GetIndexBufferPointer(), *m_PlaneShader);
	// m_Shader->SetUniform4f("u_Color", m_Color.x, m_Color.y, m_Color.z, 1);
	m_Cube->SetLocation(objectLocation + initLocation);
	m_Cube->SetRotation(objectRotation);
	//view = glm::translate(glm::mat4(1.0f), cameraTranslation);
	//glm::mat4 mvp = proj * view * model;
	m_Shader->SetUniform4fMat("u_model", m_Cube->GetModelMatrix());
	m_Shader->SetUniform4fMat("u_model", m_Cube->GetModelMatrix());
	m_Shader->SetUniform4fMat("u_view", m_Camera->GetViewMatrix());
	m_Shader->SetUniform4fMat("u_project", m_Camera->GetProjMatrix());

	m_Shader->SetUniform3f("viewPos", m_Camera->Position);
	m_Shader->SetUniform1f("material.shininess", 64.0f);
}

void test::TestDepthAndStencil::OnImGUIRender()
{
	Test::OnImGUIRender();
}

void test::TestDepthAndStencil::OnExit()
{
	Test::OnExit();
}
