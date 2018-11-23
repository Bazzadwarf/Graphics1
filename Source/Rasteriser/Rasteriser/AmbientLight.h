#pragma once
#include "POLYCOLOR.h"

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(float red, float green, float blue);

	float GetRed() const;
	void SetRed(const float red);
	float GetBlue() const;
	void SetBlue(const float blue);
	float GetGreen() const;
	void SetGreen(const float green);
	
	AmbientLight& operator= (const AmbientLight& rhs);

private:
	float _red;
	float _green;
	float _blue;
};