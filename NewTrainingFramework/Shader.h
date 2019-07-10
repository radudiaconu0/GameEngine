#pragma once
#include <string>
#include "ShaderResource.h"
#include "../../Utilities/utilities.h"
#include <string>
class Shader
{
public:
	int id;
	GLuint program, vertexShader, fragmentShader;
	std::string fileVS;
	std::string fileFS;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uniformrotation;
	GLint uniformtexture[5];
	GLint specPower[5];
	GLint direction[5];
	GLint specColor[5];
	GLint diffuseColor[5];
	GLint ambientalLight;
	GLint uvAttribute;
	GLint uvAttribute2;
	GLint heightUniform;
	GLint bigRadius;
	GLint littleRadius;
	GLint fogColor;
	GLint camPos;
	GLint model;
	GLint u_Time;
	GLint dispMax;
	GLint v_norm;
	GLint ratio;
	GLint normalAttribute;
	Shader(ShaderResource *sr);
	ShaderResource* sr;
	Shader();
	~Shader();
	void Load();
};

