#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <ext/matrix_clip_space.hpp> // glm::perspective
using namespace glm;
#pragma once

class Camera
{
	public:
		vec3 position = vec3(0, 0, 5);
		vec3 forward;
		vec3 right;
		vec3 up;
		float fov = 45.0f;

		void computeMatrices();
		mat4 getProjMatrix();
		mat4 getViewMatrix();
	private:
		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float speed = 3.0f;
		float sensivity = 0.08f;
		mat4 proj, view;
};


