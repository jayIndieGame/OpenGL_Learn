#pragma once
#include <GL/glew.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

namespace test
{
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime, GLFWwindow* window) {  }
		virtual void OnRender() {}
		virtual void OnImGUIRender() {}
		virtual void OnExit(){}

	};


	class TestMenu:public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);


		void OnImGUIRender() override;

		template<typename T>
		void Register(const std::string& name)
		{
			std::cout << "Register test" << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}
