#include "Vector3D.h"

//Default constructor
Vector3D::Vector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_length = 0.0f;
}

//Constructor
Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	CalculateLength();
}

//Copy constructor
Vector3D::Vector3D(const Vector3D & v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	CalculateLength();
}

//Destructor
Vector3D::~Vector3D()
{
}

//Getter for _x
float Vector3D::GetX() const
{
	return _x;
}

//Setter for _x
void Vector3D::SetX(float x)
{
	_x = x;
}

//Getter for _y
float Vector3D::GetY() const
{
	return _y;
}

//Setter for _y
void Vector3D::SetY(float y)
{
	_y = y;
}

//Getter for _z
float Vector3D::GetZ() const
{
	return _z;
}

//Setter for _z
void Vector3D::SetZ(float z)
{
	_z = z;
}

//Getter for _length
float Vector3D::GetLength() const
{
	return _length;
}

//Setter for _length
void Vector3D::SetLength(float l)
{
	_length = l;
}

//A method for calculating the dot product
float Vector3D::DotProduct(Vector3D v1, Vector3D v2)
{
	return ((v1.GetX() * v2.GetX()) + (v1.GetY() * v2.GetY()) + (v1.GetZ() * v2.GetZ()));
}

//A method for calculating the cross product
Vector3D Vector3D::CrossProduct(Vector3D v1, Vector3D v2)
{
	return Vector3D((v1.GetY() * v2.GetZ()) - (v1.GetZ() * v2.GetY()),
					(v1.GetZ() * v2.GetX()) - (v1.GetX() * v2.GetZ()),
					(v1.GetX() * v2.GetY()) - (v1.GetY() * v2.GetX()));
}

//A method for calculating the length of the vector
void Vector3D::CalculateLength()
{
	_length = sqrtf((_x * _x) + (_y * _y) + (_z * _z));
}

//A method for normalising a vector
void Vector3D::Normalise()
{
	CalculateLength();
	_x = _x / _length;
	_y = _y / _length;
	_z = _z / _length;
}

//A method for getting a normalised vector
Vector3D Vector3D::getNormalisedVector()
{
	CalculateLength();
	return Vector3D((_x / _length), (_y / _length), (_z / _length));
}

//An operator override for setting the calue of a vertex to that of another vertex
Vector3D & Vector3D::operator=(const Vector3D & rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_length = rhs.GetLength();
	}
	return *this;
}

//An operator override to check if two vectors are the same
bool Vector3D::operator==(const Vector3D & rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ());
}

//An operator override to add two vectors together
const Vector3D Vector3D::operator+(const Vector3D & rhs) const
{
	return Vector3D(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

//An operator override to subtract two vectors from each other
const Vector3D Vector3D::operator-(const Vector3D & rhs) const
{
	return Vector3D(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}

//An operator override to dive a vector by a float
const Vector3D Vector3D::operator/(const float & rhs) const
{
	return Vector3D((_x / rhs), (_y / rhs), (_z / rhs));
}
