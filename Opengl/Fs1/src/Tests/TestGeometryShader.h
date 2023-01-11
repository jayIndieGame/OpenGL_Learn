#pragma once
#include "Camera.h"
#include "IndexBuffer.h"
#include "Model.h"
#include "Shader.h"
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace test
{
	class TestGeometryShader:public Test
	{
	public:
		TestGeometryShader();
		~TestGeometryShader() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		float m_points[5*4] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
		};

		unsigned int m_indexs[4] = {
			0,1,2,3
		};

		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<IndexBuffer> ibo;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Shader> m_modelshaderBoom;
		std::unique_ptr<Shader> m_modelshaderNormal;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Model> m_model;
		std::string scene_label,blow_label,normal_label;
		bool nano_enable, blow_enable,normal_enable;

		float GetTime();
	};


}
