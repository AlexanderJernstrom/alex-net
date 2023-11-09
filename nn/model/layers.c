#include "../../linalg/matrix.h"
#include "layers.h"
#include "../../functions/activation_functions.h"
#include <stdio.h>
void seed_bias(struct Matrix *biases)
{
  for (int i = 0; i < (biases->cols * biases->rows); i++)
  {
    biases->elements[i] = 1;
  }
}

void seed_weights(struct Matrix *weights)
{
  for (int i = 0; i < (weights->cols * weights->rows); i++)
  {
    int row = i / weights->cols;
    int col = i % weights->cols;
    setMatrix(weights, row, col, 2.0);
  }
}
void reluLayer(struct Matrix *inputMatrix)
{
  for (int i = 0; i < (inputMatrix->cols * inputMatrix->rows); i++)
  {
    inputMatrix->elements[i] = relU(inputMatrix->elements[i]);
  }
}

void sigmoidLayer(struct Matrix *inputMatrix)
{
  for (int i = 0; i < (inputMatrix->cols * inputMatrix->rows); i++)
  {
    inputMatrix->elements[i] = sigmoid(inputMatrix->elements[i]);
  }
}

void denseLayer(struct Matrix *inputMatrix)
{
  struct Matrix weights_layer = createMatrix(inputMatrix->rows, inputMatrix->rows);
  struct Matrix bias_layer = createMatrix(inputMatrix->rows, 1);
  seed_weights(&weights_layer);
  seed_bias(&bias_layer);
  struct Matrix out = createMatrix(inputMatrix->rows, inputMatrix->cols);

  matMul(&weights_layer, inputMatrix, &out);
  inputMatrix->elements = out.elements;
  // matAdd(inputMatrix, &bias_layer, inputMatrix);
}
