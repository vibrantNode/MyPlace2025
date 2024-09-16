#pragma once

#include "Core/Window.h"
#include "Renderer/Renderer.h"


class Engine {
public:
	Engine();
	//~Engine();

	void Run();

private:
	std::unique_ptr<Window>  m_Window;
	std::unique_ptr<Renderer> m_Renderer;
	bool m_Running;

	//void ProcessInput();
};
