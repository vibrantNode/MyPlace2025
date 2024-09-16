#include "Input.h"

GLFWwindow* Input::m_Window = nullptr;  // Static member definition

void Input::SetGLFWWindow(GLFWwindow* window)
{
	m_Window = window;
}
