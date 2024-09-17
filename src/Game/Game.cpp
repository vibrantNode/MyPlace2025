#include "Game.h"
#include "Scene.h"

Game::Game() : currentScene(nullptr) {}

Game::~Game() {}

void Game::Init() {
    // Create and initialize the first scene
    currentScene = std::make_unique<Scene>();
    currentScene->Init();  // Initialize scene-specific assets like shaders, meshes, etc.
}

void Game::Update(float deltaTime) {
    if (currentScene) {
        currentScene->Update(deltaTime);
    }
}

void Game::Render(Renderer& renderer, Camera& camera) {
    if (currentScene) {
        currentScene->Render(renderer, camera);  // Call the scene's render function
    }
}