#include "../../linalg/matrix.h"
#include "../model/layers.h"
#include "../../functions/loss_functions.h"
#include <stdlib.h>
#include <stdio.h>
void test_nn()
{
    struct Matrix input_matrix = createMatrix(3, 1);
    setMatrix(&input_matrix, 0, 0, 1);
    setMatrix(&input_matrix, 1, 0, 2);
    setMatrix(&input_matrix, 2, 0, -10);

    struct Matrix train_data = createMatrix(1, 1);
    setMatrix(&train_data, 0, 0, 4);

    int n_layers = 4;
    Layer *layers = malloc(sizeof(Layer) * n_layers);

    DenseLayer dl1 = createDenseLayer(3, 3);
    Layer l1 = {.type = DENSE, .layer = (void *)&dl1};
    SigmoidLayer sigmoidl2 = {};
    Layer l2 = {.type = SIGMOID, .layer = (void *)&sigmoidl2};
    ReluLayer rl1 = {};
    Layer layer3 = {.type = RELU, .layer = (void *)&rl1};
    DenseLayer dl2 = createDenseLayer(3, 1);
    Layer layer4 = {.type = DENSE, .layer = (void *)&dl2};

    layers[0] = l2;
    layers[1] = l1;
    layers[2] = layer3;
    layers[3] = layer4;

    //  Forward pass

    for (int train_iteration = 0; train_iteration < 1000; train_iteration++)
    {
        struct Matrix *data = deepCopyMatrix(&input_matrix);
        // printf("NN input\n");
        // printMatrix(*data);
        for (int i = 0; i < n_layers; i++)
        {
            switch (layers[i].type)
            {
            case DENSE:
                denseLayer(data, layers[i].layer);
                break;
            case SIGMOID:
                sigmoidLayer(data, layers[i].layer);
                break;
            case RELU:
                reluLayer(data, layers[i].layer);
                break;
            case SOFTMAX:
                printf("RESHAPE");
                break;
            }
        }
        struct Matrix loss_mat = createMatrix(3, 1);
        for (int i = 0; i < (train_data.cols * train_data.rows); i++)
        {
            loss_mat.elements[i] = pointMSE(train_data.elements[i], data->elements[i]);
        }
        /*         printf("Loss \n");
                printMatrix(loss_mat);
         */
        struct Matrix gradient = createMatrix(train_data.rows, train_data.cols);

        // calculate dLoss/dOutput
        for (int i = 0; i < (gradient.cols * gradient.rows); i++)
        {
            gradient.elements[i] = pointMSEDerivative(train_data.elements[i], data->elements[i]);
        }

        // backward pass
        for (int i = n_layers - 1; i >= 0; i--)
        {
            switch (layers[i].type)
            {
            case DENSE:
                denseLayerBackward(&gradient, layers[i].layer, &gradient, 0.01);
                break;
            case SIGMOID:
                sigmoidLayerBackwards(&gradient, layers[i].layer);
                break;
            case RELU:
                reluLayerBackwards(&gradient, layers[i].layer);
                break;
            case SOFTMAX:
                printf("RESHAPE");
                break;
            }
        }

        printf("Model output, iteration: %d \n", train_iteration);
        printMatrix(dl2.output);
    }
}
