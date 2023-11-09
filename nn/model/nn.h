#ifndef NN_H
#define NN_H

struct Layer
{
    struct Matrix weights;
    struct Matrix biases;
    double n_nodes;
};
struct NeuralNet
{
    int n_hidden_layers;
    int n_input;
    int n_output;
    struct Layer *layers;
};
struct Matrix forward(struct NeuralNet nn, struct Matrix inputs);
struct NeuralNet initializeNN(int n_layers, int n_inputs, int n_outputs);
void printNN(struct NeuralNet nn);
#endif
