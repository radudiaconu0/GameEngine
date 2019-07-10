#pragma once

#include <string>
struct TextureResource
{
	std::string path, min_filter, mag_filter, wrap_s, wrap_t, type;
	TextureResource(std::string path, std::string min_filter, std::string mag_filter, std::string wrap_s, std::string wrap_t, std::string type) {
		this->path = std::string(path);
		this->min_filter = std::string(min_filter);
		this->mag_filter = std::string(mag_filter);
		this->wrap_s = std::string(wrap_s);
		this->wrap_t = std::string(wrap_t); 
		this->type = std::string(type);
	}
};
