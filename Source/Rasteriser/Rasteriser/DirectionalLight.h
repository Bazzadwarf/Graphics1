#pragma once
#include "Vector3D.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(float red, float green, float blue, Vector3D vector);

	float GetRed() const;
	void SetRed(const float red);
	float GetBlue() const;
	void SetBlue(const float blue);
	float GetGreen() const;
	void SetGreen(const float green);
	Vector3D GetVector() const;
	void SetVector(const Vector3D vector);
	DirectionalLight& operator= (const DirectionalLight& rhs);

private:
	float _red;
	float _green;
	float _blue;
	Vector3D _vector;
};