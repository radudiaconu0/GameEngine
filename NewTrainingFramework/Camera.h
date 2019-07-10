#pragma once
#include "../Utilities/Math.h"

class Camera
{

public:
	Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat movespeed, GLfloat rotateSpeed, GLfloat near1, GLfloat far1, GLfloat fov);
	
	Vector3 position, target, up;
    GLfloat moveSpeed, rotateSpeed, near1, far1, fov, deltaTime = 0;
	Vector3 xAxis, yAxis, zAxis;
	Matrix viewMatrix, worldMatrix, perspMatrix;
	void moveOx(int directie);
	void moveOy(int directie);
	void moveOz(int directie);
	void rotateOx(int directie);
	void rotateOy(int directie);
	void rotateOz(int directie);
	void updateWorldView();

};