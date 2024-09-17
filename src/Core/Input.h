#pragma once
#include "GLFW/glfw3.h"

class Input {
public:
    static bool IsKeyPressed(int key);
    static bool IsMouseButtonPressed(int button);
    static void GetMousePosition(double& x, double& y);

    static void SetGLFWWindow(GLFWwindow* window);

private:
    static GLFWwindow* m_Window;
};

