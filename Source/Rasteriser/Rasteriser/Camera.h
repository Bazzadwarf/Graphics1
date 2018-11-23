#pragma once
#include "Matrix.h"

class Camera
{
public:
	//Default constructor
	Camera();

	//Constructor that initialises all elements.
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);

	//Destructor
	~Camera();

	//Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	Vertex GetPosition() const;
	void SetPosition(const float x, const float y, const float z);
	Matrix GetXMatrix();
	void SetXMatrix(const float x);
	Matrix GetYMatrix();
	void SetYMatrix(const float y);
	Matrix GetZMatrix();
	void SetZMatrix(const float z);
	Matrix GetPositionMatrix();
	void SetPositionMatrix(const Vertex vertex);
	Matrix GetCameraMatrix();
	void UpdateCameraMatrix();

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;

	Matrix _xMatrix;
	Matrix _yMatrix;
	Matrix _zMatrix;
	Matrix _PositionMatrix;
	Matrix _cameraMatrix;
};