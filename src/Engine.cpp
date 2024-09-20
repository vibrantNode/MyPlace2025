#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Types/Mesh.hpp"
#include "Shader/Shader.h"
#include <iostream>
#include "Core/Camera.h"
#include "Game/Game.h"

// Acting weird flag = :   ------------------- **


// Engine init 
Engine::Engine()
    :m_Running(true) {
   
    // Initialize the GLFW window
    m_Window = std::make_unique<Window>("My Universe", 1920, 1080);

    // Initialize the Renderer
    m_Renderer = std::make_unique<Renderer>();

    // Initialize camera at some default position and orientation
    m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f);

    // Set the window for input management
    Input::SetGLFWWindow(m_Window->GetGLFWWindow());//------------------- **

    // Set up mouse callback and user pointer
    glfwSetWindowUserPointer(m_Window->GetGLFWWindow(), this);
    glfwSetCursorPosCallback(m_Window->GetGLFWWindow(), MouseCallback);
    glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Hide cursor

    // Initialize the game
    m_Game.Init();
}

// Destroy Game
Engine::~Engine()
{
}


// Engine Run
void Engine::Run() {


    float lastFrame = 0.0f;

    // Main loop
    while (m_Running && !m_Window->ShouldClose()) {
        // Frame Logic
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(deltaTime);

        // Toggle wireframe mode
        if (m_WireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Enable solid mode
        }

        // Clear the screen
        m_Renderer->Clear();

        // Update and render the game (and the current scene)
        m_Game.Update(deltaTime);
        m_Game.Render(*m_Renderer, *m_Camera);
       
        // Swap buffers and poll for events
        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}


// Keyboard event listeners
void Engine::ProcessInput(float deltaTime) {
    if (Input::IsKeyPressed(GLFW_KEY_W))
        m_Camera->ProcessKeyboardInput(FORWARD, deltaTime);
    if (Input::IsKeyPressed(GLFW_KEY_S))
        m_Camera->ProcessKeyboardInput(BACKWARD, deltaTime);
    if (Input::IsKeyPressed(GLFW_KEY_A))
        m_Camera->ProcessKeyboardInput(LEFT, deltaTime);
    if (Input::IsKeyPressed(GLFW_KEY_D))
        m_Camera->ProcessKeyboardInput(RIGHT, deltaTime);
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        m_Running = false;
    if (Input::IsKeyPressed(GLFW_KEY_4))
        m_WireframeMode = !m_WireframeMode;
}



// Mouse event listeners
void Engine::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

    if (engine->m_FirstMouse) {
        engine->m_LastX = static_cast<float>(xpos);
        engine->m_LastY = static_cast<float>(ypos);
        engine->m_FirstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - engine->m_LastX;
    float yoffset = engine->m_LastY - static_cast<float>(ypos);  // Y-coordinates go from bottom to top
    engine->m_LastX = static_cast<float>(xpos);
    engine->m_LastY = static_cast<float>(ypos);

    engine->m_Camera->ProcessMouseMovement(xoffset, yoffset);
}

