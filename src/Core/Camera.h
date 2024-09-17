#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera(glm::vec3 position, float yaw, float pitch);

	// Updating the camera's direction based on mouse movement
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	// Update the camer's position based on keyboard input
	void ProcessKeyboardInput(int direction, float deltaTime);

	// Get the view matrix (used for rendering)
	glm::mat4 GetViewMatrix() const;

	// FOV
	float GetZoom() const;

	// Getter for FoV
	float GetFoV() const { return m_FoV; }

	// Setter for FoV
	void SetFoV(float fov) { m_FoV = fov; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	// Camera roation angles
	float m_Yaw;
	float m_Pitch;
	float m_Zoom;
	float m_FoV; // Field of View

	// Update the camera vectors based on yaw and pitch
	void UpdateCameraVectors();
};


// Movement direction

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};