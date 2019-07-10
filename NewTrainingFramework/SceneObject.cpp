#include "stdafx.h"
#include "SceneObject.h"
#include "../Utilities/Math.h"
#include "SceneManager.h"
#include "Texture.h"
#include <map>
SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::Draw()
{
	glUseProgram(this->shader->program);

	this->SendCommonData();
	int err = glGetError();

	glDrawElements(GL_TRIANGLES, this->model->nrIndici, GL_UNSIGNED_SHORT, 0);
	err = glGetError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SceneObject::SendCommonData()
{
	Matrix world;
	Matrix mat;
	Matrix S, T, Rx, Ry, Rz;
	S.SetScale(this->scale);
	T.SetTranslation(this->position);
	Rx.SetRotationX(this->rotation.x);
	Ry.SetRotationY(this->rotation.y);
	Rz.SetRotationZ(this->rotation.z);


	mat.SetIdentity();
	mat = S * Rx * Ry * Rz * T * SceneManager::getInstance()->getActiveCamera()->viewMatrix * SceneManager::getInstance()->getActiveCamera()->perspMatrix;
	world = S * Rx * Ry * Rz * T;
	glBindBuffer(GL_ARRAY_BUFFER, this->model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->iboId);
	map<int, Texture*>::iterator it;
	int i = 0;
	int err = glGetError();
	for (it = textures.begin(); it != textures.end(); it++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		i++;
		if (this->shader->uniformtexture[i] != -1)
		{
			glUniform1i(this->shader->uniformtexture[i], i);
			//glVertexAttribPointer(myShaders.uniformrotation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(Vector3));
		}

		glBindTexture((it->second->tr->type == "2d") ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP, it->second->id);
	}
	map<int, Light*>::iterator itT;
	i = 0;
	for (itT = SceneManager::getInstance()->lights.begin(); itT != SceneManager::getInstance()->lights.end(); itT++)
	{

		
		if (this->shader->specColor[i] != -1)
		{
			glUniform3f(this->shader->specColor[i], itT->second->specularColor.x, itT->second->specularColor.y, itT->second->specularColor.z);
		}
		if (this->shader->direction[i] != -1)
		{
			glUniform3f(this->shader->direction[i], itT->second->direction.x, itT->second->direction.y, itT->second->direction.z);
		}
		if (this->shader->specPower[i] != -1)
		{
			glUniform1f(this->shader->specPower[i], itT->second->specPower);
		}
		if (this->shader->diffuseColor[i] != -1)
		{
			glUniform3f(this->shader->diffuseColor[i], itT->second->diffuseColor.x, itT->second->diffuseColor.y, itT->second->diffuseColor.z);
		}
		i++;
		
	}
	if (this->shader->ratio != -1)
	{
		glUniform1f(this->shader->ratio, SceneManager::getInstance()->ratio);
	}
	if(this->shader->normalAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->normalAttribute);
		glVertexAttribPointer(this->shader->normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (this->shader->ambientalLight != -1)
	{
		glUniform3f(this->shader->ambientalLight, SceneManager::getInstance()->ambientalLight.x, SceneManager::getInstance()->ambientalLight.y, SceneManager::getInstance()->ambientalLight.z);
	}
	if (this->shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->uvAttribute);
		glVertexAttribPointer(this->shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(Vector3)));
	}
	if (this->shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->positionAttribute);
		glVertexAttribPointer(this->shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (this->shader->colorAttribute != -1)
	{
		glEnableVertexAttribArray(this->shader->colorAttribute);
		glVertexAttribPointer(this->shader->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(Vector3));
	}
	if (this->shader->uniformrotation != -1)
	{
		glUniformMatrix4fv(this->shader->uniformrotation, 1, GL_FALSE, (float*)mat.m);
		//glVertexAttribPointer(myShaders.uniformrotation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(Vector3));
	}
	if (this->shader->littleRadius != -1)
	{
		glUniform1f(this->shader->littleRadius, SceneManager::getInstance()->littleRadius);
	}
	if (this->shader->bigRadius != -1)
	{
		glUniform1f(this->shader->bigRadius, SceneManager::getInstance()->bigRadius);
	}
	if (this->shader->fogColor != -1)
	{
		glUniform3f(this->shader->fogColor, SceneManager::getInstance()->fogColor.x, SceneManager::getInstance()->fogColor.y, SceneManager::getInstance()->fogColor.z);
	}
	if (this->shader->model != -1)
	{
		glUniformMatrix4fv(this->shader->model, 1, GL_FALSE, (float*)world.m);

	}
	if (this->shader->camPos != -1)
	{
		Vector3 cam_Pos = SceneManager::getInstance()->getActiveCamera()->position;
		glUniform3f(this->shader->camPos, cam_Pos.x, cam_Pos.y, cam_Pos.z);

	}
}

void SceneObject::Init()
{

}

void SceneObject::Update()
{
}
