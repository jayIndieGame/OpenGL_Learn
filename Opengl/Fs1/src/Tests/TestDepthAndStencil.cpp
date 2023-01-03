#include "TestDepthAndStencil.h"

#include "HelperLibrary.h"
#include "imGui/imgui.h"

test::TestDepthAndStencil::TestDepthAndStencil():
cubeLocation(0,0,-200),floorLocation(0,0,0)
{
	m_Cube = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CubeShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_PlaneShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_EdgeShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_cubeTexture = std::make_unique<Texture>("res/Texture/metal.png");
	m_floorTexture = std::make_unique<Texture>("res/Texture/marble.jpg");
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();
	VertexBufferLayout cube_layout;
	VertexBufferLayout plane_layout;
	//初始化cube
	m_CubeVAO->Bind();
	m_Cube->SetLocation(cubeLocation);
	m_Cube->SetRenderState(*m_CubeShader, *m_cubeTexture,  cube_layout, *m_CubeVAO, 0);
	m_CubeShader->SetUniform1i("u_Texture", 0);

	//初始化plane
	m_PlaneVAO->Bind();
	m_Plane->SetLocation(floorLocation);
	m_Plane->SetRenderState(*m_PlaneShader, *m_floorTexture, plane_layout, *m_PlaneVAO, 1);
	m_PlaneShader->SetUniform1i("u_Texture", 1);

	//
	m_Camera->Position = glm::vec3(51.0f, -24.0f, -150.f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
	GLCALL(glClearColor(0.02, 0.02, 0.02, 1.0f));
	Renderer render;
	render.Clear();

	//render plane 但是不要让floor写stencil
	GLCALL(glStencilMask(0x00));
	render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_PlaneShader);
	m_Plane->SetScale(glm::vec3(5.0f));
	m_PlaneShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
	m_PlaneShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_PlaneShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_PlaneShader->SetUniform1b("Depth", m_depth);

	//render cube 让cube写入stencil,always就行不需要比较
	GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
	GLCALL(glStencilMask(0xFF));//这里不开的话1写进去按位与就成0了
	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_CubeShader);
	m_CubeShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
	m_CubeShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_CubeShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_CubeShader->SetUniform1b("Depth", m_depth);


	m_EdgeShader->Bind();
	if (m_stencil) {
		//stencil 描边 就是画一个大一点的正方形关闭模板写入 关闭深度写入避免描边写入深度buffer
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::scale(m_Cube->GetModelMatrix(), glm::vec3(m_scale));
		m_EdgeShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
		m_EdgeShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
		m_EdgeShader->SetUniform4fMat("model", model);

		render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_EdgeShader);

		GLCALL(glBindVertexArray(0));
		GLCALL(glStencilMask(0xFF));
		GLCALL(glStencilFunc(GL_ALWAYS, 0, 0xFF));
		glEnable(GL_DEPTH_TEST);
	}
	m_EdgeShader->SetUniform1b("stencil", m_stencil);

}

void test::TestDepthAndStencil::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 2, 50.0f);
	ImGui::SliderFloat("stencil edge width", &m_scale, 1.01f, 1.1f);
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);

	if(ImGui::Button("Depth"))
	{
		m_depth = !m_depth;
	}


	if (ImGui::Button("stencil"))
	{
		m_stencil = !m_stencil;
	}

	if (ImGui::Button("reset"))
	{
		m_depth = false;
		m_stencil = false;
	}
}

void test::TestDepthAndStencil::OnExit()
{
	//Test::OnExit();
	m_cubeTexture->TextureRelease();
	m_floorTexture->TextureRelease();
}
