#pragma once
#include "SceneObject.h"
class Fire :
	public SceneObject
{
public:
	void Draw();
	void Update();
	GLfloat dispMax;
};

