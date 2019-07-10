#pragma once
#include "SceneObject.h"
#include "Camera.h"
#include "Light.h"
#include <map>
class SceneManager
{
private:
	static SceneManager* spInstance;
	SceneManager();
public:
	static SceneManager* getInstance();
	map<int, SceneObject*> sceneObjects;
	Vector3 backgrountColor;
	map<int, Camera*> cameras;
	map<int, Light*> lights;
	Vector3 fogColor;
	Vector3 ambientalLight;
	GLfloat ratio;
	GLfloat bigRadius;
	GLfloat littleRadius;

	int activeCamera;
	void Init();
	void Draw();
	void Update();
	Camera* getActiveCamera();
	~SceneManager();
};

