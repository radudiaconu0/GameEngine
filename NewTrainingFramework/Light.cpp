#include "stdafx.h"
#include "Light.h"

Light::Light(Vector3 diffuseColor, Vector3 specularColor, GLint associatedObject, std::string type, Vector3 direction, GLfloat specPower)
{
	this->diffuseColor = diffuseColor;
	this->associatedObject = associatedObject;
	this->specularColor = specularColor;
	this->associatedObject = associatedObject;
	this->type = type;
	this->direction = direction;
	this->specPower = specPower;
}