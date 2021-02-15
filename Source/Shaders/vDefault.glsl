#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec2 uv;

void main()
{
    mat4 mvp = projMatrix * viewMatrix * modelMatrix;

	uv = vertexUV;
	gl_Position = mvp * vec4(vertexPosition, 1.0);
}