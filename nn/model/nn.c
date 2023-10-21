#include "nn.h"
#include "stdlib.h"
#include "stdio.h"
NeuralNet initializeNN(int n_layers, int n_inputs, int n_outputs)
{
    NeuralNet nn = {.n_input = n_inputs, .n_hidden_layers = n_layers, .n_output = n_outputs};
    return nn;
}

double *forward(NeuralNet nn, double *input)
{
    double *outputs = malloc(sizeof(double) * nn.n_output);

    for (int i = 0; i < nn.n_input; i++)
    {
        for (int j = 0; j < nn.n_hidden_layers; j++)
        {
        }
    }

    return outputs;
}

void printNN(NeuralNet nn)
{
    printf("Hidden layers: %d, Input nodes: %d, Output nodes: %d \n", nn.n_hidden_layers, nn.n_input, nn.n_output);
}