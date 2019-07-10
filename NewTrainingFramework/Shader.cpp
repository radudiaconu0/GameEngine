#include "stdafx.h"
#include "Shader.h"

void Shader::Load()
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, sr->vs);
	int error = 0;
	if (vertexShader == 0)
		error = -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, sr->fs);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		error = -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	uniformrotation = glGetUniformLocation(program, "u_rot");
	uniformtexture[0] = glGetUniformLocation(program, "u_texture0");
	uniformtexture[1] = glGetUniformLocation(program, "u_texture1");
	uniformtexture[2] = glGetUniformLocation(program, "u_texture2");
	uniformtexture[3] = glGetUniformLocation(program, "u_texture3");
	uniformtexture[4] = glGetUniformLocation(program, "u_texture4");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	uvAttribute2 = glGetAttribLocation(program, "a_uv2");
	heightUniform = glGetUniformLocation(program, "height");
	bigRadius = glGetUniformLocation(program, "big_radius");
	littleRadius = glGetUniformLocation(program, "little_radius");
	fogColor = glGetUniformLocation(program, "f_color");
	camPos = glGetUniformLocation(program, "cam_pos");
	model = glGetUniformLocation(program, "model");
	dispMax = glGetUniformLocation(program, "u_DispMax");
	u_Time = glGetUniformLocation(program, "u_Time");
	specColor[0] = glGetUniformLocation(program, "specColor0");
	specColor[1] = glGetUniformLocation(program, "specColor1");
	specColor[2] = glGetUniformLocation(program, "specColor2");
	specColor[3] = glGetUniformLocation(program, "specColor3");
	specColor[4] = glGetUniformLocation(program, "specColor4");
	direction[0] = glGetUniformLocation(program, "direction0");
	direction[1] = glGetUniformLocation(program, "direction1");
	direction[2] = glGetUniformLocation(program, "direction2");
	direction[3] = glGetUniformLocation(program, "direction3");
	direction[4] = glGetUniformLocation(program, "direction4");
	specPower[0] = glGetUniformLocation(program, "specPower0");
	specPower[1] = glGetUniformLocation(program, "specPower1");
	specPower[2] = glGetUniformLocation(program, "specPower2");
	specPower[3] = glGetUniformLocation(program, "specPower3");
	specPower[4] = glGetUniformLocation(program, "specPower4");
	diffuseColor[0] = glGetUniformLocation(program, "diffuseColor0");
	diffuseColor[1] = glGetUniformLocation(program, "diffuseColor1");
	diffuseColor[2] = glGetUniformLocation(program, "diffuseColor2");
	diffuseColor[3] = glGetUniformLocation(program, "diffuseColor3");
	diffuseColor[4] = glGetUniformLocation(program, "diffuseColor4");
	ambientalLight = glGetUniformLocation(program, "c_amb");
	normalAttribute = glGetAttribLocation(program, "a_norm");

}

Shader::Shader(ShaderResource *sr)
{
	this->sr = sr;
}


Shader::~Shader()
{
}
