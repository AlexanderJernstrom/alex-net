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
void seed_weights(struct Matrix *weights)
{
  for (int i = 0; i < (weights->cols * weights->rows); i++)
  {
    int row = i / weights->cols;
    int col = i % weights->cols;
    setMatrix(weights, row, col, gaussian_rand(0.0, 0.01));
  }
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

void softmaxLayer(struct Matrix *inputMatrix, SoftmaxLayer *layerData)
{
  struct Matrix *input = deepCopyMatrix(inputMatrix);
  layerData->input = *input;

  struct Matrix output = softmax(*inputMatrix);
  inputMatrix->elements = output.elements;
  layerData->output = output;
}

ReluLayer createReluLayer() {}

void denseLayer(struct Matrix *inputMatrix, DenseLayer *layerData)
{
  /*   printf("out_features: %d\n", layerData->out_features);
    printf("in_features: %d\n", layerData->in_features);
    printf("Size dimensions of layerData->weights: %d x %d\n", layerData->weights.rows, layerData->weights.cols);
   */
  struct Matrix out = {};
  layerData->input = *inputMatrix;
  matMul(inputMatrix, &layerData->weights, &out);

  matAdd(inputMatrix, &layerData->biases, inputMatrix);

  layerData->output = *inputMatrix;
  inputMatrix->cols = out.cols;
  inputMatrix->rows = out.rows;
  inputMatrix->elements = out.elements;
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
  matMul(&transposed_input, outputDerivative, gradient);
  matMul(&transposed_input, outputDerivative, &d_weights);

  for (int i = 0; i < (d_weights.cols * d_weights.rows); i++)
  {
    d_weights.elements[i] += learning_rate * d_weights.elements[i];
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

void softmaxLayerBackwards(struct Matrix *gradient, SoftmaxLayer *layer)
{
  struct Matrix jacobian = createMatrix(layer->input.rows, layer->input.rows);
  // Jacobian will always be square
  int n = layer->input.rows;

  for (int i = 0; i < (jacobian.cols * jacobian.rows); i++)
  {
    for (int j = 0; j < (jacobian.cols * jacobian.rows); j++)
    {
      int index = (i * n) + j;
      if (i == j)
      {
        jacobian.elements[index] = layer->output.elements[i] * (1 - layer->output.elements[i]);
      }
      else
      {
        jacobian.elements[index] = -layer->output.elements[i] * layer->output.elements[j];
      }
    }
  }

  struct Matrix transposed_gradient = transpose(gradient);

  matMul(&transposed_gradient, &jacobian, gradient);
  /* printf("Gradient matrix after matmul in softmax \n");
  printMatrix(*gradient); */

  // free(jacobian.elements);
}

void reluLayerBackwards(struct Matrix *gradient, ReluLayer *layer)
{
  struct Matrix *input = deepCopyMatrix(&layer->input);
  for (int i = 0; i < (input->cols * input->rows); i++)
  {
    input->elements[i] = dReLU(input->elements[i]);
  }
  struct Matrix transposed_gradient = transpose(gradient);
  matMul(&transposed_gradient, input, gradient);
}