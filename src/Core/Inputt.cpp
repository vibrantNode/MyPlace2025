#include "Input.h"


// Initialize static member
GLFWwindow* Input::m_Window = nullptr;

bool Input::IsKeyPressed(int key) {
    // Check if a specific key is pressed
    int state = glfwGetKey(m_Window, key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button) {
    // Check if a specific mouse button is pressed
    int state = glfwGetMouseButton(m_Window, button);
    return state == GLFW_PRESS;
}

void Input::GetMousePosition(double& x, double& y) {
    // Get the current mouse position
    glfwGetCursorPos(m_Window, &x, &y);
}

void Input::SetGLFWWindow(GLFWwindow* window) {
    // Set the GLFW window (this needs to be called once the window is created)
    m_Window = window;
}