#pragma once
#include "SceneObject.h"
class SkyBox :
	public SceneObject
{
	//void Draw();
	void Init();
	void Update();
	Vector3 initialPosition;
};

