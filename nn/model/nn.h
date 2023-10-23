#ifndef NN_H
#define NN_H
typedef struct
{
    int n_hidden_layers;
    int n_input;
    int n_output;
    Layer *layers;
} NeuralNet;
typedef struct
{
    double *weights;
    double *biases;
    double n_nodes;
} Layer;
NeuralNet initializeNN(int n_layers, int n_inputs, int n_outputs);
void printNN(NeuralNet nn);
#endif