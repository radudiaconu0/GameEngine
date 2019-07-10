#pragma once
#include "../../Utilities/Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <map>
class SceneObject
{
public:
	int id;
	string name;
	string type;
	Vector3 rotation;
	Vector3 position;
	Vector3 scale;
	Vector3 color;
	Vector3 followingCamera;
	GLfloat u_Time;
	bool following = false;
	map<int ,Texture*> textures;
	Model *model;
	Shader *shader;
	bool depthTest;
	SceneObject();
	~SceneObject();
	virtual void Draw();
	void SendCommonData();
	virtual GLvoid Init();
	virtual void Update();
	virtual GLvoid generateModel() {};
};

