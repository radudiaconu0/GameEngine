#include "stdafx.h"
#include "rapidxml/rapidxml.hpp"
#include "ResourceManager.h"
#include "TextureResource.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
using namespace std;
using namespace rapidxml;
ResourceManager* ResourceManager::spInstance = NULL;

ResourceManager* ResourceManager::getInstance() {
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}
void ResourceManager::Init() {
	xml_document<> doc;
	std::ifstream file("resourceManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	int count = 0;
	xml_node<> *pModels = pRoot->first_node("models");
	for (xml_node<> *pNode = pModels->first_node("model"); pNode; pNode = pNode->next_sibling())
	{
		string path;
		int id;
		for (xml_attribute<> *pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			//xml_attribute<> *pAttr = pNodeAttr->next_attribute();
			std::string strValue = pNodeAttr->value();
			id = atoi(strValue.c_str());
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		// Do something here
		xml_node<> *pPathNode = pNode->first_node();
		path = pPathNode->value();
		cout << path << endl;
		ResourceManager::getInstance()->mModelRes[id] = new ModelResource(path);
	}
	xml_node<> *pShaders = pRoot->first_node("shaders");
	for (xml_node<> *pNode = pShaders->first_node("shader"); pNode; pNode = pNode->next_sibling())
	{
		string vs, fs;
		int id;
		for (xml_attribute<> *pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			//xml_attribute<> *pAttr = pNodeAttr->next_attribute();
			std::string strValue = pNodeAttr->value();
			id = atoi(strValue.c_str());
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		// Do something here

		xml_node<>  *pNodeFiu = pNode->first_node("vs");
		vs = string(pNodeFiu->value());
		pNodeFiu = pNode->first_node("fs");
		fs = string(pNodeFiu->value());
		ResourceManager::getInstance()->mShaderRes[id] = new ShaderResource(vs, fs);
	}
	xml_node<> *pTextures = pRoot->first_node("textures");
	for (xml_node<> *pNode = pTextures->first_node("texture"); pNode; pNode = pNode->next_sibling())
	{
		string path, min_filter, mag_filter, wrap_s, wrap_t, type;
		int id;
		for (xml_attribute<> *pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			//xml_attribute<> *pAttr = pNodeAttr->next_attribute();
			if (!strcmp(pNodeAttr->name(), "id")) {
				std::string strValue = pNodeAttr->value();
				id = atoi(strValue.c_str());
			}
			if (!strcmp(pNodeAttr->name(), "type")) {
				std::string strValue = pNodeAttr->value();
				type = strValue.c_str();
			}
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		// Do something here
		xml_node<> *pNodeFiu = pNode->first_node("path");
		path = pNodeFiu->value();
		pNodeFiu = pNode->first_node("min_filter");
		min_filter = pNodeFiu->value();
		pNodeFiu = pNode->first_node("mag_filter");
		mag_filter = pNodeFiu->value();
		pNodeFiu = pNode->first_node("wrap_s");
		wrap_s = pNodeFiu->value();
		pNodeFiu = pNode->first_node("wrap_t");
		wrap_t = pNodeFiu->value();
	
		ResourceManager::getInstance()->mTextureRes[id] = new TextureResource(path, min_filter, mag_filter, wrap_s, wrap_t, type);
	}
}
Texture* ResourceManager::LoadTexture(int id) {
	std::map<int, Texture*>::iterator it;
	it = mTextureLoaded.find(id);
	if (it != mTextureLoaded.end()) {
		return it->second;
	}
	else {
		Texture* texture;
		std::map<int, TextureResource*>::iterator itr;
		itr = mTextureRes.find(id);
		texture = new Texture(itr->second);
		texture->Load();
		mTextureLoaded[id] = texture;
		return texture;
	}
}
Model* ResourceManager::LoadModel(int id) {
	std::map<int, Model*>::iterator im;
	im = mModelLoaded.find(id);
	if (im != mModelLoaded.end()) {
		return im->second;
	}
	else {
		Model* model;
		std::map<int, ModelResource*>::iterator imr;
		imr = mModelRes.find(id);
		model = new Model(imr->second);
		model->Load();
		mModelLoaded[id] = model;
		return model;
	}
}
Shader* ResourceManager::LoadShader(int id) {
	std::map<int, Shader*>::iterator is;
	is = mShaderLoaded.find(id);
	if (is != mShaderLoaded.end()) {
		return is->second;
	}
	else {
		Shader* shader;
		std::map<int, ShaderResource*>::iterator isr;
		isr = mShaderRes.find(id);
		shader = new Shader(isr->second);
		shader->Load();
		mShaderLoaded[id] = shader;
		return shader;
	}
}
ResourceManager::ResourceManager() {

}
