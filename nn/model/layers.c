#include "../../linalg/matrix.h"
#include "layers.h"
#include "../../functions/activation_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
void seed_bias(struct Matrix *biases)
{
  for (int i = 0; i < (biases->cols * biases->rows); i++)
  {
    biases->elements[i] = 1;
  }
}

double gaussian_rand(double mean, double std_dev)
{
  double u = ((double)rand() / (RAND_MAX)) * 2 - 1;
  double v = ((double)rand() / (RAND_MAX)) * 2 - 1;
  double r = u * u + v * v;
  if (r == 0 || r > 1)
    return gaussian_rand(mean, std_dev);
  double c = sqrt(-2 * log(r) / r);
  return mean + std_dev * u * c;
}

DenseLayer createDenseLayer(int in_features, int out_features)
{
  DenseLayer dl = {};

  struct Matrix weights = createMatrix(in_features, out_features);
  struct Matrix biases = createMatrix(in_features, 1);

  seed_weights(&weights);
  seed_bias(&biases);

  dl.biases = biases;
  dl.weights = weights;
  dl.in_features = in_features;
  dl.out_features = out_features;
  return dl;
}

void seed_weights(struct Matrix *weights)
{
  for (int i = 0; i < (weights->cols * weights->rows); i++)
  {
    int row = i / weights->cols;
    int col = i % weights->cols;
    setMatrix(weights, row, col, gaussian_rand(0.0, 0.01));
  }
}

void reluLayer(struct Matrix *inputMatrix, ReluLayer *layerData)
{
  struct Matrix *input = deepCopyMatrix(inputMatrix);

  layerData->input = *input;
  for (int i = 0; i < (inputMatrix->cols * inputMatrix->rows); i++)
  {
    inputMatrix->elements[i] = relU(inputMatrix->elements[i]);
  }
  struct Matrix *output = deepCopyMatrix(inputMatrix);

  layerData->output = *output;
}

void sigmoidLayer(struct Matrix *inputMatrix, SigmoidLayer *layerData)
{
  struct Matrix *input = deepCopyMatrix(inputMatrix);
  layerData->input = *input;
  for (int i = 0; i < (inputMatrix->cols * inputMatrix->rows); i++)
  {
    inputMatrix->elements[i] = sigmoid(inputMatrix->elements[i]);
  }
  struct Matrix *output = deepCopyMatrix(inputMatrix);
  layerData->output = *output;
}

ReluLayer createReluLayer() {}

void denseLayer(struct Matrix *inputMatrix, DenseLayer *layerData)
{

  struct Matrix out = createMatrix(layerData->out_features, 1);

  layerData->input = *inputMatrix;
  matMul(&layerData->weights, inputMatrix, &out);

  matAdd(&out, &layerData->biases, &out);
  inputMatrix->elements = out.elements;

  layerData->output = out;
}

void reshapeLayer(struct Matrix *inputMatrix, ReshapeLayer *layerData)
{
}

// Take in prev gradient as argument, get gradients with respect to each weight and bias and append to final grad
// https://web.eecs.umich.edu/~justincj/teaching/eecs498/FA2020/linear-backprop.html
// DLoss/dWeight = Input(transpose) * DLoss/DOutput
// learning_rate * dLoss/dWeight
// weights - (learningRate * dLoss/dWeight) (element wise)
void denseLayerBackward(struct Matrix *gradient, DenseLayer *layer, struct Matrix *outputDerivative, double learning_rate)
{
  // X(transpose)
  struct Matrix transposed_input = transpose(&layer->input);

  struct Matrix d_weights = createMatrix(layer->weights.rows, layer->weights.cols);
  matMul(outputDerivative, &transposed_input, gradient);
  matMul(outputDerivative, &transposed_input, &d_weights);
  for (int i = 0; i < (d_weights.cols * d_weights.rows); i++)
  {
    d_weights.elements[i] = learning_rate * d_weights.elements[i];
  }
  matAdd(&layer->weights, &d_weights, &layer->weights);
}

//
void sigmoidLayerBackwards(struct Matrix *gradient, SigmoidLayer *layer)
{
  struct Matrix *input = deepCopyMatrix(&layer->input);
  for (int i = 0; i < (input->cols * input->rows); i++)
  {
    input->elements[i] = dSigmoid(input->elements[i]);
  }
  matMul(gradient, input, gradient);
}
void reluLayerBackwards(struct Matrix *gradient, ReluLayer *layer)
{
  struct Matrix *input = deepCopyMatrix(&layer->input);
  for (int i = 0; i < (input->cols * input->rows); i++)
  {
    input->elements[i] = dReLU(input->elements[i]);
  }
  matMul(gradient, input, gradient);
}