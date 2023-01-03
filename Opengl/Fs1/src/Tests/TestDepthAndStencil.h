#pragma once
#include "Camera.h"
#include "VertexBufferLayout.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Test.h"

namespace test
{
	class TestDepthAndStencil :public test::Test
	{
	public:
		TestDepthAndStencil();
		~TestDepthAndStencil() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<VertexArray> m_CubeVAO,m_PlaneVAO;
		bool m_depth, m_stencil;
		float m_scale = 1.04f;
		std::unique_ptr<Shader> m_CubeShader,m_PlaneShader,m_EdgeShader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane;

		std::unique_ptr<Texture> m_cubeTexture, m_floorTexture;
		glm::vec3 cubeLocation, floorLocation;

	};
}