#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	_red = 0.0f;
	_green = 0.0f;
	_blue = 0.0f;
	_vector = Vector3D();
}

DirectionalLight::DirectionalLight(float red, float green, float blue, Vector3D vector)
{
	_red = red;
	_green = green;
	_blue = blue;
	_vector = vector;
}

float DirectionalLight::GetRed() const
{
	return _red;
}

void DirectionalLight::SetRed(const float red)
{
	_red = red;
}

float DirectionalLight::GetBlue() const
{
	return _blue;
}

void DirectionalLight::SetBlue(const float blue)
{
	_blue = blue;
}

float DirectionalLight::GetGreen() const
{
	return _green;
}

void DirectionalLight::SetGreen(const float green)
{
	_green = green;
}

Vector3D DirectionalLight::GetVector() const
{
	return _vector;
}

void DirectionalLight::SetVector(const Vector3D vector)
{
	_vector = vector;
}

DirectionalLight & DirectionalLight::operator=(const DirectionalLight & rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
		_vector = rhs.GetVector();
	}
	return *this;
}
