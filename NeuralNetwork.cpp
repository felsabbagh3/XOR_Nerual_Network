
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <stdlib.h>
#include <math.h>

#include "NeuralNetwork.h"



using namespace std;

NeuralNetwork::NeuralNetwork(int input_nodes_, int hidden_nodes_, int output_nodes_, float lr_) : input_nodes(input_nodes_), hidden_nodes(hidden_nodes_), output_nodes(output_nodes_), lr(lr_)
{
	weights_ih = new Matrix(hidden_nodes, input_nodes);
	weights_ih->randomize();
	weights_ho = new Matrix(output_nodes, hidden_nodes);
	weights_ho->randomize();
	bias_h = new Matrix(hidden_nodes, 1);
	bias_h->randomize();
	bias_o = new Matrix(output_nodes, 1);
	bias_o->randomize();
}

NeuralNetwork::~NeuralNetwork()
{
	delete weights_ih;
	delete weights_ho;
	delete bias_h;
	delete bias_o;
}

Matrix NeuralNetwork::feedforward(Matrix & input)
{
	// Generating the hidden outputs
	Matrix hidden = (*weights_ih) * (input);
	hidden = hidden + (*bias_h);
	// Activation Function for hidden layer
	hidden.map(sigmoid);

	// Generating output
	Matrix output = (*weights_ho) * hidden;
	output = output + (*bias_o);
	// Activation function for output layers
	output.map(sigmoid);

	return output;
}

void NeuralNetwork::train(Matrix & input, Matrix & target)
{
	Matrix who_tr = weights_ho->transpose();

    // *************** FEED FORWARD **************
	// Generating the hidden outputs
	Matrix hidden = (*weights_ih) * (input);
	hidden = hidden + (*bias_h);
	// Activation Function for hidden layer
	hidden.map(sigmoid);

	// Generating output
	Matrix output = (*weights_ho) * hidden;
	output = output + (*bias_o);
	// Activation function for output layers
	output.map(sigmoid);
	// ********************************************


	// Calculating the error at each layer
	Matrix output_errors  = target - output;
	Matrix hidden_errors  = who_tr * output_errors;

	// Calculate Gradient
	Matrix output_gradients = output;
	output_gradients.map(dsigmoid);
	output_gradients = output_gradients * output_errors;
	output_gradients = output_gradients * lr;

	// Calculate HO Deltas
	Matrix hidden_t          = hidden.transpose();
	Matrix weights_ho_deltas = output_gradients * hidden_t;

	// Changing HO layer weights
	weights_ho = weights_ho + weights_ho_deltas;

	// Calculating Hidden Gradient
	Matrix hidden_gradient = hidden;
	hidden_gradient.map(dsigmoid);
	hidden_gradient = hidden_gradient * hidden_errors;
	hidden_gradient = hidden_gradient * lr;


	// Calculating IH deltas
	Matrix input_t           = input.transpose();
	Matrix weights_ih_deltas = hidden_gradient * input_t;

	// Changing IH layer weights
	weights_ih = weights_ih + weights_ih_deltas;

}

int main()
{
	NeuralNetwork nn(2,2,1,0.1);

	Matrix input(2,1);
	input(0,0) = 1;
	input(1,0) = 0;

	Matrix output(1,1);
	output(0,0) = 1;

	nn.train(input, output);

}











