#pragma once

class POLYCOLOR
{
public:
	POLYCOLOR();
	POLYCOLOR(int r, int g, int b);

	POLYCOLOR(const POLYCOLOR& polycolor);

	int GetR() const;
	void SetR(const int r);
	int GetG() const;
	void SetG(const int g);
	int GetB() const;
	void SetB(const int b);
	void SetRGB(const int red, const int green, const int blue);
	void Clamp();
	
	POLYCOLOR& operator= (const POLYCOLOR& rhs);

	const POLYCOLOR POLYCOLOR::operator+(const POLYCOLOR& rhs) const;
	const POLYCOLOR POLYCOLOR::operator*(const float& rhs) const;
	
private:
	int _r;
	int _g;
	int _b;
};