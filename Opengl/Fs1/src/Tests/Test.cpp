#include "Test.h"
#include "imGui/imgui.h"
namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer):m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGUIRender()
	{
		for(auto& test :m_Tests)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}
