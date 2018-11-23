#include "POLYCOLOR.h"

POLYCOLOR::POLYCOLOR()
{
	_r = 0;
	_b = 0;
	_g = 0;
}

POLYCOLOR::POLYCOLOR(int r, int g, int b)
{
	_r = r;
	_g = g;
	_b = b;
}

POLYCOLOR::POLYCOLOR(const POLYCOLOR & polycolor)
{
	_r = polycolor.GetR();
	_b = polycolor.GetB();
	_g = polycolor.GetG();
}

int POLYCOLOR::GetR() const
{
	return _r;
}

void POLYCOLOR::SetR(const int r)
{
	_r = r;
}

int POLYCOLOR::GetG() const
{
	return _g;
}

void POLYCOLOR::SetG(const int g)
{
	_g = g;
}

int POLYCOLOR::GetB() const
{
	return _b;
}

void POLYCOLOR::SetB(const int b)
{
	_b = b;
}

POLYCOLOR & POLYCOLOR::operator=(const POLYCOLOR & rhs)
{
	if (this != &rhs)
	{
		_r = rhs.GetR();
		_g = rhs.GetG();
		_b = rhs.GetB();
	}
	return *this;
}

const POLYCOLOR POLYCOLOR::operator+(const POLYCOLOR & rhs) const
{
	return POLYCOLOR(_r + rhs.GetR(), _g + rhs.GetG(), _b + rhs.GetB());
}

const POLYCOLOR POLYCOLOR::operator*(const float & rhs) const
{
	return POLYCOLOR((int)(_r * rhs), (int)(_g * rhs), (int)(_b * rhs));
}

void POLYCOLOR::SetRGB(const int red, const int green, const int blue)
{
	_r = red;
	_g = green;
	_b = blue;
}

void POLYCOLOR::Clamp()
{
	if (_r < 0) 
	{
		_r = 0;
	}

	if (_r > 255)
	{
		_r = 255;
	}

	if (_g < 0)
	{
		_g = 0;
	}

	if (_g > 255)
	{
		_g = 255;
	}

	if (_g < 0)
	{
		_g = 0;
	}

	if (_b > 255)
	{
		_b = 255;
	}

	if (_b < 0)
	{
		_b = 0;
	}
}
