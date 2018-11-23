#include "Vertex.h"
//Default constructor (Initialises values to 0)
Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
	_vertNormal = Vector3D();
	_verColor = POLYCOLOR();
	_timesContributed = 0;
}

Vertex::Vertex(float x, float y)
{
	_x = x;
	_y = y;
	_z = 1.0f;
	_w = 1.0f;
	_vertNormal = Vector3D();
	_verColor = POLYCOLOR();
	_timesContributed = 0;
}

// Constructor that initialises the elements to the values passed in (Exculding W )
Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1.0f;
	_vertNormal = Vector3D();
	_verColor = POLYCOLOR();
	_timesContributed = 0;
}

//Constructor that initialises the elements to the values passed in (Including W )
Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
	_vertNormal = Vector3D();
	_verColor = POLYCOLOR();
	_timesContributed = 0;
}

// Copy constructor implementation
// Note that the parameter v is passed by reference, rather than value (that is what
// '&' indicates).  Note also the use of 'const' to indicate that the parameter v cannot
// be changed.

Vertex::Vertex(const Vertex& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
	_vertNormal = v.GetVector();
	_verColor = v.GetColor();
	_timesContributed = v.GetTimesContributed();
}

// Destructor does not need to do anything
Vertex::~Vertex()
{
}

//Getter for _x
float Vertex::GetX() const
{
	return _x;
}

//Setter for _x
void Vertex::SetX(const float x)
{
	_x = x;
}

//Getter for _y
float Vertex::GetY() const
{
	return _y;
}

//Setter for _y
void Vertex::SetY(const float y)
{
	_y = y;
}

//Getter for _z
float Vertex::GetZ() const
{
	return _z;
}

//Setter for _z
void Vertex::SetZ(const float z)
{
	_z = z;
}

//Getter for _w
float Vertex::GetW() const
{
	return _w;
}

//Setter for _w
void Vertex::SetW(const float w)
{
	_w = w;
}

//Getter for _vertNormal
Vector3D Vertex::GetVector() const
{
	return _vertNormal;
}

//Setter for _vertNormal
void Vertex::SetVector(Vector3D v)
{
	_vertNormal = v;
}

//A method to add a vector to a vertex
void Vertex::AddVector(Vector3D v)
{
	_vertNormal = _vertNormal + v;
}

//A method to calculate the normal of the vector in the vertex
void Vertex::NormalizeNormal()
{
	_vertNormal = _vertNormal / (float)_timesContributed;
	_vertNormal.Normalise();
}

//Getter for _vertColor
POLYCOLOR Vertex::GetColor() const
{
	return _verColor;
}

//Setter for _vertColor
void Vertex::SetColor(POLYCOLOR c)
{
	_verColor = c;
}

//A method to add color to the vertex
void Vertex::AddColor(POLYCOLOR c)
{
	_verColor = _verColor + c;
	_verColor.Clamp();
}

//Getter for _timesContributed
int Vertex::GetTimesContributed() const
{
	return _timesContributed;
}

//Setter for _timesContributed
void Vertex::SetTimesContributed(int i)
{
	_timesContributed = i;
}

//A method to increment _timesContributed
void Vertex::AddToTimesContributed()
{
	_timesContributed = _timesContributed + 1;
}

//A method for dehemoginising a inputted vertex
void Vertex::dehemoginiseVertex()
{
	_x = (_x / _w); //Dehemoginise the x value
	_y = (_y / _w); //Dehemoginise the y value
	_z = (_z / _w); //Dehemoginise the z value
	_w = (_w / _w); //Dehemoginise the w value (Should be 1)
}

//A method for calculating ambient lighting
void Vertex::CalculateAmbientLighting(const std::vector<AmbientLight>& ambientLights, float kd_red, float kd_green, float kd_blue)
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
void Vertex::CalculateDirectionalLighting(const std::vector<DirectionalLight>& directionalLights, float kd_red, float kd_green, float kd_blue)
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
		dotProduct = Vector3D::DotProduct(_vertNormal, directionalLights[i].GetVector().getNormalisedVector());

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

//A operator override for setting the value of a vertex to that of another vertex
Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
		_vertNormal = rhs.GetVector();
		_verColor = rhs.GetColor();
		_timesContributed = rhs.GetTimesContributed();
	}
	return *this;
}

//A opperator override for checking that two vertexes are the same
bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

//A operator override for adding two vertices together
const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ(), _w + rhs.GetW());
}

//An operator override to subtract two vertices from each other
const Vertex Vertex::operator-(const Vertex & rhs) const
{
	return Vertex(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}
