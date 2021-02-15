#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
using namespace glm;

#pragma once
class Camera
{
public:
	vec3 position = vec3(0, 0, 5);
	vec3 forward = vec3(0, 0, 1);
	vec3 right = vec3(1, 0, 0);
	vec3 up = vec3(0, 1, 0);
	float fov = 45.0f;

	void computeMatrices();
	mat4 getProjMatrix();
	mat4 getViewMatrix();
private:
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 2.0f;
	float sensivity = 0.08f;

	mat4 proj = mat4(1);
	mat4 view = mat4(1);
};

