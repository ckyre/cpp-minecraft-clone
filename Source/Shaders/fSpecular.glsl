#version 330 core

in vec2 uv;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 Normal_cameraspace;

uniform sampler2D textureSampler;

out vec3 color;

void main()
{
	vec3 lightPosition = vec3(0, 0, 5);
	vec3 lightColor = vec3(1, 0, 0);
	float lightPower = 20;
	float lightDistance = distance(Position_worldspace, lightPosition);

	vec3 materialDiffuseColor = texture(textureSampler, uv).rgb; 
	vec3 materialAmbientColor = vec3(0.4, 0.4, 0.4) * materialDiffuseColor;

	vec3 E = normalize(EyeDirection_cameraspace); // Eye vector (towards the camera)
	vec3 R = reflect(-LightDirection_cameraspace, Normal_cameraspace); // Direction in which the triangle reflects the light

	float cosAlpha = clamp( dot(E, R), 0, 1);

	color = materialAmbientColor + 
			materialDiffuseColor * lightColor * lightPower * pow(cosAlpha, 5) / (lightDistance*lightDistance);
}