#pragma once
#include <string>
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "ModelResource.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include <map>
using namespace std;
class ResourceManager
{
private:
	static ResourceManager* spInstance;
	ResourceManager();
public:
	void Init();
	static ResourceManager* getInstance();
	Texture *LoadTexture(int id);
	Model *LoadModel(int id);
	Shader *LoadShader(int id);
	map<int, ModelResource*> mModelRes;
	map<int, ShaderResource*> mShaderRes;
	map<int, TextureResource*> mTextureRes;
	map<int, Model*> mModelLoaded;
	map<int, Shader*> mShaderLoaded;
	map<int, Texture*> mTextureLoaded;
};

