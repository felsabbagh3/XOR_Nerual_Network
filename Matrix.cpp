#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;
class Matrix
{

	public:
		Matrix(int,int);
		float & operator()(int, int) const;
		~Matrix();
		Matrix operator*(Matrix &);
		void randomize();
		int rows;
		int cols;
		float ** weights;

};

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

Matrix Matrix::operator*(Matrix & other)
{
	Matrix final(rows, 1);
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
			final(curr_row, 0) = sum;
		}
	} else {
		cout << "THERE IS AN ERROR";
	}

	return final;
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

int main()
{
	Matrix m(3,2);
	// Matrix h(2,1);
	// Matrix y = m * h;
	m.randomize();
	cout << m;
}

