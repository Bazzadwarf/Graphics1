#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_red = 0.0f;
	_blue = 0.0f;
	_green = 0.0f;
}

AmbientLight::AmbientLight(float red, float green, float blue)
{
	_red = red;
	_green = green;
	_blue = blue;
}

float AmbientLight::GetRed() const
{
	return _red;
}

void AmbientLight::SetRed(const float red)
{
	_red = red;
}

float AmbientLight::GetBlue() const
{
	return _blue;
}

void AmbientLight::SetBlue(const float blue)
{
	_blue = blue;
}

float AmbientLight::GetGreen() const
{
	return _green;
}

void AmbientLight::SetGreen(const float green)
{
	_green = green;
}

AmbientLight & AmbientLight::operator=(const AmbientLight & rhs)
{
	if (this != &rhs)
	{
		_red = rhs.GetRed();
		_green = rhs.GetGreen();
		_blue = rhs.GetBlue();
	}
	return *this;
}
