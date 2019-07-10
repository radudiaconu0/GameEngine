#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/TGA.h"

void Texture::Load()
{
	int err = glGetError();
	int type = (tr->type == "2d" ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP);
	err = glGetError();
	int bpp;
	char* pixels = LoadTGA(tr->path.c_str(), &width, &height, &bpp);
	err = glGetError();
	glGenTextures(1, &id);
	err = glGetError();
	glBindTexture(type, id);
	err = glGetError();
	if (tr->min_filter == "LINEAR")
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	else
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (tr->mag_filter == "LINEAR")
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	else
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (tr->wrap_s == "CLAMP_TO_EDGE")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	else if (tr->wrap_s == "REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else if (tr->wrap_s == "MIRRORED_REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	if (tr->wrap_t == "CLAMP_TO_EDGE")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	else if (tr->wrap_t == "REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	else if (tr->wrap_t == "MIRRORED_REPEAT")
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	err = glGetError();
	int texture_format = (bpp == 32) ? GL_RGBA : GL_RGB;
	if (tr->type == "2d")
	{
		glTexImage2D(type, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, pixels);
	}
	else
	{
		int Width = width;
		int Height = height;
		width /= 4;
		height/=3;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, 0);
		err = glGetError();
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + (Width * height + 2 * width) * bpp / 8 + Width * (bpp / 8) * i);
		}
		err = glGetError();
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, 0);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + Width * height * bpp / 8 + Width * (bpp / 8) * i);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, pixels);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + width * bpp / 8 + Width * (bpp / 8) * i);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, pixels);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + (Width * height * 2 + width) * bpp / 8 + Width * (bpp / 8) * i);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, pixels);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + (Width * height + width) * bpp / 8 + Width * (bpp / 8) * i);
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, pixels);
		for (int i = 0; i < height; i++) {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, i, width, 1, texture_format, GL_UNSIGNED_BYTE, pixels + (Width * height + 3 * width) * bpp / 8 + Width * (bpp / 8) * i);
		}
		err = glGetError();
	}

	err = glGetError();

}

Texture::Texture(TextureResource* tr) {
	this->tr = tr;
}
Texture::~Texture()
{
}
