#include "PointLight.h"

PointLight::PointLight()
{
	_red = 0.0f;
	_green = 0.0f;
	_blue = 0.0f;
	_ac_a = 0.0f;
	_ac_b = 0.0f;
	_ac_c = 0.0f;
	_position = Vertex();
}

PointLight::PointLight(float red, float green, float blue, float a, float b, float c, Vertex position)
{
	_red = red;
	_green = green;
	_blue = blue;
	_ac_a = a;
	_ac_b = b;
	_ac_c = c;
	_position = position;
}

float PointLight::GetRed() const
{
	return _red;
}

void PointLight::SetRed(const float red)
{
	_red = red;
}

float PointLight::GetBlue() const
{
	return _blue;
}

void PointLight::SetBlue(const float blue)
{
	_blue = blue;
}

float PointLight::GetGreen() const
{
	return _green;
}

void PointLight::SetGreen(const float green)
{
	_green = green;
}

float PointLight::GetA() const
{
	return _ac_a;
}

void PointLight::SetA(const float a)
{
	_ac_a = a;
}

float PointLight::GetB() const
{
	return _ac_b;
}

void PointLight::SetB(const float b)
{
	_ac_b = b;
}

float PointLight::GetC() const
{
	return _ac_c;
}

void PointLight::GetC(const float c)
{
	_ac_c = c;
}

Vertex PointLight::GetPosition() const
{
	return _position;
}

void PointLight::SetPosition(Vertex vertex)
{
	_position = vertex;
}

float PointLight::CalculateAttenuation(float distance)
{
	return (1.0f / (_ac_a + (_ac_b * distance) + (_ac_c * (distance * distance))));
}

PointLight & PointLight::operator=(const PointLight & rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
	}
	return *this;
}
