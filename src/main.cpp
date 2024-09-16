


// Prevent accidentally selecting integrated GPU
extern "C" {
    __declspec(dllexport) unsigned __int32 AmdPowerXpressRequestHighPerformance = 0x1;
    __declspec(dllexport) unsigned __int32 NvOptimusEnablement = 0x1;
}


#include "GLFW/glfw3.h"
#include "Engine.h"

#include <iostream>



int main() 
{

    std::cout << "Welcome to my sanctuary.\n" << std::endl;
    
    if (!glfwInit()) {
        std::cout << "Failture";
    }


    Engine engine;
    engine.Run();

    return 0; 

}
