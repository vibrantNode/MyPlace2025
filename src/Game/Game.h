#pragma once
#include "Scene.h"
#include <memory>

class Game {
public:
    Game();
    ~Game();

    void Init();       // Initialize the game and load the first scene
    void Update(float deltaTime);  // Update game logic
    void Render(Renderer& renderer, Camera& camera);

private:
    std::unique_ptr<Scene> currentScene;
};