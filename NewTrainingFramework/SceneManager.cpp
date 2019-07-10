#include "stdafx.h"
#include "rapidxml/rapidxml.hpp"
#include "SceneManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "ResourceManager.h"
#include "SceneObject.h"
#include "Terain.h"
#include "Fire.h"

using namespace rapidxml;

SceneManager* SceneManager::spInstance = NULL;
SceneManager* SceneManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new SceneManager();
	}
	return spInstance;
}
Camera* SceneManager::getActiveCamera()
{
	return this->cameras[activeCamera];
}
void SceneManager::Init()
{
	int err = glGetError();
	xml_document<> doc;
	std::ifstream file("sceneManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<>* pRoot = doc.first_node();
	xml_node<>* pBack = pRoot->first_node("backgroundColor");
	xml_node<>* pNode = pBack->first_node("r");
	float r = atof(pNode->value());
	pNode = pBack->first_node("g");
	float g = atof(pNode->value());
	pNode = pBack->first_node("b");
	float b = atof(pNode->value());
	pBack = pRoot->first_node("fog");
	float bigR = atof(pBack->first_node("R")->value());
	float littleR = atof(pBack->first_node("r")->value());
	pNode = pRoot->first_node("fog")->first_node("color");
	float R = atof(pNode->first_node("r")->value());

	float G = atof(pNode->first_node("g")->value());

	float B = atof(pNode->first_node("b")->value());
	SceneManager::getInstance()->backgrountColor = Vector3(r, g, b);
	SceneManager::getInstance()->fogColor = Vector3(R, G, B);
	SceneManager::getInstance()->littleRadius = littleR;
	SceneManager::getInstance()->bigRadius = bigR;
	xml_node<>* pCameras = pRoot->first_node("cameras");
	xml_node<>* pActiveCamera = pRoot->first_node("activeCamera");
	SceneManager::getInstance()->activeCamera = atoi(pActiveCamera->value());
	for (xml_node<>* pNode = pCameras->first_node("camera"); pNode; pNode = pNode->next_sibling())
	{
		Vector3 position;
		Vector3 target;
		Vector3 up;
		GLfloat translationSpeed;
		GLfloat rotationSpeed;
		GLfloat fov;
		GLfloat Near;
		GLfloat Far;

		int id;
		for (xml_attribute<>* pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			//xml_attribute<> *pAttr = pNodeAttr->next_attribute();
			std::string strValue = pNodeAttr->value();
			id = atoi(strValue.c_str());
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		// Do something here
		for (xml_node<>* pNodeFiu = pNode->first_node(); pNodeFiu; pNodeFiu = pNodeFiu->next_sibling())
		{
			if (!strcmp(pNodeFiu->name(), "position"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("x");
				int x = atoi(pPos->value());
				pPos = pNodeFiu->first_node("y");
				int y = atoi(pPos->value());
				pPos = pNodeFiu->first_node("z");
				int z = atoi(pPos->value());
				position = Vector3(x, y, z);
			}
			else if (!strcmp(pNodeFiu->name(), "target"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("x");
				int x = atoi(pPos->value());
				pPos = pNodeFiu->first_node("y");
				int y = atoi(pPos->value());
				pPos = pNodeFiu->first_node("z");
				int z = atoi(pPos->value());
				target = Vector3(x, y, z);
			}
			else if (!strcmp(pNodeFiu->name(), "up"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("x");
				int x = atoi(pPos->value());
				pPos = pNodeFiu->first_node("y");
				int y = atoi(pPos->value());
				pPos = pNodeFiu->first_node("z");
				int z = atoi(pPos->value());
				up = Vector3(x, y, z);
			}
			else if (!strcmp(pNodeFiu->name(), "translationSpeed"))
			{
				translationSpeed = atof(pNodeFiu->value());
			}
			else if (!strcmp(pNodeFiu->name(), "rotationSpeed"))
			{
				rotationSpeed = atof(pNodeFiu->value());
			}
			else if (!strcmp(pNodeFiu->name(), "fov"))
			{
				fov = atof(pNodeFiu->value());
			}
			else if (!strcmp(pNodeFiu->name(), "near"))
			{
				Near = atof(pNodeFiu->value());
			}
			else if (!strcmp(pNodeFiu->name(), "far"))
			{
				Far = atof(pNodeFiu->value());
			}

		}
		SceneManager::getInstance()->cameras[id] = new Camera(position, target, up, translationSpeed, rotationSpeed, Near, Far, fov);
	}
	xml_node<>* pLights = pRoot->first_node("lights");
	for (xml_node<>* pNode = pLights->first_node("light"); pNode; pNode = pNode->next_sibling())
	{
		Vector3 diffuseColor;
		Vector3 specularColor;
		Vector3 direction;
		GLfloat specPower;
		GLint associatedObject;
		std::string type;

		int id;
		for (xml_attribute<>* pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			//xml_attribute<> *pAttr = pNodeAttr->next_attribute();
			std::string strValue = pNodeAttr->value();
			id = atoi(strValue.c_str());
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		// Do something here
		for (xml_node<>* pNodeFiu = pNode->first_node(); pNodeFiu; pNodeFiu = pNodeFiu->next_sibling())
		{
			if (!strcmp(pNodeFiu->name(), "diffuseColor"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("r");
				float r = atof(pPos->value());
				pPos = pNodeFiu->first_node("g");
				float g = atof(pPos->value());
				pPos = pNodeFiu->first_node("b");
				float b = atof(pPos->value());
				diffuseColor = Vector3(r, g, b);
			}
			else if (!strcmp(pNodeFiu->name(), "specularColor"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("r");
				float r = atof(pPos->value());
				pPos = pNodeFiu->first_node("g");
				float g = atof(pPos->value());
				pPos = pNodeFiu->first_node("b");
				float b = atof(pPos->value());
				specularColor = Vector3(r, g, b);
			}
			else if (!strcmp(pNodeFiu->name(), "associatedObject"))
			{
				associatedObject = stoi(pNodeFiu->value());
			}
			else if (!strcmp(pNodeFiu->name(), "type"))
			{
				type = pNodeFiu->value();
			}
			else if (!strcmp(pNodeFiu->name(), "direction"))
			{
				xml_node<>* pPos = pNodeFiu->first_node("x");
				float x = atof(pPos->value());
				pPos = pNodeFiu->first_node("y");
				float y = atof(pPos->value());
				pPos = pNodeFiu->first_node("z");
				float z = atof(pPos->value());
				direction = Vector3(x, y, z);
			}
			else if (!strcmp(pNodeFiu->name(), "specPower"))
			{
	
				specPower = atof(pNodeFiu->value());
				
										
			}

		}
		SceneManager::getInstance()->lights[id] = new Light(diffuseColor, specularColor, associatedObject, type, direction, specPower);
	}
	xml_node<>* pAmb = pRoot->first_node("ambientalLight");
	float Rr = atof(pAmb->first_node("color")->first_node("r")->value());
	float Gg = atof(pAmb->first_node("color")->first_node("g")->value());
	float Bb = atof(pAmb->first_node("color")->first_node("b")->value());
	float ratio = atof(pAmb->first_node("ratio")->value());
	SceneManager::getInstance()->ambientalLight = Vector3(Rr, Gg, Bb);
	SceneManager::getInstance()->ratio = ratio;

	xml_node<>* pObjects = pRoot->first_node("objects");
	for (xml_node<>* pNode = pObjects->first_node("object"); pNode; pNode = pNode->next_sibling())
	{
		SceneObject* sc;
		Model* m;
		Shader* s;
		Texture* t;
		string type = pNode->first_node("type")->value();
		if (type == "fire")
		{
			Fire* fire = new Fire();
			for (xml_attribute<>* pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
			{
				xml_attribute<>* pAttr = pNodeAttr->next_attribute();
				std::string strValue = pNodeAttr->value();
				fire->id = stoi(strValue);
			}
			for (xml_node<>* pNodeFiu = pNode->first_node(); pNodeFiu; pNodeFiu = pNodeFiu->next_sibling())
			{
				char* name = pNodeFiu->name();

				if (!strcmp(name, "dispMax"))
				{
					fire->dispMax = atof(pNodeFiu->value());
				}


				std::cout << pNodeFiu->value() << endl;

				SceneManager::getInstance()->sceneObjects[fire->id] = fire;
			}

			sc = fire;
		}

		else if (type == "teren")
		{
			Terain* terain = new Terain();
			for (xml_attribute<>* pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
			{
				xml_attribute<>* pAttr = pNodeAttr->next_attribute();
				std::string strValue = pNodeAttr->value();
				terain->id = stoi(strValue);
			}
			for (xml_node<>* pNodeFiu = pNode->first_node(); pNodeFiu; pNodeFiu = pNodeFiu->next_sibling())
			{
				char* name = pNodeFiu->name();

				if (!strcmp(name, "dim_cel"))
				{
					terain->cellDim = atoi(pNodeFiu->value());
				}
				else if (!strcmp(name, "nr_celule"))
				{
					terain->noCells = atoi(pNodeFiu->value());
				}
				else if (!strcmp(name, "offsetY"))
				{
					terain->offSetY = atoi(pNodeFiu->value());
				}
				else if (!strcmp(name, "inaltimi"))
				{
					xml_node<>* pNodeFiu1 = pNodeFiu->first_node("r");
					float r = atof(pNodeFiu1->value());
					pNodeFiu1 = pNodeFiu->first_node("g");
					float g = atof(pNodeFiu1->value());
					pNodeFiu1 = pNodeFiu->first_node("b");
					float b = atof(pNodeFiu1->value());
					terain->heights = Vector3(r, g, b);
				}

				std::cout << pNodeFiu->value() << endl;

				SceneManager::getInstance()->sceneObjects[terain->id] = terain;
			}

			sc = terain;
		}
		else {
			sc = new SceneObject();
		}
		for (xml_attribute<>* pNodeAttr = pNode->first_attribute(); pNodeAttr; pNodeAttr = pNodeAttr->next_attribute())
		{
			xml_attribute<>* pAttr = pNodeAttr->next_attribute();
			std::string strValue = pNodeAttr->value();
			sc->id = stoi(strValue);
			//std::cout << pNodeAttr->name() << ":";
			//std::cout << strValue << " " << endl;

			// Do something here
		}
		for (xml_node<>* pNodeFiu = pNode->first_node(); pNodeFiu; pNodeFiu = pNodeFiu->next_sibling())
		{
			char* name = pNodeFiu->name();
			if (!strcmp(name, "model")) {
				if (strcmp(pNodeFiu->value(), "generated")) {
					int idm = atoi(pNodeFiu->value());
					m = ResourceManager::getInstance()->LoadModel(idm);
					sc->model = m;
				}
				else sc->generateModel();
			}

			else if (!strcmp(name, "type"))
			{
				sc->type = pNodeFiu->value();
			}
			else if (!strcmp(name, "name"))
			{
				sc->name = pNodeFiu->value();
			}
			else if (!strcmp(name, "shader"))
			{
				int ids = atoi(pNodeFiu->value());
				int err = glGetError();
				s = ResourceManager::getInstance()->LoadShader(ids);
				err = glGetError();
				sc->shader = s;
			}
			else if (!strcmp(name, "textures"))
			{
				for (xml_node<>* pNodeText = pNodeFiu->first_node(); pNodeText; pNodeText = pNodeText->next_sibling())
				{
					xml_attribute<>* pNodeAttr = pNodeText->first_attribute();
					int idt = atoi(pNodeAttr->value());
					t = ResourceManager::getInstance()->LoadTexture(idt);
					sc->textures[idt] = t;
					std::cout << idt;
				}
			}
			else if (!strcmp(name, "rotation"))
			{
				xml_node<>* pNodeFiu1 = pNodeFiu->first_node("x");
				float x = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("y");
				float y = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("z");
				float z = atof(pNodeFiu1->value());
				sc->rotation = Vector3(x, y, z);

			}
			else if (!strcmp(name, "scale"))
			{
				xml_node<>* pNodeFiu1 = pNodeFiu->first_node("x");
				float x = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("y");
				float y = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("z");
				float z = atof(pNodeFiu1->value());
				sc->scale = Vector3(x, y, z);

			}
			else if (!strcmp(name, "position"))
			{
				xml_node<>* pNodeFiu1 = pNodeFiu->first_node("x");
				float x = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("y");
				float y = atof(pNodeFiu1->value());
				pNodeFiu1 = pNodeFiu->first_node("z");
				float z = atof(pNodeFiu1->value());
				sc->position = Vector3(x, y, z);

			}
			else if (!strcmp(name, "followingCamera"))
			{
				int x, y, z;
				xml_node<>* pNodeFiu1 = pNodeFiu->first_node("ox");
				if (pNodeFiu1 != NULL)
					x = 1;
				else x = 0;
				pNodeFiu1 = pNodeFiu->first_node("oy");
				if (pNodeFiu1 != NULL)
					y = 1;
				else y = 0;
				pNodeFiu1 = pNodeFiu->first_node("oz");
				if (pNodeFiu1 != NULL)
					z = 1;
				else z = 0;
				sc->followingCamera = Vector3(x, y, z);
				sc->following = true;

			}
			std::cout << pNodeFiu->value() << endl;
		}
		SceneManager::getInstance()->sceneObjects[sc->id] = sc;

	}
	xml_node<>* pCamera = pRoot->first_node("activeCamera");
	this->activeCamera = atoi(pCamera->value());
	map<int, SceneObject*>::iterator it;
	for (it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->second->Init();
	}

}
void SceneManager::Draw()
{
	map<int, SceneObject*>::iterator it;
	for (it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->second->Draw();
	}

}
void SceneManager::Update()
{
	map<int, SceneObject*>::iterator it;
	for (it = sceneObjects.begin(); it != sceneObjects.end(); it++)
	{
		it->second->Update();
	}
}
SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{
}
