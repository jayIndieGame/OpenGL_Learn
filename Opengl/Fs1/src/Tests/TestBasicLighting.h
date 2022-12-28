#pragma once
#include "Camera.h"
#include "Cube.h"
#include "Test.h"

#include "Texture.h"
#include "memory"
#include "imGui/imgui.h"


namespace test
{
	class TestBasicLighting :public Test
	{
	public:
		TestBasicLighting();
		~TestBasicLighting() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture_Diffuse,m_Texture_Specular;
		glm::vec3 objectLocation, initLocation, objectRotation, lightPos;
		ImVec4 m_Color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f), lightColor;
	};
}


