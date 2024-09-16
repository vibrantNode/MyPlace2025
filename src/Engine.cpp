#include "Engine.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Types/Mesh.hpp"
#include "Shader/Shader.h"
#include <iostream>

// Acting weird flag = :   ------------------- **


// Define your vertex and index data
std::vector<float> vertices = {
    // Positions
    0.0f,  0.5f, 0.0f,  // Vertex 1
   -0.5f, -0.5f, 0.0f,  // Vertex 2
    0.5f, -0.5f, 0.0f   // Vertex 3
};

std::vector<unsigned int> indices = {
    0, 1, 2  // Triangle
};

// Engine init 
Engine::Engine()
    :m_Running(true) {
   
    // Initialize the GLFW window
    m_Window = std::make_unique<Window>("My Universe", 1280, 720);


    // Set the window for input management
    Input::SetGLFWWindow(m_Window->GetGLFWWindow());//------------------- **

    // Initialize the Renderer
    m_Renderer = std::make_unique<Renderer>();

    // Here, you can load any resources, such as shaders or meshes
}

Engine::~Engine()
{
}



// Engine Run
void Engine::Run() {

    Mesh myMesh(vertices, indices); 


    Shader myShader("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag");

    // Main loop
    while (m_Running && !m_Window->ShouldClose()) {
        // Process Input
        //ProcessInput();------------------- **

        // Clear the screen
        m_Renderer->Clear();

        // Issue your draw calls
        m_Renderer->Draw(myMesh, myShader);

        // Swap buffers and poll for events
        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}




/*
void Engine::ProcessInput() {
    // Check for user input and handle it
    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
        m_Running = false;  // Stop the main loop if Escape is pressed------------------- **
    }

    // Handle other inputs here
}

*/

