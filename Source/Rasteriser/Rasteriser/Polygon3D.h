#pragma once
#include "PointLight.h"
#include "Windows.h"

class Polygon3D
{
public:

	//Default constructor
	Polygon3D();

	//Constructor
	Polygon3D(int index0, int index1, int index2);

	//Destructor
	~Polygon3D();

	//Accessors
	int GetIndex(int index) const;
	void SetCulling(bool culled);
	bool GetCulling() const;
	float GetAverageZ() const;
	void SetAverageZ(float z);
	Vector3D GetNormal() const;
	void SetColor(POLYCOLOR color);
	COLORREF GetColor() const;
	void AddColor(POLYCOLOR color);
	void calculateNormal(const std::vector<Vertex> & vertexList);
	void DeterminBackface(const Vertex cameraPosition, const std::vector<Vertex> & vertexList);
	void CalculateAmbientLighting(const std::vector<AmbientLight>& ambientLights, float kd_red, float kd_green, float kd_blue);
	void CalculateDirectionalLighting(const std::vector<DirectionalLight>& directionalLights, float kd_red,	float kd_green,	float kd_blue);
	void CalculatePointLighting(const std::vector<Vertex>& vertexList, std::vector<PointLight>& pointLights, float kd_red, float kd_green, float kd_blue);

	//Copy assignment operator
	Polygon3D& operator= (const Polygon3D &rhs);

private:
	int _indices[3];
	float _averageZ;
	bool _cull;
	Vector3D _normal;
	COLORREF _color;
	POLYCOLOR _total;
	POLYCOLOR _temp;
};