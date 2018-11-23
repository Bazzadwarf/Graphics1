#include "FPoint.h"

//Default constructor
FPoint::FPoint()
{
	_x = 0.0f;
	_y = 0.0f;
}

//Constuctor
FPoint::FPoint(float x, float y)
{
	_x = x;
	_y = y;
}

//Copy constructor
FPoint::FPoint(const FPoint & p)
{
	_x = p._x;
	_y = p._y;
}

//Getter for _x
float FPoint::GetX() const
{
	return _x;
}

//Setter for _x
void FPoint::SetX(float x)
{
	_x = x;
}

//Getter for _y
float FPoint::GetY() const
{
	return _y;
}

//Setter for _y
void FPoint::SetY(float y)
{
	_y = y;
}
