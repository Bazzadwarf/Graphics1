#pragma once
#include <vector>
#include "DirectionalLight.h"
#include "AmbientLight.h"

class Vertex
{
public:
	//Constructors
	Vertex();
	Vertex(float x, float y);
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w);

	// Copy constructor.  
	Vertex(const Vertex& v);

	// Destructer
	~Vertex();

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float w);
	Vector3D GetVector() const;
	void SetVector(Vector3D v);
	void AddVector(Vector3D v);
	void NormalizeNormal();
	POLYCOLOR GetColor() const;
	void SetColor(POLYCOLOR c);
	void AddColor(POLYCOLOR c);
	int GetTimesContributed() const;
	void SetTimesContributed(int i);
	void AddToTimesContributed();

	//Methods
	void dehemoginiseVertex();
	void CalculateAmbientLighting(const std::vector<AmbientLight>& ambientLights, float kd_red, float kd_green, float kd_blue);
	void CalculateDirectionalLighting(const std::vector<DirectionalLight>& directionalLights, float kd_red, float kd_green, float kd_blue);

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	const Vertex operator- (const Vertex& rhs) const;

private:
	float _x;
	float _y;
	float _z;
	float _w;
	
	Vector3D _vertNormal;
	POLYCOLOR _verColor;
	int _timesContributed;
};
