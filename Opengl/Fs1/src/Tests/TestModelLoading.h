#pragma once
#include <Tests/Test.h>

#include "Camera.h"
#include "Model.h"
#include "Shader.h"

namespace test
{
	class TestModelLoading :public Test
	{
	public:
		TestModelLoading();
		~TestModelLoading() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Model>  m_model;
		std::unique_ptr<Camera> m_Camera;
	};
}
