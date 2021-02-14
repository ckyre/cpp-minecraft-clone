#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec2 uv;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 Normal_cameraspace;

void main()
{
    mat4 mvp = projMatrix * viewMatrix * modelMatrix;
	gl_Position = mvp * vec4(vertexPosition, 1.0);
	uv = vertexUV;

    // Position of the vertex, in worldspace : M * position
	Position_worldspace = (modelMatrix * vec4(vertexPosition, 1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( viewMatrix * modelMatrix * vec4(vertexPosition, 1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = (viewMatrix * vec4(0, 0, 5, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
    
    // Normal of the the vertex, in camera space
	Normal_cameraspace = (viewMatrix * modelMatrix * vec4(vertexNormal, 0)).xyz;

}