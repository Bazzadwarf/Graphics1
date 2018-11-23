#pragma once
class FPoint
{
public:
	//Constructors
	FPoint();
	FPoint(float x, float y);
	FPoint(const FPoint& p);

	//Accessors
	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);

private:
	float _x;
	float _y;
};
