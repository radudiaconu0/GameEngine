#pragma once
#include <string>
struct  ModelResource
{
	std::string path;
	ModelResource(std::string path) {
		this->path = std::string(path);
	}
};
