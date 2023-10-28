#include "../../linalg/matrix.h"
#include "nn.h"
#include "stdlib.h"
#include "stdio.h"
#include "../../functions/activation_functions.h"
void init_bias(struct Matrix *biases)
{
    for (int i = 0; i < (biases->cols * biases->rows); i++)
    {
        biases->elements[i] = 1;
    }
}

void init_weights(struct Matrix *weights)
{
    for (int i = 0; i < (weights->cols * weights->rows); i++)
    {
        weights->elements[i] = 2;
    }
}

struct NeuralNet initializeNN(int n_layers, int n_inputs, int n_outputs)
{
    struct NeuralNet nn = {.n_input = n_inputs, .n_hidden_layers = n_layers, .n_output = n_outputs};
    // inputs in vectors, n_input => n_input x 1 vector, weight layers n_input x n_input, bias vector n_output_from_layers x 1
    struct Layer *layers = malloc(sizeof(struct Layer) * n_layers);

    for (int i = 0; i < n_layers; i++)
    {
        struct Matrix weight_layer = createMatrix(n_inputs, n_inputs);
        struct Matrix bias_layer = createMatrix(n_inputs, 1);
        init_bias(&bias_layer);
        init_weights(&weight_layer);
        layers[i].weights = weight_layer;
        layers[i].biases = bias_layer;
        layers[i].n_nodes = n_inputs;
    }
    printf("Sizeof layers: %lu", sizeof(*layers) / sizeof(struct Layer));
    // printMatrix(layers[i].weights);
    nn.layers = layers;

    return nn;
}

struct Matrix forward(struct NeuralNet nn, struct Matrix inputs)
{
    // Output should always be initialized though input, if there are no layers then output should be returned
    struct Matrix output = inputs;

    for (int i = 0; i < nn.n_hidden_layers; i++)
    {

        struct Matrix weights_matrix = nn.layers[i].weights;
        struct Matrix bias_matrix = nn.layers[i].biases;

        matMul(&output, &weights_matrix, &output);
        matAdd(&output, &bias_matrix, &output);
    }
    return output;
}

void reluLayer(struct Matrix *inputMatrix)
{
}

void printNN(struct NeuralNet nn)
{
    printf("Hidden layers: %d, Input nodes: %d, Output nodes: %d \n", nn.n_hidden_layers, nn.n_input, nn.n_output);
}