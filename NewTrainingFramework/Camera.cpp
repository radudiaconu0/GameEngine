#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include "Shaders.h"
#include <Math.h>


Camera::Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat movespeed, GLfloat rotateSpeed, GLfloat near1, GLfloat far1, GLfloat fov)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->rotateSpeed = rotateSpeed;
	this->moveSpeed = movespeed;
	this->near1 = near1;
	this->far1 = far1;
	this->fov = fov;
	this->deltaTime = deltaTime;
	this->zAxis = -(target - position).Normalize();
	this->yAxis = up.Normalize(); 
	this->xAxis = zAxis.Cross(yAxis).Normalize();
	perspMatrix.SetPerspective(fov, (float)Globals::screenWidth / Globals::screenHeight, near1, far1);
	updateWorldView();
}



void Camera::moveOy(int directie) 
{
	Vector3 forward = up.Normalize() * directie;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOx(int directie) 
{
	this->zAxis = -(target - position).Normalize();
	this->yAxis = up.Normalize();
	this->xAxis = zAxis.Cross(yAxis).Normalize();
	Vector3 forward = zAxis.Cross(yAxis).Normalize() * directie;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOz(int directie)
{
	Vector3 forward = -(target - position).Normalize() * directie;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOy(int directie)
{
	Matrix mRotateOY;
	mRotateOY.SetRotationY(deltaTime*rotateSpeed*directie);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}


void Camera::rotateOx(int directie)
{
	Matrix mRotateOX;
	mRotateOX.SetRotationX(deltaTime*rotateSpeed*directie);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}


void Camera::rotateOz(int directie)
{
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(deltaTime*rotateSpeed*directie);
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 rotatedUp = localUp * mRotateOZ;
	up = (rotatedUp * worldMatrix).toVector3();
	up.Normalize();
	updateWorldView();
}

void Camera::updateWorldView()
{
	Matrix T, R;
	T.SetTranslation(position);
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
	R.m[0][0] = xAxis.x;
	R.m[1][0] = yAxis.x;
	R.m[2][0] = zAxis.x;
	R.m[3][0] = 0;
	R.m[0][1] = xAxis.y;
	R.m[1][1] = yAxis.y;
	R.m[2][1] = zAxis.y;
	R.m[3][1] = 0;
	R.m[0][2] = xAxis.z;
	R.m[1][2] = yAxis.z;
	R.m[2][2] = zAxis.z;
	R.m[3][2] = 0;
	R.m[0][3] = 0;
	R.m[1][3] = 0;
	R.m[2][3] = 0;
	R.m[3][3] = 1;
	worldMatrix = R * T;
	T.SetTranslation(-position);
	viewMatrix = T * R.Transpose();
}