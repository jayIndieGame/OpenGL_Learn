#include "TestSkyBoxAndReflect.h"

#include "HelperLibrary.h"
#include "imGui/imgui.h"

test::TestSkyBoxAndReflect::TestSkyBoxAndReflect():
cubeLocation(0,0,-200),floorLocation(0,0,0)
{
	m_Cube = std::make_unique<Cube>();
	m_Skybox = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CubeShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_SkyboxShader = std::make_unique<Shader>("res/shaders/SkyBoxAndReflect.shader");
	m_PlaneShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_cubeTexture = std::make_unique<Texture>("res/Texture/window.png");
	m_floorTexture = std::make_unique<Texture>("res/Texture/marble.jpg");
	m_skyboxTexture = std::make_unique<CubeTexture>(m_cubemapPath);
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();
	VertexBufferLayout cube_layout;
	VertexBufferLayout skybox_layout;
	VertexBufferLayout plane_layout;
	//初始化cube
	m_CubeVAO->Bind();
	m_Cube->SetLocation(cubeLocation);
	m_Cube->SetCubeBoxRenderState(*m_SkyboxShader, *m_skyboxTexture,  cube_layout, *m_CubeVAO, 0);
	m_cubeTexture->Bind(1);
	m_Skybox->SetCubeBoxRenderState(*m_SkyboxShader, *m_skyboxTexture, skybox_layout, *m_CubeVAO, 0);

	//初始化plane
	m_PlaneVAO->Bind();
	m_Plane->SetLocation(floorLocation);
	m_Plane->SetRenderState(*m_PlaneShader, *m_floorTexture, plane_layout, *m_PlaneVAO, 2);
	m_frac = false;
	m_fraclabel = "enable refract";
	//
	m_Camera->Position = glm::vec3(100.0f, 100.0f, 200.f);
	m_Camera->SetZOOM(90.0f);
	GLCALL(glEnable(GL_DEPTH_TEST));
	GLCALL(glDepthFunc(GL_LESS));


}

test::TestSkyBoxAndReflect::~TestSkyBoxAndReflect()
{
}

void test::TestSkyBoxAndReflect::OnUpdate(float deltaTime, GLFWwindow* window)
{
	//Test::OnUpdate(deltaTime, window);
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);
}

void test::TestSkyBoxAndReflect::OnRender()
{
	GLCALL(glClearColor(0.02, 0.02, 0.02, 1.0f));
	Renderer render;
	render.Clear();


	render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_PlaneShader);
	m_Plane->SetScale(glm::vec3(5.0f));
	m_PlaneShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
	m_PlaneShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_PlaneShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());


	m_SkyboxShader->Bind();
	m_SkyboxShader->SetUniform1b("skybox", false);
	m_SkyboxShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
	m_SkyboxShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_SkyboxShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_SkyboxShader->SetUniform3f("cameraPos", m_Camera->Position);
	m_SkyboxShader->SetUniform1i("u_Diffuse", 1);
	m_SkyboxShader->SetUniform1b("refrac", m_frac);
	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_SkyboxShader);
	GLCALL(glDepthFunc(GL_LEQUAL));  // change depth function so depth test passes when values are equal to depth buffer's content

	m_SkyboxShader->SetUniform4fMat("model", glm::mat4(1.0f));
	m_SkyboxShader->SetUniform4fMat("view", glm::mat4(glm::mat3(m_Camera->GetViewMatrix())));
	m_SkyboxShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_SkyboxShader->SetUniform1b("skybox", true);
	render.Draw(*m_CubeVAO, *m_Skybox->GetIndexBufferPointer(), *m_SkyboxShader);


	GLCALL(glDepthFunc(GL_LESS));
}

void test::TestSkyBoxAndReflect::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 2, 50.0f);
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);
	if(ImGui::Button(m_fraclabel.c_str()))
	{
		m_frac = !m_frac;
		if(m_frac)
		{
			m_fraclabel = "enable reflect";
		}else
		{
			m_fraclabel = "enable refract";
		}
	}
}

void test::TestSkyBoxAndReflect::OnExit()
{
	//Test::OnExit();
	m_cubeTexture->TextureRelease();
	m_floorTexture->TextureRelease();
}
