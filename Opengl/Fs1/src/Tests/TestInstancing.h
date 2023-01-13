#pragma once
#include "Camera.h"
#include "IndexBuffer.h"
#include "Model.h"
#include "Shader.h"
#include "Test.h"
#include "VertexArray.h"
#include "glm/glm.hpp"
#include "Quad2D.h"

namespace test
{
	class TestInstancing:public Test
	{
	public:
		TestInstancing();
		~TestInstancing() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;
	private:
		std::unique_ptr<VertexBuffer> instanceVb;
		std::unique_ptr<Shader> planet_shader;
		std::unique_ptr<Shader> rock_shader;
		std::unique_ptr<Model> planet;
		std::unique_ptr<Model> rock;
		std::unique_ptr<Camera> m_Camera;
		
		glm::vec2 translations[100];
		glm::mat4* modelMatrices;

		unsigned int m_amount = 10000;
		float m_radius, m_offset;
	};

}
