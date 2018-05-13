#include <iostream>

class Matrix
{

	public:
		Matrix(int,int);
		~Matrix();
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
}

Matrix::~Matrix()
{
	delete [] weights;
}


int main()
{
	std::cout << "HI\n";
}