#include "Texture.h"

Texture::Texture(const char* path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	data = Load(path);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

}

unsigned char* Texture::Load(const char* path)
{
	unsigned char* image = stbi_load(path, &width, &height, nullptr, 0);
	size = width * height * 3;
	if (image == NULL)
	{
		printf("Error in loading the texture\n");
		return 0;
	}
	return image;
}

GLuint Texture::GetId() { return id; }

int Texture::GetSize() { return size; }

int Texture::GetWidth() { return width; }

int Texture::GetHeight() { return height; }
