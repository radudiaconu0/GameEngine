#include "stdafx.h"
#include "SkyBox.h"
#include "SceneManager.h"


void SkyBox::Init()
{
	this->position = initialPosition;

}

void SkyBox::Update()
{
	if (this->following == true)
	{

		if (followingCamera.x == 1)
			this->position.x += SceneManager::getInstance()->getActiveCamera()->position.x;
		if (followingCamera.y == 1)
			this->position.y += SceneManager::getInstance()->getActiveCamera()->position.y;
		if (followingCamera.z == 1)
			this->position.z += SceneManager::getInstance()->getActiveCamera()->position.z;

	}
}
