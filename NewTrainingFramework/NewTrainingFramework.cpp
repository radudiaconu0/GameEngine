// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include "ResourceManager.h"
#include "Texture.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "SceneManager.h"
#include <mmsystem.h>

float unghi = 0, pos = 0.01;
GLfloat frames;
Matrix mat;
GLuint vboId;
Vertex verticesData[6];
GLfloat counter = 0;
GLfloat limita = 0.05f;
GLfloat limit = 0.05f;
int nbframes = 0;
POINT cursor = { 1000, 500 };
//GLushort* indices;
Vertex* w;
//Texture texture;

int Init(ESContext* esContext)
{
	int err = glGetError();
	ResourceManager::getInstance()->Init();
	SceneManager::getInstance()->Init();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;

}

void Draw(ESContext* esContext)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneManager::getInstance()->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{

	nbframes++;
	frames += deltaTime;
	if (frames >= limit)
	{
		// cout << nbframes / frames << " ";
	}

	counter += deltaTime;
	if (counter >= limita)
	{
		counter -= limita;
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		{
			POINT pct;
			
			GetCursorPos(&pct);
			ScreenToClient(esContext->hWnd, &pct);
			//cout << pct.x << " " << pct.y << endl;

			if (pct.y >= 0 && pct.y <= Globals::screenHeight) {
				if (pct.x >= 0 && pct.x <= Globals::screenWidth / 2) {
					std::cout << "click la stanga";
				}
				else if (pct.x >= Globals::screenWidth / 2 && pct.x <= Globals::screenWidth) {
					std::cout << "click la dreapta";
				}
			}
		}

	}
	unghi += pos;
	mat.SetRotationZ(unghi);
	SceneManager::getInstance()->getActiveCamera()->deltaTime = deltaTime;
	SceneManager::getInstance()->Update();

}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		
		switch (key)
		{
		case 'W': SceneManager::getInstance()->getActiveCamera()->moveOy(-1); break;
		case 'S': SceneManager::getInstance()->getActiveCamera()->moveOy(1); break;
		case 'A': SceneManager::getInstance()->getActiveCamera()->moveOx(1); break;
		case 'D': SceneManager::getInstance()->getActiveCamera()->moveOx(-1); break;
		case 'Z':  SceneManager::getInstance()->getActiveCamera()->moveOz(1); break;
		case 'X':  SceneManager::getInstance()->getActiveCamera()->moveOz(-1); break;
		case 'Q':  SceneManager::getInstance()->getActiveCamera()->rotateOz(-1); break;
		case 'E':  SceneManager::getInstance()->getActiveCamera()->rotateOz(1); break;
		case VK_RIGHT:  SceneManager::getInstance()->getActiveCamera()->rotateOy(1); break;
		case VK_LEFT:  SceneManager::getInstance()->getActiveCamera()->rotateOy(-1); break;
		case VK_UP:  SceneManager::getInstance()->getActiveCamera()->rotateOx(-1); break;
		case VK_DOWN:  SceneManager::getInstance()->getActiveCamera()->rotateOx(1); break;

		default:
			break;
		}

	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//

	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;

	esInitContext(&esContext);
	esCreateWindow(&esContext, "The fucking game", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;
	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();


	return 0;
}

