#pragma once

#include <memory>
#include <vector>
#include "Core/Window.h"
#include "Core/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Types/Mesh.hpp"
#include "Shader/Shader.h"
#include "Core/Camera.h" // Include the Camera header
#include "Game/Game.h"


class Engine {
public:
	Engine();
	~Engine();

	void Run();
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Shader> m_Shader;

private:
	void ProcessInput(float deltaTime);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	std::unique_ptr<Window> m_Window;
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<Camera> m_Camera;
	
	

	bool m_Running;
	

	Game m_Game;  // Game object that manages the scenes

	// Variables for mouse handling
	bool m_FirstMouse = true;
	float m_LastX = 0.0f;
	float m_LastY = 0.0f;
	
};
