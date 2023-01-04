

#include "TestAlphaAndCilp.h"

#include "HelperLibrary.h"
#include "imGui/imgui.h"

test::TestAlphaAndClip::TestAlphaAndClip():
cubeLocation(0,0,-200),floorLocation(0,0,0),
m_windows_location{
		glm::vec3(0.0f,40.0f, 40.0f),
		glm::vec3(-40.0f, 20.0f , -40.0f),
		glm::vec3(0.0f,0.0f, 0.0f)
}
{
	m_Cube = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Grass = std::make_unique<Plane>();
	m_Window = std::make_unique<Plane>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CubeShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_PlaneShader = std::make_unique<Shader>("res/shaders/DepthStencilObject.shader");
	m_GrassShader = std::make_unique<Shader>("res/shaders/AlphaAndClip.shader");
	m_WindowShader = std::make_unique<Shader>("res/shaders/AlphaAndClip.shader");
	m_cubeTexture = std::make_unique<Texture>("res/Texture/metal.png");
	m_floorTexture = std::make_unique<Texture>("res/Texture/marble.jpg");
	m_grassTexture = std::make_unique<Texture>("res/Texture/grass.png");
	m_windowTexture = std::make_unique<Texture>("res/Texture/window.png");
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();

	VertexBufferLayout cube_layout;


	//使用同个vao的layout要区分下，我setrenderstate中是push布局的，用同一个layout会重复
	//这里同种mesh使用了同一个vao，我随便写写的没啥依据。
	VertexBufferLayout plane_layout;
	VertexBufferLayout grass_layout;
	VertexBufferLayout window_layout;

	//初始化cube
	m_CubeVAO->Bind();
	m_Cube->SetLocation(cubeLocation);
	m_Cube->SetRenderState(*m_CubeShader, *m_cubeTexture,  cube_layout, *m_CubeVAO, 0);

	//初始化plane
	m_PlaneVAO->Bind();
	m_Plane->SetLocation(floorLocation);
	m_Plane->SetRenderState(*m_PlaneShader, *m_floorTexture, plane_layout, *m_PlaneVAO, 1);

	//
	m_Window->SetRotation(glm::vec3(glm::pi<float>()/2, 0, 0));
	m_Window->SetLocation(glm::vec3(100, 20, -100));
	m_Grass->SetRotation(glm::vec3(glm::pi<float>() / 2, 0, 0));
	m_Window->SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	m_Grass->SetScale(glm::vec3(0.2f));
	m_Grass->SetLocation(glm::vec3(-40, 20, -60));
	m_Window->SetRenderState(*m_WindowShader, *m_windowTexture, window_layout, *m_PlaneVAO, 2);
	m_Grass->SetRenderState(*m_GrassShader, *m_grassTexture, grass_layout, *m_PlaneVAO, 3);

	m_Camera->Position = glm::vec3(35, 25, 140);
	GLCALL(glEnable(GL_DEPTH_TEST))

}

test::TestAlphaAndClip::~TestAlphaAndClip()
{
}

void test::TestAlphaAndClip::OnUpdate(float deltaTime, GLFWwindow* window)
{
	//Test::OnUpdate(deltaTime, window);
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);

	if(m_enableBlend)
	{
		m_blend_button = "disable blend";
	}
	else
	{
		m_blend_button = "enable blend";
	}

	if(m_order)
	{
		m_order_button = "disable order";
		for (unsigned int i = 0; i < m_windows_location.size(); i++)
		{
			float distance = glm::length(m_Camera->Position - m_windows_location[i]);
			sorted[distance] = m_windows_location[i];
		}
	}
	else
	{
		m_order_button = "enable order";
	}
	if(m_clip)
	{
		m_clip_button = "disable clip";
	}
	else
	{
		m_clip_button = "enable clip";
	}
}

void test::TestAlphaAndClip::OnRender()
{
	GLCALL(glClearColor(0.02, 0.02, 0.02, 1.0f));
	Renderer render;
	render.Clear();

	//render cube 让cube写入stencil,always就行不需要比较
	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_CubeShader);
	m_CubeShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
	m_CubeShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_CubeShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());

	//render plane 但是不要让floor写stencil
	GLCALL(glStencilMask(0x00));
	render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_PlaneShader);
	m_Plane->SetScale(glm::vec3(5.0f));
	m_PlaneShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
	m_PlaneShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_PlaneShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());


	render.Draw(*m_PlaneVAO, *m_Grass->GetIndexBufferPointer(), *m_GrassShader);
	m_GrassShader->SetUniform4fMat("model", m_Grass->GetModelMatrix());
	m_GrassShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_GrassShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
	m_GrassShader->SetUniform1b("clip", m_clip);//为了clip不影响transparent，使用了两个shader实例

	if (m_enableBlend)
	{
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
	else
	{
		GLCALL(glDisable(GL_BLEND));
		m_order = false;
	}
	//画窗户,透明物体最后画,没必要关闭深度写入，反正我们是按distance逆序绘制的，并且所有opaque物体都画完了，这里不会有问题。但是后续比如做shadowmap，不画透明物体的阴影时，记得关。
	m_WindowShader->Bind();
	if (!m_order)
	{
		for (unsigned int i = 0; i < m_windows_location.size(); i++)
		{
			glm::mat4 model = glm::translate(m_Window->GetModelMatrix(), m_windows_location[i]);
			m_WindowShader->SetUniform4fMat("model", model);
			render.Draw(*m_PlaneVAO, *m_Window->GetIndexBufferPointer(), *m_WindowShader);
		}
	}
	else
	{
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			glm::mat4 model = glm::translate(m_Window->GetModelMatrix(), it->second);
			m_WindowShader->SetUniform4fMat("model", model);
			render.Draw(*m_PlaneVAO, *m_Window->GetIndexBufferPointer(), *m_WindowShader);//我平时懒得先bind shader，所以把draw写在了前面能省一行bind，但是这里不行，这里会导致物体2取了物体1的model矩阵，3取2的，1取3的，深度正好反了
		}
	}
	m_WindowShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_WindowShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());

	GLCALL(glDisable(GL_BLEND));//不要影响clip的物体

}

void test::TestAlphaAndClip::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 2, 50.0f);
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);

	if(ImGui::Button(m_blend_button.c_str()))
	{
		m_enableBlend = !m_enableBlend;
	}
	if(m_enableBlend)
	{
		if (ImGui::Button(m_order_button.c_str()))
			m_order = !m_order;
	}
	if(ImGui::Button(m_clip_button.c_str()))
	{
		m_clip = !m_clip;
	}
}

void test::TestAlphaAndClip::OnExit()
{
	//Test::OnExit();
	m_cubeTexture->TextureRelease();
	m_floorTexture->TextureRelease();
	m_windowTexture->TextureRelease();
	m_grassTexture->TextureRelease();
}
