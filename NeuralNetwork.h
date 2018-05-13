

//#include "Matrix.h"
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <stdlib.h>
#include <math.h>

using namespace std;

class Matrix
{

	public:
		Matrix();
		Matrix(int,int);
		Matrix(int,int, float *);
		Matrix(Matrix &);
		Matrix(const Matrix &);
		~Matrix();
		float & operator()(int, int) const;
		Matrix & operator=(Matrix &);
		Matrix & operator=(const Matrix &);
		Matrix & operator*(Matrix &);
		Matrix & operator*(float);
		Matrix & operator+(float);
		Matrix & operator+(Matrix);
		Matrix & operator-(float);
		Matrix & operator-(Matrix);
		Matrix & transpose();
		void randomize();
		void map( float (*f)(float) );
		int rows;
		int cols;
		float ** weights;

};

// Overloading the output stream operator << 
ostream & operator<<(ostream & out, Matrix & cm) {

	for (int y = 0; y < cm.rows; y++) {
		for (int x = 0; x < cm.cols; x++) {
			out << cm(y,x) << "\t";
		}
		out << endl;
	}

	return out;
}


Matrix::Matrix()
{
	rows    = 0;
	cols    = 0;
	weights = NULL;
}

Matrix::Matrix(int rows_, int cols_)
{
	rows    = rows_;
	cols    = cols_;
	weights = new float*[rows];
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		weights[curr_row] = new float[cols];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			weights[curr_row][curr_col] = 0;
		}
	}
	srand(time(0));
}

Matrix::Matrix(int rows_, int cols_, float * arr)
{
	rows    = rows_;
	cols    = cols_;
	weights = new float*[rows];
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		weights[curr_row] = new float[cols];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			weights[curr_row][curr_col] = arr[curr_row];
		}
	}
	srand(time(0));
}

// Copy constructor
Matrix::Matrix(Matrix & other) {
	rows = other.rows;
	cols = other.cols;
	weights = new float*[rows];
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		weights[curr_row] = new float[cols];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			weights[curr_row][curr_col] = other(curr_row, curr_col);
		}
	}
	srand(time(0));
}

// Copy constructor
Matrix::Matrix(const Matrix & other) {
	rows = other.rows;
	cols = other.cols;
	weights = new float*[rows];
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		weights[curr_row] = new float[cols];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			weights[curr_row][curr_col] = other(curr_row, curr_col);
		}
	}
	srand(time(0));
}

Matrix & Matrix::operator=(Matrix & other) {
	if (&other != this) {
		if (( rows != other.rows) && (cols != other.cols)) {
			if (weights != NULL) {
				delete [] weights;
			}
			rows = other.rows;
			cols = other.cols;
			weights = new float*[rows];
			for (int curr_row = 0; curr_row < rows; curr_row++)
			{
				weights[curr_row] = new float[cols];
				for (int curr_col = 0; curr_col < cols; curr_col++)
				{
					weights[curr_row][curr_col] = 1;
				}
			}
        }
        float * row;
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				row[curr_col] = other(curr_row,curr_col);
			}
		}
    }
	return (*this);

}

Matrix & Matrix::operator=(const Matrix & other) {
	if (&other != this) {
		if (( rows != other.rows) && (cols != other.cols)) {
			if (weights != NULL) {
				delete [] weights;
			}
			rows = other.rows;
			cols = other.cols;
			weights = new float*[rows];
			for (int curr_row = 0; curr_row < rows; curr_row++)
			{
				weights[curr_row] = new float[cols];
				for (int curr_col = 0; curr_col < cols; curr_col++)
				{
					weights[curr_row][curr_col] = 1;
				}
			}
        }
        float * row;
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				row[curr_col] = other(curr_row,curr_col);
			}
		}
    }
	return (*this);

}

Matrix::~Matrix()
{
	delete [] weights;
}

void Matrix::randomize()
{
	float * row;
	float r;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			r = ( (float) ((rand()) % 100) / 100);
			r = (r * 2) - 1;
			row[curr_col] = r;
		}
	}
}

float & Matrix::operator()(int y, int x) const{
	if (y < rows && x < cols) {
		return weights[y][x];
	} else {
		return weights[0][0];
	}
}

Matrix & Matrix::operator+(float num)
{
	Matrix * final = new Matrix(rows, cols);
	float * row;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			(*final)(curr_row, curr_col) = row[curr_col] + num;
		}
	}

	return (*final);
}

Matrix & Matrix::operator+(Matrix other)
{

	Matrix * final = new Matrix(rows, cols);
	if (other.cols == 1) {
		float * row;
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				(*final)(curr_row, curr_col) = row[curr_col] + other(curr_row, curr_col);
			}
		}
	} else {
		cout << "THERE IS AN ERROR\n";
	}

	return (*final);
}

Matrix & Matrix::operator-(float num)
{
	Matrix * final = new Matrix(rows, cols);
	float * row;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			(*final)(curr_row, curr_col) = row[curr_col] - num;
		}
	}

	return (*final);
}

Matrix & Matrix::operator-(Matrix other)
{

	Matrix * final = new Matrix(rows, cols);
	if (other.cols == 1) {
		float * row;
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				(*final)(curr_row, curr_col) = row[curr_col] - other(curr_row, curr_col);
			}
		}
	} else {
		cout << "THERE IS AN ERROR\n";
	}

	return (*final);
}

Matrix & Matrix::operator*(Matrix & other)
{
	Matrix * final = new Matrix(rows, other.cols);

	float * row;
	float sum;
	for (int i = 0; i < other.cols; i++)
	{
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			sum = 0;
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				sum += row[curr_col] * other(curr_col, i);
			}
			(*final)(curr_row, i) = sum;
		}
	}

	return (*final);
}

Matrix & Matrix::operator*(float num)
{
	Matrix * final = new Matrix(rows, 1);

	float * row;
	float sum;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		sum = 0;
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			sum += row[curr_col] * num;
		}
		(*final)(curr_row, 0) = sum;
	}


	return (*final);
}

void Matrix::map(float (*f)(float))
{
	float * row;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			row[curr_col] = f(row[curr_col]);
		}
	}
}

Matrix & Matrix::transpose()
{
	Matrix * final = new Matrix(cols, rows);
	float * row;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			(*final)(curr_col, curr_row) = row[curr_col];
		}
	}
	return (*final);
}

// // Overloading the output stream operator << 
// ostream & operator<<(ostream & out, Matrix & cm) {

// 	for (int y = 0; y < cm.rows; y++) {
// 		for (int x = 0; x < cm.cols; x++) {
// 			out << cm(y,x) << "\t";
// 		}
// 		out << endl;
// 	}

// 	return out;
// }



// int main()
// {
// 	Matrix m(3,1);
// 	cout << m << endl;
// 	// Matrix x(3,1);
// 	// x(0,0) = 100;
// 	// Matrix h(2,1);
// 	// Matrix y = m * h;
// 	// cout << y;
// 	// cout << m << endl;
// 	// //m.map(func);
// 	// cout << "HERE?" << endl;
// 	// Matrix y;
// 	// y = m + x;
// 	// cout << "AFTER?" << endl;
// 	// cout << y;
// 	// m.randomize();
// 	// cout << m << endl;
// 	// m = m + 5;
// 	// cout << m << endl;
// 	// m = m - 5;
// 	// cout << m;
// }




class NeuralNetwork
{
	public:
		NeuralNetwork(int,int,int,float);
		~NeuralNetwork();
		Matrix feedforward(Matrix &);
		int input_nodes;
		int hidden_nodes;
		int output_nodes;
		float lr;
		Matrix * weights_ih;
		Matrix * weights_ho;
		Matrix * bias_h;
		Matrix * bias_o;
		void train(Matrix &, Matrix &);
};


float sigmoid(float x)
{
	return (1 / (1 + exp(-x)));
}

float dsigmoid(float y)
{
	return y * (1 - y);
}



