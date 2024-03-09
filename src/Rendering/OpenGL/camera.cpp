#include "Rendering/OpenGL/camera.hpp"

Camera::Camera()
	: GameObject("Camera")
{
	transform.SetPosition({ 0, -1, -10 });
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}
