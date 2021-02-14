#include "Camera.h"
#include "Renderer.h"
#include "Time.h"

void Camera::computeMatrices()
{
	// Mouse inputs
	double mousePosX, mousePosY;
	glfwGetCursorPos(Renderer::window, &mousePosX, &mousePosY); // Read mouse position
	glfwSetCursorPos(Renderer::window, (double)(Renderer::windowWidth / 2), (double)(Renderer::windowHeight / 2)); // Replace cursor at center

	// View angles
	horizontalAngle += sensivity * Time::deltaTime * float((Renderer::windowWidth / 2) - mousePosX);
	verticalAngle += sensivity * Time::deltaTime * float((Renderer::windowHeight / 2) - mousePosY);

	// Relative vetors
	forward = vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	right = vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	up = cross(right, forward);

	// Move position
	if (glfwGetKey(Renderer::window, GLFW_KEY_W) == GLFW_PRESS) // Forward
		position += forward * Time::deltaTime * speed;
	if (glfwGetKey(Renderer::window, GLFW_KEY_S) == GLFW_PRESS) // Backward
		position -= forward * Time::deltaTime * speed;
	if (glfwGetKey(Renderer::window, GLFW_KEY_D) == GLFW_PRESS) // Right
		position += right * Time::deltaTime * speed;
	if (glfwGetKey(Renderer::window, GLFW_KEY_A) == GLFW_PRESS) // Left
		position -= right * Time::deltaTime * speed;

	// Calculate matices
	proj = perspective(radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	view = lookAt(position, position + forward, up);
}

mat4 Camera::getProjMatrix() { return proj; }

mat4 Camera::getViewMatrix() { return view; }