#pragma once
#include <string>
#include "ModelResource.h"
#include "Vertex.h"
using namespace std;
class Model
{
public:

	Model(ModelResource *mr);
	ModelResource *mr;
	GLuint iboId;
	GLuint wiredIboId;
	GLuint vboId;
	int nrOfVertexes = 0;
	GLushort *indices;
	Vertex *w;
	GLushort nrIndici, nrIndiciWiredl;
	void Load();
	Model();
	~Model();
};

