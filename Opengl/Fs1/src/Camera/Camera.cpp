#include "Camera.h"

#include "imGui/imgui.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
:Front(glm::vec3(0.0f, 0.0f, -1.0f)),MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjMatrix()
{
    if(m_isOrtho)
    {
        return glm::mat4(1.0f);//todo
    }
    return glm::mat4(glm::perspective(glm::radians(Zoom), 4.0f / 3.0f, 0.1f, 1000.0f));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == Cam_Up)
        Position += Up * velocity;
    if (direction == Cam_DOWN)
        Position -= Up * velocity;

}

void Camera::ImGuiMouse(GLFWwindow* window)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    float xscroll = static_cast<float>(ImGui::GetIO().MouseWheel);
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 90.0f)
        Zoom = 90.0f;
    Zoom -= (float)xscroll * 3;
    if (state == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
    {
        float xpos = static_cast<float>(ImGui::GetIO().MousePos.x);
        float ypos = static_cast<float>(ImGui::GetIO().MousePos.y);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
        updateCameraVectors();

    }
    else if (state == GLFW_RELEASE)
    {
        firstMouse = true;

    }


}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
