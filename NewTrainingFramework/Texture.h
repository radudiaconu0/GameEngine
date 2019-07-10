#pragma once
#include <string>
#include "../Utilities/utilities.h"
#include "TextureResource.h"
using namespace std;
class Texture
{
public:
	TextureResource *tr;
	GLuint id;
	int width, height;
	Texture(TextureResource *tr);
	void Load();
	~Texture();
};

