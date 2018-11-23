#include "Model.h"

//Default constructor
Model::Model()
{
	
}

//Destructor
Model::~Model()
{
	if (_polygons.size() != NULL)
	{
		_polygons.clear();
	}

	if (_vertices.size() != NULL)
	{
		_vertices.clear();
	}
}

//Getter for polygons
std::vector<Polygon3D> &Model::GetPolygons()
{
	// TODO: insert return statement here
	return _polygons;
}

//Getter for vertices
std::vector<Vertex> &Model::GetVertices()
{
	// TODO: insert return statement here
	return _vertices;
}

std::vector<Vertex>& Model::GetTransformedVertices()
{
	// TODO: insert return statement here
	return _transformedVertices;
}

//Returns a value for the size of the _polygons vector
int Model::GetPolygonCount() const
{
	return (int)_polygons.size();
}

//Returns a value for the size of the _vertiecs vector
int Model::GetVertexCount() const
{
	return (int)_vertices.size();
}

int Model::GetTransformedVertexCount() const
{
	return (int)_transformedVertices.size();
}

//Add a vertex to the _vertices vector
void Model::AddVertex(float x, float y, float z)
{
	Vertex newVertex(x, y, z);
	_vertices.push_back(newVertex);
}

//Add a polygon to the _polygons vector
void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D newPolygon(i0, i1, i2);
	_polygons.push_back(newPolygon);
}

//Apply a transformation to the vertices in _vertices and add it to the _transformedVertices vector
void Model::ApplyTransformToLocalVertiecs(const Matrix &transform)
{
	_transformedVertices.clear();
	for (size_t i = 0; i < _verticesSize; i++)
	{
		_transformedVertices.push_back( transform * _vertices[i] );
	}
}

//Transform the values in _transformedVertices
void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	for (size_t i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i] = (transform * _transformedVertices[i]);
	}
}

//Calculate the size of the list of polygons
void Model::CalculatePolygonCount()
{
	_polygonsSize = (int)_polygons.size();
}

//Calculate the size of the list of vertices
void Model::CalculateVerticesCount()
{
	_verticesSize = (int)_vertices.size();
}

//Dehemoginise the vertices!
void Model::dehemoginiseVerticies()
{
	for (size_t i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i].dehemoginiseVertex();
	}
}

//Calculate which polygons are backwards facing
void Model::CalculateBackfaces(Vertex cameraPosition)
{
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		_polygons[i].DeterminBackface(cameraPosition, _transformedVertices);
	}
}

//Sort the list of polygons from furthest away to closest to the screen
void Model::Sort(void)
{
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		_polygons[i].SetAverageZ((_transformedVertices[_polygons[i].GetIndex(0)].GetZ()
								+ _transformedVertices[_polygons[i].GetIndex(1)].GetZ()
								+ _transformedVertices[_polygons[i].GetIndex(2)].GetZ()) / 3);
	}
	std::sort(_polygons.begin(), _polygons.end(), [](Polygon3D & lhs, Polygon3D & rhs) { return lhs.GetAverageZ() > rhs.GetAverageZ(); });
}

//Calculate ambient lighting for the polygons
void Model::CalculateAmbientLighting(const std::vector<AmbientLight> & ambientLighting)
{
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		_polygons[i].CalculateAmbientLighting(ambientLighting, kd_red, kd_green, kd_blue);
	}
}

//Calculate directional lighting for the polygons
void Model::CalculateLightingDirectional(const std::vector<DirectionalLight> & directionalLighting)
{
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		_polygons[i].CalculateDirectionalLighting(directionalLighting, kd_red, kd_green, kd_blue);
	}
}

//Calculate point lighting for the polygons
void Model::CalculatePointLighting(std::vector<PointLight> & pointLighting)
{
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		_polygons[i].CalculatePointLighting(_transformedVertices, pointLighting, kd_red, kd_green, kd_blue);
	}
}

//Calculate the normal vector for the list of vertices
void Model::CalculateVertexNormals()
{
	for (int i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i].SetVector(Vector3D(0, 0, 0));
		_transformedVertices[i].SetTimesContributed(0);
	}
	
	for (size_t i = 0; i < _polygonsSize; i++)
	{
		Vector3D polyNormal = _polygons[i].GetNormal();
		for (int j = 0; j < 3; j++)
		{
			_transformedVertices[_polygons[i].GetIndex(j)].AddVector(polyNormal);
			_transformedVertices[_polygons[i].GetIndex(j)].AddToTimesContributed();
		}
	}
	
	for (int i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i].NormalizeNormal();
	}
}

//Calculate the ambient lighting for the list of vertices
void Model::CalculateVertexAmbientLighting(const std::vector<AmbientLight>& ambientLighting)
{
	for (size_t i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i].CalculateAmbientLighting(ambientLighting, kd_red, kd_green, kd_blue);
	}
}

//Calculate the direction lighting for the list of vertices
void Model::CalculateVertexLightingDirectional(const std::vector<DirectionalLight>& directionalLighting)
{
	for (size_t i = 0; i < _verticesSize; i++)
	{
		_transformedVertices[i].CalculateDirectionalLighting(directionalLighting, kd_red, kd_green, kd_blue);
	}
}

//Calculate the point lighting for the list of point lights
void Model::CalculateVertexPointLighting(std::vector<PointLight>& pointLighting)
{
	//Declare variables for holding temporary values
	POLYCOLOR total;
	POLYCOLOR temp;
	Vertex lightVertex;
	Vector3D lightVector;
	float attenuation;
	float dotProduct;

	//Get the size of list of point lights
	int count = (int)pointLighting.size();

	//For each vertex in the list of vertices
	for (int i = 0; i < _verticesSize; i++)
	{
		//Reset the total color
		total.SetRGB(0, 0, 0);

		//For each light in the list of lights
		for (int j = 0; j < count; j++)
		{
			//Calculate the lights color value by multiplying by the reflection coefficients 
			temp.SetRGB((int)(pointLighting[j].GetRed() * kd_red), (int)(pointLighting[j].GetGreen() * kd_green), (int)(pointLighting[j].GetBlue() * kd_blue));

			//Create a vector to the light
			lightVertex = _transformedVertices[i] - pointLighting[j].GetPosition();
			lightVector = Vector3D(lightVertex.GetX(), lightVertex.GetY(), lightVertex.GetZ());

			//Calculate the dot product of the vector to the light and the normal vector of the vertex
			dotProduct = Vector3D::DotProduct(lightVector.getNormalisedVector(), _transformedVertices[i].GetVector());

			//Calculate the light attenuation
			attenuation = pointLighting[j].CalculateAttenuation(lightVector.GetLength());

			//Check to see if light reaches the polygon
			if (dotProduct > 0)
			{
				//Calculate color
				temp.SetR(int((temp.GetR() * dotProduct) * attenuation));
				temp.SetG(int((temp.GetG() * dotProduct) * attenuation));
				temp.SetB(int((temp.GetB() * dotProduct) * attenuation));
			}
			else
			{
				temp.SetRGB(0, 0, 0);
			}

			//Add the color to any existing colors
			total = total + temp;
		}
		//Add the color to the color stored in the vertex
		total.Clamp();
		_transformedVertices[i].AddColor(total);
	}
}
