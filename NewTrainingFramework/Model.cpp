#include "stdafx.h"
#include "Model.h"
#include "ModelResource.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
Model::Model(ModelResource* mr)
{
	this->mr = mr;
}
void Model::Load() {
	string line;
	string mat[100];
	int k = 0;

	ifstream f(mr->path);
	int count = 0, count1 = 0;
	getline(f, line);
	char* p;
	nrOfVertexes = stoi(line.substr(12, sizeof(line)));
	w = new Vertex[nrOfVertexes];
	while (getline(f, line))
	{

		istringstream iss(line);
		if (line.find("NrIndices:") == 0)
		{
			break;
		}
		else
		{
			count++;
			line.erase(0, 6);
			char sep[] = "posbinormtguv;[],:";
			char* line1 = strdup(line.c_str());
			p = strtok(line1, sep);
			while (p)
			{
				string s = p;
				if (s.compare(" ") != 0) mat[++k] = s;
				p = strtok(NULL, sep);
				if (k == 3)
				{
					w[count - 1].pos.x = atof(_strdup(mat[1].c_str()));
					w[count - 1].pos.y = atof(_strdup(mat[2].c_str()));
					w[count - 1].pos.z = atof(_strdup(mat[3].c_str()));
				}
				else if (k == 6)
				{
					w[count - 1].norm.x = atof(_strdup(mat[4].c_str()));
					w[count - 1].norm.y = atof(_strdup(mat[5].c_str()));
					w[count - 1].norm.z = atof(_strdup(mat[6].c_str()));
				}
				else if (k == 9)
				{
					w[count - 1].binorm.x = atof(_strdup(mat[7].c_str()));
					w[count - 1].binorm.y = atof(_strdup(mat[8].c_str()));
					w[count - 1].binorm.z = atof(_strdup(mat[9].c_str()));
				}
				else if (k == 12)
				{
					w[count - 1].tgt.x = atof(_strdup(mat[10].c_str()));
					w[count - 1].tgt.y = atof(_strdup(mat[11].c_str()));
					w[count - 1].tgt.z = atof(_strdup(mat[12].c_str()));
				}
				else if (k == 14)
				{
					w[count - 1].uv.x = atof(_strdup(mat[13].c_str()));
					w[count - 1].uv.y = atof(_strdup(mat[14].c_str()));
				}
			}
			k = 0;
		}

	}
	nrIndici = stoi(line.substr(11, sizeof(line)));
	indices = new GLushort[nrIndici];
	while (getline(f, line))
	{
		char sep[] = ",.";

		line.erase(0, 6);

		char* line1 = strdup(line.c_str());
		p = strtok(line1, sep);
		while (p)
		{
			string s = p;
			p = strtok(NULL, sep);
			indices[count1] = stoi(s);
			count1++;
		}
		k = 0;
	}
	glGenBuffers(1, &(this->vboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * nrOfVertexes, w, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &(this->iboId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * this->nrIndici, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Model::Model()
{

}
Model::~Model()
{
}
