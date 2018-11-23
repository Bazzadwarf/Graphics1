#pragma once
#include "Polygon3D.h"
#include "Camera.h"
#include <algorithm>

class Model
{
public:
	//Default constructor
	Model();

	//Destructor
	~Model();

	//Accessors
	std::vector<Polygon3D> &GetPolygons();
	std::vector<Vertex> &GetVertices();
	std::vector<Vertex> &GetTransformedVertices();
	int GetPolygonCount() const;
	int GetVertexCount() const;
	int GetTransformedVertexCount() const;

	//Methods
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertiecs(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void CalculatePolygonCount();
	void CalculateVerticesCount();
	void dehemoginiseVerticies();
	void CalculateBackfaces(Vertex cameraPosition);
	void Sort(void);
	void CalculateAmbientLighting(const std::vector<AmbientLight> & ambientLighting);
	void CalculateLightingDirectional(const std::vector<DirectionalLight> & directionalLighting);
	void CalculatePointLighting(std::vector<PointLight> & pointLighting);
	void CalculateVertexNormals();
	void CalculateVertexAmbientLighting(const std::vector<AmbientLight> & ambientLighting);
	void CalculateVertexLightingDirectional(const std::vector<DirectionalLight> & directionalLighting);
	void CalculateVertexPointLighting(std::vector<PointLight> & pointLighting);

private:

	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformedVertices;
	int _polygonsSize;
	int _verticesSize;

	Matrix scaleMatrix = { 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f };

	Matrix translateMatrix = { 1.0f, 0.0f, 0.0f, 1.0f,
							   0.0f, 1.0f, 0.0f, 1.0f,
							   0.0f, 0.0f, 1.0f, 1.0f,
							   0.0f, 0.0f, 0.0f, 1.0f };

	Matrix xrotateMatrix = { 1.0f,       0.0f,        0.0f, 0.0f,
							 0.0f,  cos(1.0f),  -sin(1.0f), 0.0f,
							 0.0f,  sin(1.0f),   cos(1.0f), 0.0f,
							 0.0f,       0.0f,        0.0f, 1.0f };

	Matrix yrotateMatrix = { cos(1.0f), 0.0f, sin(1.0f), 0.0f,
								  0.0f, 1.0f,	   0.0f, 0.0f,
							-sin(1.0f), 0.0f, cos(1.0f), 0.0f,
								  0.0f, 0.0f,	   0.0f, 1.0f };

	Matrix zrotateMatrix = { cos(1.0f), -sin(1.0f), 0.0f, 0.0f,
							 sin(1.0f),  cos(1.0f), 0.0f, 0.0f,
								   0.0f,		0.0f, 1.0f, 0.0f,
								   0.0f,		0.0f, 0.0f, 1.0f };

	Vector3D _normal;

	float kd_red = 1;
	float kd_green = 1;
	float kd_blue = 1;
};