#pragma once
#include "IndexBuffer.h"
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
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> instanceVb;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Quad2D> m_quad;
		std::unique_ptr<Texture> m_texture;
		
		glm::vec2 translations[100];
	};

}
