#include "TestBufferAndPost.h"

#include "HelperLibrary.h"
#include "imGui/imgui.h"

test::TestBufferAndPost::TestBufferAndPost():
cubeLocation(0,0,-200),floorLocation(0,0,0), m_postMode(PostRenderMode::null)
{
	m_Cube = std::make_unique<Cube>();
	m_Plane = std::make_unique<Plane>();
	m_Quad = std::make_unique<Quad2D>();
	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CubeShader = std::make_unique<Shader>("res/shaders/BufferAndPost.shader");
	m_PlaneShader = std::make_unique<Shader>("res/shaders/BufferAndPost.shader");
	m_SceenQuadShader = std::make_unique<Shader>("res/shaders/BufferQuad.shader");
	m_cubeTexture = std::make_unique<Texture>("res/Texture/window.png");
	m_floorTexture = std::make_unique<Texture>("res/Texture/container2.png");
	m_rt = std::make_unique<RuntimeTexture>(1280, 960, GL_RGB, GL_RGB);
	m_CubeVAO = std::make_unique<VertexArray>();
	m_PlaneVAO = std::make_unique<VertexArray>();
	m_QuadVAO = std::make_unique<VertexArray>();

	VertexBufferLayout cube_layout;
	VertexBufferLayout plane_layout;
	VertexBufferLayout quad_layout;

	//初始化cube
	m_CubeVAO->Bind();
	m_Cube->SetLocation(cubeLocation);
	m_Cube->SetRenderState(*m_CubeShader, *m_cubeTexture,  cube_layout, *m_CubeVAO, 0);

	//初始化plane
	m_PlaneVAO->Bind();
	m_Plane->SetLocation(floorLocation);
	m_Plane->SetRenderState(*m_PlaneShader, *m_floorTexture, plane_layout, *m_PlaneVAO, 1);

	//初始化screen quad
	m_QuadVAO->Bind();
	m_frameBuffer = std::make_unique<FrameBuffer>();
	m_frameBuffer->Bind();
	m_Quad->SetRenderState(*m_SceenQuadShader, *m_rt, quad_layout, *m_QuadVAO, GL_COLOR_ATTACHMENT0,2);
	m_rb = std::make_unique<RuntimeRenderbuffer>(1280, 960, GL_DEPTH24_STENCIL8);
	m_rb->BindRenderbuffer(GL_DEPTH_STENCIL_ATTACHMENT);
	m_Quad->SetScale(glm::vec3(0.4f,0.53333f,0.f));
	m_Quad->SetLocation(glm::vec3(0.6f, 0.466666f, 0));
	m_Camera->Position = glm::vec3(30.0f, 65.0f, 250.f);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	glEnable(GL_DEPTH_TEST);


}

test::TestBufferAndPost::~TestBufferAndPost()
{
}

void test::TestBufferAndPost::OnUpdate(float deltaTime, GLFWwindow* window)
{
	//Test::OnUpdate(deltaTime, window);
	m_Camera->ImGuiMouse(window);
	Helper::processInput(window, *m_Camera, deltaTime);
	if(enable_frameBuffer)
	{
		label_frameBuffer = "disable Framebuffer";
	}
	else
	{
		label_frameBuffer = "enable Framebuffer";
	}
}

void test::TestBufferAndPost::OnRender()
{
	GLCALL(glClearColor(0.02, 0.02, 0.02, 1.0f));
	Renderer render;
	if (enable_frameBuffer) {
		m_frameBuffer->Bind();
		render.Clear();

		render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_PlaneShader);
		m_Plane->SetScale(glm::vec3(5.0f));
		m_PlaneShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
		m_PlaneShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
		m_PlaneShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());

		render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_CubeShader);
		m_CubeShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
		m_CubeShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
		m_CubeShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());

		//重置
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	//glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClear(GL_COLOR_BUFFER_BIT);

	render.Draw(*m_PlaneVAO, *m_Plane->GetIndexBufferPointer(), *m_PlaneShader);
	m_Plane->SetScale(glm::vec3(5.0f));
	m_PlaneShader->SetUniform4fMat("model", m_Plane->GetModelMatrix());
	m_PlaneShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_PlaneShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());



	render.Draw(*m_CubeVAO, *m_Cube->GetIndexBufferPointer(), *m_CubeShader);
	m_CubeShader->SetUniform4fMat("model", m_Cube->GetModelMatrix());
	m_CubeShader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
	m_CubeShader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());

	if (enable_frameBuffer) {
		m_SceenQuadShader->Bind();
		m_SceenQuadShader->SetUniform4fMat("model", m_Quad->GetModelMatrix());
		render.Draw(*m_QuadVAO, *m_Quad->GetIndexBufferPointer(), *m_SceenQuadShader);
		m_SceenQuadShader->SetUniform1b("antiphase", enable_antiphase);
		m_SceenQuadShader->SetUniform1b("grayscale", enable_grayscale);
		m_SceenQuadShader->SetUniform1b("convolution", enable_convolution);
		m_SceenQuadShader->SetUniform1b("blur", enable_blur);
		m_SceenQuadShader->SetUniform1b("sobel", enable_sobel);
	}




}

void test::TestBufferAndPost::OnImGUIRender()
{
	ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 2, 50.0f);
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("camera Location X %f", m_Camera->Position.x);
	ImGui::Text("camera Location Y %f", m_Camera->Position.y);
	ImGui::Text("camera Location Z %f", m_Camera->Position.z);

	if(ImGui::Button(label_frameBuffer.c_str()))
	{
		enable_frameBuffer = !enable_frameBuffer;
		
	}
	if(enable_frameBuffer)
	{
		if(ImGui::Button(label_antiphase.c_str()))
		{
			ChangeRenderMode(PostRenderMode::antiphase);

		}
		if (ImGui::Button(label_grayscale.c_str()))
		{
			ChangeRenderMode(PostRenderMode::grayscale);

		}
		if (ImGui::Button(label_convolution.c_str()))
		{
			ChangeRenderMode(PostRenderMode::convolution);

		}
		if (ImGui::Button(label_blur.c_str()))
		{
			ChangeRenderMode(PostRenderMode::blur);

		}
		if (ImGui::Button(label_sobel.c_str()))
		{
			ChangeRenderMode(PostRenderMode::sobel);

		}
	}
	else
	{
		ChangeRenderMode(PostRenderMode::null);
	}

}

void test::TestBufferAndPost::OnExit()
{
	//Test::OnExit();
	m_cubeTexture->TextureRelease();
	m_floorTexture->TextureRelease();
	m_rt->TextureRelease();
}

void test::TestBufferAndPost::ChangeRenderMode(PostRenderMode mode)
{
	m_postMode = mode;
	switch (mode)
	{
	case PostRenderMode::null:
		enable_grayscale = false;
		label_grayscale = "enable grayscale";
		enable_antiphase = false;
		label_antiphase = "enable antiphase";
		enable_convolution = false;
		label_convolution = "enable convolution";
		enable_blur = false;
		label_blur = "enable blur";
		enable_sobel = false;
		label_sobel = "enable soble";
		break;
	case PostRenderMode::convolution:
		enable_grayscale = false;
		label_grayscale = "enable grayscale";
		enable_antiphase = false;
		label_antiphase = "enable antiphase";
		enable_convolution = !enable_convolution;
		if (enable_convolution)
			label_convolution = "disable convolution";
		else{
			label_convolution = "enable convolution";
		}
		enable_blur = false;
		label_blur = "enable blur";
		enable_sobel = false;
		label_sobel = "enable soble";
		break;
	case PostRenderMode::grayscale:
		enable_grayscale = !enable_grayscale;
		if (enable_grayscale)
			label_grayscale = "disable grayscale";
		else {
			label_grayscale = "enable grayscale";
		}
		enable_antiphase = false;
		label_antiphase = "enable antiphase";
		enable_convolution = false;
		label_convolution = "enable convolution";
		enable_blur = false;
		label_blur = "enable blur";
		enable_sobel = false;
		label_sobel = "enable soble";
		break;
	case PostRenderMode::antiphase:
		enable_grayscale =false;
		label_grayscale = "enable grayscale";
		enable_antiphase = !enable_antiphase;
		if (enable_antiphase)
			label_antiphase = "disable antiphase";
		else {
			label_antiphase = "enable antiphase";
		}
		enable_convolution = false;
		label_convolution = "enable convolution";
		enable_blur = false;
		label_blur = "enable blur";
		enable_sobel = false;
		label_sobel = "enable soble";
		break;
	case PostRenderMode::blur:
		enable_grayscale = false;
		label_grayscale = "enable grayscale";
		enable_antiphase = false;
		label_antiphase = "enable antiphase";
		enable_convolution = false;
		label_convolution = "enable convolution";
		enable_blur = !enable_blur;
		if (enable_blur)
			label_blur = "disable blur";
		else {
			label_blur = "enable blur";
		}
		enable_sobel = false;
		label_sobel = "enable soble";
		break;
	case PostRenderMode::sobel:
		enable_grayscale = false;
		label_grayscale = "enable grayscale";
		enable_antiphase = false;
		label_antiphase = "enable antiphase";
		enable_convolution = false;
		label_convolution = "enable convolution";
		enable_blur = false;
		label_blur = "enable blur";
		enable_sobel = !enable_sobel;
		if (enable_sobel)
			label_sobel = "disable sobel";
		else {
			label_sobel = "enable sobel";
		}
		break;
	}
}


