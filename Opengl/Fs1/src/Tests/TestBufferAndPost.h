#pragma once
#include "Camera.h"
#include "VertexBufferLayout.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Test.h"
#include "FrameBuffer.h"
#include "Quad2D.h"
#include "RuntimeRenderBuffer.h"
#include "RuntimeTexture.h"

enum PostRenderMode
{
	null,
	grayscale,
	antiphase,
	convolution,
	blur,
	sobel
};

namespace test
{
	class TestBufferAndPost :public test::Test
	{
	public:
		TestBufferAndPost();
		~TestBufferAndPost() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<VertexArray> m_CubeVAO,m_PlaneVAO,m_QuadVAO;
		std::unique_ptr<Shader> m_CubeShader,m_PlaneShader,m_SceenQuadShader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Quad2D> m_Quad;
		std::unique_ptr<FrameBuffer> m_frameBuffer;
		std::unique_ptr<RuntimeTexture> m_rt;
		std::unique_ptr<RuntimeRenderbuffer> m_rb;

		std::unique_ptr<Texture> m_cubeTexture, m_floorTexture;
		glm::vec3 cubeLocation, floorLocation;

		std::string label_frameBuffer, label_grayscale, label_antiphase, label_convolution, label_blur,label_sobel;
		bool enable_frameBuffer, enable_grayscale, enable_antiphase,enable_convolution, enable_blur, enable_sobel;
		PostRenderMode m_postMode;
		void ChangeRenderMode(PostRenderMode mode);
	};
}