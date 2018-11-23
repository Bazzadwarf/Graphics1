#pragma once
#include "Vertex.h"
#include <initializer_list>

const int ROWS = 4;
const int COLS = 4;

class Matrix
{
	public:
		//Default constructor
		Matrix();

		//Constructor that initialises all elements.
		//The initializer_list is used to pass in values. This is new to c++ so google.
		Matrix(std::initializer_list<float> list);

		//Copy constructor
		Matrix(const Matrix& other);

		//Destructor
		~Matrix();

		//Get and Set
		float GetM(const int row, const int column) const;
		void SetM(const int row, const int column, const float value);

		//Copy assignment operator
		Matrix& operator= (const Matrix &rhs);

		//Multiply two matrices together
		const Matrix operator*(const Matrix &other) const;

		//Multiply a matrix by a vertex, returning a vertex
		const Vertex operator*(const Vertex &other)const;

private:
	float _matrixValue[ROWS][COLS];
};
