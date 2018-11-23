#pragma once
#include "Vertex.h"

class PointLight
{
public:
	PointLight();
	PointLight(float red, float green, float blue, float a, float b, float c, Vertex position);

	float GetRed() const;
	void SetRed(const float red);
	float GetBlue() const;
	void SetBlue(const float blue);
	float GetGreen() const;
	void SetGreen(const float green);
	float GetA() const;
	void SetA(const float a);
	float GetB() const;
	void SetB(const float b);
	float GetC() const;
	void GetC(const float c);
	Vertex GetPosition() const;
	void SetPosition(Vertex vertex);

	float CalculateAttenuation(float distance);

	PointLight& operator= (const PointLight& rhs);

private:
	float _red;
	float _green;
	float _blue;

	float _ac_a;
	float _ac_b;
	float _ac_c;

	Vertex _position;
};
