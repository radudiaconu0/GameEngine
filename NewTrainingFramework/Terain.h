#pragma once
#include "SceneObject.h"
class Terain :public SceneObject
{
public:
	vector <GLushort> indices;
	vector <Vertex> verticies;
	GLfloat noCells, cellDim, offSetY;
	Vector3 heights;
	void generateModel();
	void Draw();
	void Init();
	void  Update();
	Terain();
	~Terain();
};

