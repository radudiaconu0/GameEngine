#pragma once
#include "../../Utilities/Math.h"
class Light
{
public:
	Vector3 diffuseColor;
	Vector3 specularColor;
	GLint associatedObject;
	GLfloat specPower;

	std::string type;
	//Vector3 position;
	Vector3 direction;
	Light(Vector3, Vector3, GLint, std::string, Vector3, GLfloat);
};

