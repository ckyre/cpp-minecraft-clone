#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class Time
{
	public:
		static float time;
		static float deltaTime;

		static void Update();

	private:
		static float lastTime;
};