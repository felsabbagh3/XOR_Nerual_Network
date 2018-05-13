#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;
class Matrix
{

	public:
		Matrix();
		Matrix(int,int);
		Matrix(Matrix &);
		~Matrix();
		float & operator()(int, int) const;
		Matrix & operator=(Matrix & other);
		Matrix & operator*(Matrix &);
		Matrix & operator+(int);
		Matrix & operator+(Matrix);
		Matrix & operator-(int);
		Matrix & operator-(Matrix);
		void randomize();
		void map( int (*f)(int) );
		int rows;
		int cols;
		float ** weights;

};

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
			weights[curr_row][curr_col] = 1;
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

Matrix::~Matrix()
{
	delete [] weights;
}

void Matrix::randomize()
{
	float * row;
	for (int curr_row = 0; curr_row < rows; curr_row++)
	{
		row = weights[curr_row];
		for (int curr_col = 0; curr_col < cols; curr_col++)
		{
			row[curr_col] = rand() % 10;
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

Matrix & Matrix::operator+(int num)
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

Matrix & Matrix::operator-(int num)
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

Matrix & Matrix::operator*(Matrix & other)
{
	Matrix * final = new Matrix(rows, 1);
	if (other.cols == 1)
	{
		float * row;
		float sum;
		for (int curr_row = 0; curr_row < rows; curr_row++)
		{
			row = weights[curr_row];
			sum = 0;
			for (int curr_col = 0; curr_col < cols; curr_col++)
			{
				sum += row[curr_col] * other(curr_col, 0);
			}
			(*final)(curr_row, 0) = sum;
		}
	} else {
		cout << "THERE IS AN ERROR";
	}

	return (*final);
}

void Matrix::map(int (*f)(int))
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

int func(int x)
{
	return (x * 2);
}

int main()
{
	// Matrix m(3,1);
	// Matrix x(3,1);
	// x(0,0) = 100;
	// Matrix h(2,1);
	// Matrix y = m * h;
	// cout << y;
	// cout << m << endl;
	// //m.map(func);
	// cout << "HERE?" << endl;
	// Matrix y;
	// y = m + x;
	// cout << "AFTER?" << endl;
	// cout << y;
	// m.randomize();
	// cout << m << endl;
	// m = m + 5;
	// cout << m << endl;
	// m = m - 5;
	// cout << m;
}

