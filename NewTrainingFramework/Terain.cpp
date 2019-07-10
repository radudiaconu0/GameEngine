#include "stdafx.h"
#include "Terain.h"
#include "../Utilities/Math.h"
#include "SceneManager.h"

void Terain::generateModel()
{

	for (size_t i = 0; i <= noCells; i++)
	{
		for (size_t j = 0; j <= noCells; j++)
		{
			Vertex v;
			v.pos = Vector3((-noCells) * cellDim / 2 + j * cellDim, -10, (-noCells) * cellDim / 2 + i * cellDim);
			v.uv = Vector2(i, j);
			v.uv2 = Vector2((float)i / noCells, (float)j / noCells);
			verticies.push_back(v);
			//indices.push_back(i * (noCells + 1) + j);
		}
	}
	for (size_t i = 0; i < noCells; i++)
	{
		for (size_t j = 0; j < noCells; j++)
		{
			indices.push_back(i * (noCells + 1) + j);
			indices.push_back(i * (noCells + 1) + j + 1);
			indices.push_back((i + 1) * (noCells + 1) + j);
			indices.push_back(i * (noCells + 1) + j + 1);
			indices.push_back((i + 1) * (noCells + 1) + j);
			indices.push_back((i + 1) * (noCells + 1) + j + 1);

		}
	}
	Vector3 cam_pos = SceneManager::getInstance()->getActiveCamera()->position;
	//this->position = Vector3(-noCells * cellDim / 2 + cam_pos.x, -noCells * cellDim / 2 + cam_pos.y, 0);
	//this->position = Vector3(-10, -10, 0);
	model = new Model();
	model->nrIndici = indices.size();
	glGenBuffers(1, &(model->vboId));
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &(model->iboId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * model->nrIndici, indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Terain::Draw()
{
	glUseProgram(this->shader->program);

	this->SendCommonData();
	if (this->shader->uvAttribute2 != -1)
	{
		glEnableVertexAttribArray(this->shader->uvAttribute2);

		glVertexAttribPointer(this->shader->uvAttribute2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(Vector3) + sizeof(Vector2)));
	}
	if (this->shader->heightUniform != -1)
	{
		glUniform3f(shader->heightUniform, heights.x, heights.y, heights.z);
	}
	int err = glGetError();

	glDrawElements(GL_TRIANGLES, this->model->nrIndici, GL_UNSIGNED_SHORT, 0);
	err = glGetError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Terain::Init()
{
	this->position = Vector3(SceneManager::getInstance()->getActiveCamera()->position.x, SceneManager::getInstance()->getActiveCamera()->position.y - this->offSetY, SceneManager::getInstance()->getActiveCamera()->position.z);
}
GLvoid Terain::Update()
{
	GLfloat CamX = SceneManager::getInstance()->getActiveCamera()->position.x;
	GLfloat terainX = this->position.x;
	GLfloat CamZ = SceneManager::getInstance()->getActiveCamera()->position.z;
	GLfloat terainZ = this->position.z;
	GLint dx = CamX - terainX;
	if (abs(dx) > cellDim)
	{
		if (dx < 0)
		{
			this->position.x -= cellDim;
			for (auto& vertice : verticies)
			{
				vertice.uv2.y -= 1 / (float)noCells;
			}
			glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (dx > 0)
		{
			this->position.x += cellDim;
			for (auto& vertice : verticies)
			{
				vertice.uv2.y += 1 / (float)noCells;
			}
			glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}

	GLint dz = CamZ - terainZ;
	if (abs(dz) > cellDim)
	{
		if (dz < 0)
		{
			this->position.z -= cellDim;
			for (auto& vertice : verticies)
			{
				vertice.uv2.x -= 1 / (float)noCells;
			}
			glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else if (dz > 0)
		{
			this->position.z += cellDim;
			for (auto& vertice : verticies)
			{
				vertice.uv2.x += 1 / (float)noCells;
			}
			glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), verticies.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}

}
Terain::Terain()
{
}


Terain::~Terain()
{
}
