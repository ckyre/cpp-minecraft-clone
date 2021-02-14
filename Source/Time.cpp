#include "Time.h"

float Time::time;
float Time::deltaTime;
float Time::lastTime;

void Time::Update()
{
	time = (float)glfwGetTime();
	deltaTime = float(time - lastTime);
	lastTime = time;
}