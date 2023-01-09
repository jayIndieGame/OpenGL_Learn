#pragma once
#include "Camera.h"
#include "VertexBufferLayout.h"
#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Test.h"
#include "CubeTexture.h"

namespace test
{
	class TestSkyBoxAndReflect :public test::Test
	{
	public:
		TestSkyBoxAndReflect();
		~TestSkyBoxAndReflect() override;
		void OnUpdate(float deltaTime, GLFWwindow* window) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void OnExit() override;

	private:
		std::unique_ptr<VertexArray> m_CubeVAO,m_PlaneVAO;
		
		std::unique_ptr<Shader> m_CubeShader,m_PlaneShader,m_SkyboxShader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Cube> m_Skybox;
		std::unique_ptr<Plane> m_Plane;

		std::unique_ptr<Texture> m_cubeTexture, m_floorTexture;
		std::unique_ptr<CubeTexture> m_skyboxTexture;
		glm::vec3 cubeLocation, floorLocation;

		bool m_frac;
		std::string m_fraclabel;

		std::vector<std::string> m_cubemapPath = 
		{
			"res/Texture/skybox/right.jpg",
			"res/Texture/skybox/left.jpg",
			"res/Texture/skybox/top.jpg",
			"res/Texture/skybox/bottom.jpg",
			"res/Texture/skybox/front.jpg",
			"res/Texture/skybox/back.jpg",
		};
	};
}