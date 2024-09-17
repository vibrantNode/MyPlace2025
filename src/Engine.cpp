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
    m_Window = std::make_unique<Window>("My Universe", 1280, 720);
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

    // Initialize Meshes and shaders


    // Define a fixed rotation to make the rectangle a plane and scale it
    // glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)); // Scale by 5
    //m_FixedRotation = scale * rotation; // Apply scaling after rotation


    m_Game.Init();
}

// Destroy Game
Engine::~Engine()
{
}


// Engine Run
void Engine::Run() {


    float lastFrame = 0.0f;
    float angle = 0.0f;  // Rotation angle

    // Main loop
    while (m_Running && !m_Window->ShouldClose()) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(deltaTime);

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
}

// Mouse callback function definition
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

