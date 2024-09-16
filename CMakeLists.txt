cmake_minimum_required(VERSION "3.13")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

add_subdirectory("vendor/glfw")


project(MyHell2024)
set(CMAKE_CXX_STANDARD 17)




add_executable(MyHell2024 
	src/main.cpp
	src/Engine.cpp
	src/Core/Window.cpp 
	src/Core/Inputt.cpp
	src/Renderer/Renderer.cpp 
	src/Shader/Shader.cpp
)


target_include_directories(MyHell2024 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(MyHell2024 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Core")
target_include_directories(MyHell2024 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer")
target_include_directories(MyHell2024 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/Types")

target_link_libraries(MyHell2024 glfw ${CMAKE_DL_LIBS} opengl32)