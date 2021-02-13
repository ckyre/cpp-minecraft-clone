#include "Texture.h"

Texture::Texture(const char* path)
{
	glGenTextures(1, &id);
	Bind();
	Load(path);
}

GLuint Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
	return id;
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::Load(const char* path)
{
	// Load image
	unsigned char* image = stbi_load(path, &width, &height, nullptr, 0);
	if (image == NULL)
	{
		printf("Error in loading the texture\n");
		return false;
	}

	// Enable trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Send to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

GLuint Texture::GetId() { return id; }

int Texture::GetSize() { return width * height * 3; }

int Texture::GetWidth() { return width; }

int Texture::GetHeight() { return height; }
