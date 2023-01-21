#include "TestShadowMap.h"

#include "HelperLibrary.h"
#include "VertexBufferLayout.h"
#include "imGui/imgui.h"

test::TestShadowMap::TestShadowMap():
	cubeLocation(0, 0, -200), floorLocation(0, 0, 0), lightPos(51.0f,- 24.0f, -150.0f)
{
	m_rt = std::make_unique<RuntimeTexture>(1024, 1024, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);
	m_frameBuffer = std::make_unique<FrameBuffer>();
	m_Cube = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Quad2D = std::make_unique<Quad2D>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_simpleDepthShader = std::make_unique<Shader>("res/shaders/ShadowmappingDepth.shader");
	m_debugDepth = std::make_unique<Shader>("res/shaders/ShadowmapDebug.shader");
	m_Default = std::make_unique<Texture>("res/Texture/wood.png");
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();
	m_QuadVAO = std::make_unique<VertexArray>();
	VertexBufferLayout cube_layout;
	VertexBufferLayout plane_layout;
	VertexBufferLayout quad_layout;
	//初始化cube
	m_Cube->SetLocation(cubeLocation);
	m_Cube->SetRenderState(*m_simpleDepthShader, *m_Default, cube_layout, *m_CubeVAO, 0);

	//初始化plane
	m_Plane->SetLocation(floorLocation);
	m_Plane->SetRenderState(*m_simpleDepthShader, *m_Default, plane_layout, *m_PlaneVAO, 0);


	//
	m_Camera->Position = glm::vec3(51.0f, -24.0f, -150.f);
	m_frameBuffer->Bind();
	m_Quad2D->SetRenderState(*m_debugDepth, *m_rt, quad_layout, *m_QuadVAO, GL_DEPTH_ATTACHMENT, 1);
	GLCALL(glDrawBuffer(GL_NONE));
	GLCALL(glReadBuffer(GL_NONE));
	m_frameBuffer->UnBind();


	glEnable(GL_DEPTH_TEST);
}

test::TestShadowMap::~TestShadowMap()
{
}

void test::TestShadowMap::OnUpdate(float deltaTime, GLFWwindow* window)
{
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);


}

void test::TestShadowMap::OnRender()
{
	GLCALL(glClearColor(0.02, 0.02, 0.02, 1.0f));
	Renderer render;
	render.Clear();

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 500.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	glViewport(0, 0, 1024, 1024);
	m_frameBuffer->Bind();


	m_simpleDepthShader->Bind();
	m_simpleDepthShader->SetUniform4fMat("lightSpaceMatrix", lightSpaceMatrix);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_rt->Bind(GL_DEPTH_ATTACHMENT, 1);
	m_Plane->SetScale(glm::vec3(5.0f));
	m_simpleDepthShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
	render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_simpleDepthShader);


	m_simpleDepthShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_simpleDepthShader);

	m_frameBuffer->UnBind();
	glViewport(0, 0, 1280, 960);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_debugDepth->Bind();
	m_debugDepth->SetUniform1f("near_plane", near_plane);
	m_debugDepth->SetUniform1f("far_plane", far_plane);
	m_debugDepth->SetUniform1i("u_Texture", 1);

	render.Draw(*m_QuadVAO, *m_Quad2D->GetIndexBufferPointer(), *m_debugDepth);


}

void test::TestShadowMap::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 2, 50.0f);
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);

}

void test::TestShadowMap::OnExit()
{
	glViewport(0, 0, 1280, 960);
	Test::OnExit();
}
