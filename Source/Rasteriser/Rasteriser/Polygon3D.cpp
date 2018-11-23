#include "Polygon3D.h"

//Default constructor
Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_cull = false;
}

//Constructor that initialises all elements.
Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_cull = false;
}

//Destructor
Polygon3D::~Polygon3D()
{
//	if (this != nullptr)
//	{
//		delete[] _indices;
//	}
}

//Getter for index
int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

//Setter for _cull
void Polygon3D::SetCulling(bool culled)
{
	_cull = culled;
}

//Getter for _cull
bool Polygon3D::GetCulling() const
{
	return _cull;
}

//Getter for _averageZ
float Polygon3D::GetAverageZ() const
{
	return _averageZ;
}

//Setter for _averageZ
void Polygon3D::SetAverageZ(float z)
{
	_averageZ = z;
}

//Getter for _normal
Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

//Setter for Color
void Polygon3D::SetColor(POLYCOLOR color)
{
	_total = color;
	_total.Clamp();
}

//Getter for a color refernce of the color stored in the polygon
COLORREF Polygon3D::GetColor() const
{
	return RGB(_total.GetR(), _total.GetG(), _total.GetB());
}

//A method for adding to color to the polygon
void Polygon3D::AddColor(POLYCOLOR color)
{
	_total = _total + color;
	_total.Clamp();
}

//A method for calculating the normal vector of the polygon
void Polygon3D::calculateNormal(const std::vector<Vertex> & vertexList)
{
	Vector3D a(vertexList[GetIndex(0)].GetX() - vertexList[GetIndex(1)].GetX(),
			   vertexList[GetIndex(0)].GetY() - vertexList[GetIndex(1)].GetY(),
			   vertexList[GetIndex(0)].GetZ() - vertexList[GetIndex(1)].GetZ());

	Vector3D b(vertexList[GetIndex(0)].GetX() - vertexList[GetIndex(2)].GetX(),
			   vertexList[GetIndex(0)].GetY() - vertexList[GetIndex(2)].GetY(),
			   vertexList[GetIndex(0)].GetZ() - vertexList[GetIndex(2)].GetZ());

	_normal = Vector3D::CrossProduct(b, a);
}

//A method for calculating the if the polygon is backfacing
void Polygon3D::DeterminBackface(const Vertex cameraPosition, const std::vector<Vertex> & vertexList)
{
	calculateNormal(vertexList);
	Vector3D eyeVector(vertexList[GetIndex(0)].GetX() - cameraPosition.GetX(),
					   vertexList[GetIndex(0)].GetY() - cameraPosition.GetY(),
					   vertexList[GetIndex(0)].GetZ() - cameraPosition.GetZ());
	_cull = Vector3D::DotProduct(_normal, eyeVector) < 0;
}

//A method for calculating ambient lighting
void Polygon3D::CalculateAmbientLighting(const std::vector<AmbientLight>& ambientLights, float kd_red, float kd_green, float kd_blue)
{
	//Declare temporary color values
	POLYCOLOR total;
	POLYCOLOR temp;

	//Get the size of the ambient light list
	int count = (int)ambientLights.size();

	//For each light in the list
	for (int i = 0; i < count; i++)
	{
		//Calculate the lights color value by multiplying by the reflection coefficients 
		temp.SetRGB((int)(ambientLights[i].GetRed() * kd_red), (int)(ambientLights[i].GetGreen() * kd_green), (int)(ambientLights[i].GetBlue() * kd_blue));
		
		//Add the color to any existing colors
		total = total + temp;
	}

	//Add the color to the color stored in the polygon
	total.Clamp();
	SetColor(total);
}

//A method for calculating directional lighting
void Polygon3D::CalculateDirectionalLighting(const std::vector<DirectionalLight>& directionalLights, float kd_red, float kd_green, float kd_blue)
{
	//Declare temporary values
	POLYCOLOR total;
	POLYCOLOR temp;
	float dotProduct;

	//Get the size of the directional light list
	int count = (int)directionalLights.size();

	//For each light in the list
	for (int i = 0; i < count; i++)
	{
		//Calculate the lights color value by multiplying by the reflection coefficients 
		temp.SetRGB((int)(directionalLights[i].GetRed() * kd_red), (int)(directionalLights[i].GetGreen() * kd_green), (int)(directionalLights[i].GetBlue() * kd_blue));

		//Calculate the dot product from the polygons normal vector to directional light vector
		dotProduct = Vector3D::DotProduct(_normal.getNormalisedVector(), directionalLights[i].GetVector().getNormalisedVector());

		//Check to see if light reaches the polygon
		if (dotProduct > 0)
		{
			//Calculate color
			temp = temp * dotProduct;
		}
		else
		{
			temp.SetRGB(0, 0, 0);
		}

		//Add the color to any existing colors
		total = total + temp;
	}

	//Add the color to the color stored in the polygon
	total.Clamp();
	AddColor(total);
}

void Polygon3D::CalculatePointLighting(const std::vector<Vertex>& vertexList, std::vector<PointLight>& pointLights, float kd_red, float kd_green, float kd_blue)
{
	//Declare temporary values
	POLYCOLOR total;
	POLYCOLOR temp;
	Vertex lightVec;
	Vector3D test;
	float attenuation;
	float dotProduct;

	//Get the size of the directional light list
	int count = (int)pointLights.size();

	//For each light in the list
	for (size_t i = 0; i < count; i++)
	{
		//Calculate the lights color value by multiplying by the reflection coefficients 
		temp.SetRGB((int)(pointLights[i].GetRed() * kd_red), (int)(pointLights[i].GetGreen() * kd_green), (int)(pointLights[i].GetBlue() * kd_blue));

		//Create a vector to the light
		lightVec = vertexList[GetIndex(0)] - pointLights[i].GetPosition();
		test = Vector3D(lightVec.GetX(), lightVec.GetY(), lightVec.GetZ());

		//Calculate the dot product of the vector to the light and the normal vector of the vertex
		dotProduct = Vector3D::DotProduct(test.getNormalisedVector(), _normal.getNormalisedVector());

		//Calculate the light attenuation
		attenuation = pointLights[i].CalculateAttenuation(test.GetLength());

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
	AddColor(total);
}

//Copy assignment operator
Polygon3D & Polygon3D::operator=(const Polygon3D & rhs)
{
	// TODO: insert return statement here
	if (this != &rhs)
	{
		for (int i = 0; i < 3; i++)
		{
			_indices[i] = rhs.GetIndex(i);
		}
		_averageZ = rhs.GetAverageZ();
		_cull = rhs.GetCulling();
		_normal = rhs.GetNormal();
		_color = rhs.GetColor();
	}
	return *this;
}
