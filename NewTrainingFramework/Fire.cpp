#include "stdafx.h"
#include "Fire.h"
#include <time.h>
GLvoid Fire::Draw()
{
	glUseProgram(this->shader->program);
	this->SendCommonData();
	if (this->shader->dispMax != -1)
	{
		glUniform1f(this->shader->dispMax, dispMax);
	}
	if (this->shader->u_Time != -1)
	{
		glUniform1f(this->shader->u_Time, u_Time);
	}
	glDrawElements(GL_TRIANGLES, this->model->nrIndici, GL_UNSIGNED_SHORT, 0);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid Fire::Update()
{
	u_Time =(GLfloat) clock() / 5000;
}
