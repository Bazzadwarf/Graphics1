#include "Matrix.h"

//Default constructor
Matrix::Matrix()
{
	// Create matrix
	float matrixData[ROWS][COLS];

	// Assign 0.0f to all indexes in the array
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			matrixData[i][j] = 0.0f;
		}
	}
}

//Constructor that initialises all elements.
//The initializer_list is used to pass in values. This is new to c++ so google.
Matrix::Matrix(std::initializer_list<float> list)
{
	// Check to see if the list inputted is the same size as the required matrix 
	if (list.size() != ROWS * COLS)
	{
		throw "Something borked";
	}

	//Get the inputted list
	auto listInput = list.begin();

	//Set the matrix to the contense of the list
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_matrixValue[i][j] = *listInput;
			listInput = listInput++;
		}
	}
}


//A copy constructor
Matrix::Matrix(const Matrix& other)
{
	//Copy values from a matrix (other) to new matrix (matrixData)
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_matrixValue[i][j] = other.GetM(i, j);
		}
	}


}
//Destructor
Matrix::~Matrix()
{
	//Check to see if the pointer to the value in the matrix is null and if it isn't delete it
	if (this != NULL)
	{
		//delete this;
	}
}

//Getter for M
float Matrix::GetM(const int row, const int column) const
{
	//Get the value from the specified index and return it
	return  _matrixValue[row][column];
}

//Setter for M
void Matrix::SetM(const int row, const int column, const float value)
{
	//Set the input value as the value stored in the matrix specified by the index
	_matrixValue[row][column] = value;
}

//Copy assignment operator
Matrix & Matrix::operator=(const Matrix &rhs)
{
	if (this != &rhs)
	{
		//Copy values from a matrix (other) to new matrix (matrixData)
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				_matrixValue[i][j] = rhs.GetM(i, j);
			}
		}
	}
	return *this;
}

//Multiply two matrices together
const Matrix Matrix::operator*(const Matrix & other) const
{
	//Create a empty matrix
	Matrix result;

	//Loops for keeping track of place in the matrix
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//Multiply matrixs together then set the result in the matrix
			result.SetM(i, j, (GetM(i,0) * other.GetM(0,j)) + (GetM(i, 1) * other.GetM(1, j)) + (GetM(i, 2) * other.GetM(2, j)) + (GetM(i, 3) * other.GetM(3, j)));
		}
	}
	
	//Return the result
	return result;
}

//Multiply a matrix by a vertex, returning a vertex
const Vertex Matrix::operator*(const Vertex & other) const
{
	//Create a vertex to store our result
	Vertex result;
	
	//CALCULATE
	result.SetX((GetM(0, 0) * other.GetX()) + (GetM(0, 1) * other.GetY()) + (GetM(0, 2) * other.GetZ()) + (GetM(0, 3) * other.GetW()));
	result.SetY((GetM(1, 0) * other.GetX()) + (GetM(1, 1) * other.GetY()) + (GetM(1, 2) * other.GetZ()) + (GetM(1, 3) * other.GetW()));
	result.SetZ((GetM(2, 0) * other.GetX()) + (GetM(2, 1) * other.GetY()) + (GetM(2, 2) * other.GetZ()) + (GetM(2, 3) * other.GetW()));
	result.SetW((GetM(3, 0) * other.GetX()) + (GetM(3, 1) * other.GetY()) + (GetM(3, 2) * other.GetZ()) + (GetM(3, 3) * other.GetW()));
	result.SetColor(other.GetColor());
	result.SetVector(other.GetVector());
	//Return the vertex result
	return result;
}


