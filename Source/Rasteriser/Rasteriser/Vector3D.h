#pragma once
#include <math.h>

class Vector3D
{
public:
	//Default constructor
	Vector3D();

	//Constructor that initialises the elements to the values passed in.
	Vector3D(float x, float y, float z);

	//Copy constructor
	Vector3D(const Vector3D& v);

	//Destructor
	~Vector3D();

	//Accessors
	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);
	float GetZ() const;
	void SetZ(float z);
	float GetLength() const;
	void SetLength(float l);

	//Methods
	static float DotProduct(Vector3D v1, Vector3D v2);
	static Vector3D CrossProduct(Vector3D v1, Vector3D v2);
	void CalculateLength();
	void Normalise();
	Vector3D getNormalisedVector();

	//Operators
	Vector3D& operator= (const Vector3D& rhs);
	bool operator== (const Vector3D& rhs) const;
	const Vector3D operator+ (const Vector3D& rhs) const;
	const Vector3D operator- (const Vector3D& rhs) const;
	const Vector3D operator/ (const float& rhs) const;

private:
	float _x;
	float _y;
	float _z;
	float _length;
};