#include "TestInstancing.h"

#include "HelperLibrary.h"
#include "VertexBufferLayout.h"
#include "imGui/imgui.h"

test::TestInstancing::TestInstancing()
{
    rock = std::make_unique<Model>("res/Model/rock/rock.obj");
	planet = std::make_unique<Model>("res/Model/planet/planet.obj");
    planet_shader = std::make_unique<Shader>("res/shaders/InstancingPlanet.shader");
    rock_shader = std::make_unique<Shader>("res/shaders/InstancingPlanet.shader");

    m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));

    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)i / (float)m_amount * 360.0f;
        float displacement = (rand() % (int)(2 * m_offset * 100)) / 100.0f - m_offset;
        float x = sin(angle) * m_radius + displacement;
        displacement = (rand() % (int)(2 * m_offset * 100)) / 100.0f - m_offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * m_offset * 100)) / 100.0f - m_offset;
        float z = cos(angle) * m_radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    instanceVb = std::make_unique<VertexBuffer>(&modelMatrices[0], m_amount * sizeof(glm::mat4));
    VertexBufferLayout layout;
    layout.PushInstance<glm::mat4>(1, 3, 1);
    layout.PushInstance<glm::mat4>(1, 4, 1);
    layout.PushInstance<glm::mat4>(1, 5, 1);
    layout.PushInstance<glm::mat4>(1, 6, 1);

    for (unsigned int i = 0; i < rock->meshes.size(); i++)
    {
        VertexArray tempVao = rock->meshes[i].GetVertexArray();
        tempVao.Bind();

        tempVao.AddInstance(*instanceVb, layout);

        tempVao.UnBind();
    }


	glEnable(GL_DEPTH_TEST);
}

test::TestInstancing::~TestInstancing()
{

}

void test::TestInstancing::OnUpdate(float deltaTime, GLFWwindow* window)
{
    m_Camera->ImGuiMouse(window);
    Helper::processInput(window, *m_Camera, deltaTime);
}

void test::TestInstancing::OnRender()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	Renderer renderer;
	renderer.Clear();
    planet->Draw(*planet_shader);
    planet_shader->SetUniform4fMat("projection", m_Camera->GetProjMatrix());
    planet_shader->SetUniform4fMat("view", m_Camera->GetViewMatrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -150.0f, 0.0f));
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
    planet_shader->SetUniform4fMat("model", model);

    for (unsigned int i = 0;i<rock->meshes.size();i++)
    {
        renderer.DrawInstance(rock->meshes[i].GetVertexArray(), rock->meshes[i].GetIndexBuffer(), *rock_shader, m_amount);
        rock->meshes[i].GetVertexArray().UnBind();
    }
}

void test::TestInstancing::OnImGUIRender()
{
	//Test::OnImGUIRender();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void test::TestInstancing::OnExit()
{
    ImGui::SliderFloat("Camera Speed", &m_Camera->MovementSpeed, 8, 50.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("camera Location X %f", m_Camera->Position.x);
    ImGui::Text("camera Location Y %f", m_Camera->Position.y);
    ImGui::Text("camera Location Z %f", m_Camera->Position.z);
}
