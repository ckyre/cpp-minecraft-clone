#version 330 core

in vec2 uv;
uniform sampler2D textureSampler;
out vec3 color;

void main()
{
	color = texture(textureSampler, uv).rgb;
}