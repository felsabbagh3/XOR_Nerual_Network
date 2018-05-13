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

