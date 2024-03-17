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
  struct Matrix out = {};
  layerData->input = *inputMatrix;
  matMul(inputMatrix, &layerData->weights, &out);

  matAdd(inputMatrix, &layerData->biases, inputMatrix);

  inputMatrix->cols = out.cols;
  inputMatrix->rows = out.rows;
  inputMatrix->elements = out.elements;
  layerData->output = *inputMatrix;
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
  /*   printf("Dimensions of transposed_input: %d x %d\n", transposed_input.rows, transposed_input.cols);
    printf("Dimensions of outputDerivative: %d x %d\n", outputDerivative->rows, outputDerivative->cols);
   */
  struct Matrix d_weights = {};
  matMul(&transposed_input, outputDerivative, outputDerivative);
  matMul(&transposed_input, outputDerivative, &d_weights);

  for (int i = 0; i < (d_weights.cols * d_weights.rows); i++)
  {

    d_weights.elements[i] = -learning_rate * d_weights.elements[i];
  }
  matAdd(&layer->weights, &d_weights, &layer->weights);
  /*
    printf("Dimensions of layer->weights: %d x %d\n", layer->weights.rows, layer->weights.cols);
    printf("Dimensions of layer->d_weights: %d x %d\n", d_weights.rows, d_weights.cols); */
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
  struct Matrix jacobian = createMatrix(layer->input.cols, layer->input.cols);
  for (int i = 0; i < (jacobian.cols * jacobian.rows); i++)
  {
    int row;
    int col;
    indexToRowCol(&jacobian, i, &row, &col);
    if (col == row)
    {

      jacobian.elements[i] = layer->output.elements[col] * (1 - layer->output.elements[col]);
    }
    else
    {

      jacobian.elements[i] = -layer->output.elements[row] * layer->output.elements[col];
    }
  }

  struct Matrix transposed_gradient = transpose(gradient);
  /* printf("Dimensions of gradient: %d x %d\n", gradient->rows, gradient->cols);
  printf("Dimensions of jacobian: %d x %d\n", jacobian.rows, jacobian.cols);

 */
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
  struct Matrix transposed_input = transpose(input);

  matMul(&transposed_gradient, &transposed_input, gradient);
  free(transposed_gradient.elements);
  free(transposed_input.elements);
}