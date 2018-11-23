#include "Camera.h"

//Default constructor
Camera::Camera()
{
	_xRotation = 0.0f;
	_yRotation = 0.0f;
	_zRotation = 0.0f;
}

//Constructor
Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex & position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;

	SetXMatrix(_xRotation);
	SetYMatrix(_yRotation);
	SetZMatrix(_zRotation);
	SetPositionMatrix(_position);
	
	UpdateCameraMatrix();
}

//Destructor
Camera::~Camera()
{
	//delete &_xRotation;
	//delete &_yRotation;
	//delete &_zRotation;
	//delete &_position;
}

//Getter for _xRotation
float Camera::GetX() const
{
	return _xRotation;
}

//Setter for  _xRotation
void Camera::SetX(const float x)
{
	_xRotation = x;
}

//Getter for _yRotation
float Camera::GetY() const
{
	return _yRotation;
}

//Setter for _yRotation
void Camera::SetY(const float y)
{
	_yRotation = y;
}

//Getter for _zRotation
float Camera::GetZ() const
{
	return _zRotation;
}

//Setter for _zRotation
void Camera::SetZ(const float z)
{
	_zRotation = z;
}

//Getter for _position
Vertex Camera::GetPosition() const
{
	return _position;
}

//Setter for _position
void Camera::SetPosition(const float x, const float y, const float z)
{
	_position.SetX(x);
	_position.SetY(y);
	_position.SetZ(z);
}

//Getter for _xMatrix
Matrix Camera::GetXMatrix()
{
	return _xMatrix;
}

//Setter for _xMatrix
void Camera::SetXMatrix(const float x)
{
	_xMatrix = { 1,		  0,	  0, 0,
				 0,  cos(x), sin(x), 0,
				 0, -sin(x), cos(x), 0,
				 0,		  0,	  0, 1 };
}

//Getter for _yMatrix
Matrix Camera::GetYMatrix()
{
	return _yMatrix;
}

//Setter for _yMatrix
void Camera::SetYMatrix(const float y)
{
	_yMatrix = { cos(y), 0, -sin(y), 0,
					  0, 1,		  0, 0,
				 sin(y), 0,  cos(y), 0,
					  0, 0,		  0, 1 };
}

//Getter for _zMatrix
Matrix Camera::GetZMatrix()
{
	return _zMatrix;
}

//Setter for _zMatrix
void Camera::SetZMatrix(const float z)
{
	_zMatrix = { cos(z), sin(z), 0, 0,
				-sin(z), cos(z), 0, 0,
					  0,	  0, 1, 0,
					  0,	  0, 0, 1 };
}

//Getter for _positionMatrix
Matrix Camera::GetPositionMatrix()
{
	return _PositionMatrix;
}

//Setter for _PositionMatrix
void Camera::SetPositionMatrix(const Vertex vertex)
{
	_PositionMatrix = { 1, 0, 0, -vertex.GetX(),
						0, 1, 0, -vertex.GetY(),
						0, 0, 1, -vertex.GetZ(),
						0, 0, 0,			   1 };
}

//Getter for _cameraMatrix
Matrix Camera::GetCameraMatrix()
{
	return _cameraMatrix;
}

//Setter for _cameraMatrix
void Camera::UpdateCameraMatrix()
{
	_cameraMatrix = _xMatrix * _yMatrix * _zMatrix * _PositionMatrix;
}
