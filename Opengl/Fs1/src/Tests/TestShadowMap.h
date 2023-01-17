#pragma once
#include "Camera.h"
#include "Cube.h"
#include "FrameBuffer.h"
#include "Plane.h"
#include "Quad2D.h"
#include "RuntimeTexture.h"
#include "Test.h"
#include "Texture.h"

namespace test
{
	class TestShadowMap:public Test
	{
	public:
		TestShadowMap();
		~TestShadowMap() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<RuntimeTexture> m_rt;
		std::unique_ptr<FrameBuffer> m_frameBuffer;
		std::unique_ptr<VertexArray> m_CubeVAO, m_PlaneVAO,m_QuadVAO;
		std::unique_ptr<Shader> m_simpleDepthShader, m_debugDepth;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Quad2D> m_Quad2D;
		std::unique_ptr<Texture> m_Default;

		glm::vec3 cubeLocation, floorLocation,lightPos;
	};
}

