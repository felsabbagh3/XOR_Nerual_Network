#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
class NeuralNetwork
{

public:
	NeuralNetwork(int,int,int);
	int input_nodes;
	int hidden_nodes;
	int output_nodes;
private:


};


NeuralNetwork::NeuralNetwork(int input_nodes_, int hidden_nodes_, int output_nodes_)
{
	input_nodes  = input_nodes_;
	hidden_nodes = hidden_nodes_;
	output_nodes = output_nodes_;
}



int main()
{
	cout << "HI\n";
}