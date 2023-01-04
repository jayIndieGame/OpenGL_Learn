#pragma once
#include "Camera.h"
#include "VertexBufferLayout.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Test.h"
#include <map>

namespace test
{
	class TestAlphaAndClip :public test::Test
	{
	public:
		TestAlphaAndClip();
		~TestAlphaAndClip() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<VertexArray> m_CubeVAO,m_PlaneVAO;
		std::unique_ptr<Shader> m_CubeShader,m_PlaneShader, m_GrassShader, m_WindowShader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Plane> m_Plane,m_Grass,m_Window;

		std::unique_ptr<Texture> m_cubeTexture, m_floorTexture, m_grassTexture,m_windowTexture;
		glm::vec3 cubeLocation, floorLocation;
		std::vector<glm::vec3> m_windows_location;
		std::map<float, glm::vec3> sorted;

		bool m_enableBlend,m_order,m_clip;
		std::string m_blend_button,m_order_button,m_clip_button;
	};
}