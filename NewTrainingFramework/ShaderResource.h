#pragma once
#include <string>
struct ShaderResource
{
	std::string vs, fs;
	
	ShaderResource(std::string vs, std::string fs) {
		this->vs = std::string(vs);
		this->fs = std::string(fs);
	
	}
};
