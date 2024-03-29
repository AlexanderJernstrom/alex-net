
#include <stdlib.h>
#include "../linalg/matrix.h"
#include "../nn/model/layers.h"
#include "../functions/loss_functions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Load mnist data
const int LABELS = 10;
const double LEARNING_RATE = 0.009;

void ReadMNIST(struct Matrix *train_values, struct Matrix *labels, int n_points)
{

    FILE *stream = fopen("examples/data/MNIST/mnist_train.csv", "r");
    if (stream == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }

    char line[5700];
    int line_number = 0;
    while (fgets(line, 5700, stream) && line_number < n_points)
    {
        if (line_number > 0)
        {
            char *token = strtok(line, ",");
            int column = 1; // Start from the first column
            float label;

            while (token != NULL)
            {
                if (column == 1)
                {
                    label = atof(token);
                }
                else if (column <= 784)
                {
                    // Populate matrix and normalize pixel values
                    setMatrix(train_values, line_number - 1, column - 2, (double)atof(token) / 255);
                }

                token = strtok(NULL, ",");
                column++;

                setMatrix(labels, line_number - 1, 0, label);
            }
        }
        line_number++;
    }
}

void ReadMNISTRow(struct Matrix *train_sample, int *label, int line_number)
{

    FILE *stream = fopen("examples/data/MNIST/mnist_train.csv", "r");
    if (stream == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }

    char line[5700];
    fgets(line, 5700, stream);
}

void backwardPass(Layer *layers, struct Matrix *gradient, int n_layers)
{
    for (int i = n_layers - 1; i >= 0; i--)
    {
        switch (layers[i].type)
        {
        case DENSE:
            denseLayerBackward(gradient, layers[i].layer, gradient, LEARNING_RATE);
            // printf("Dense: %d \n", i);
            //  printMatrix(gradient);
            break;
        case SIGMOID:
            sigmoidLayerBackwards(gradient, layers[i].layer);
            // printMatrix(gradient);
            // printf("Sigmoid");
            break;
        case RELU:
            reluLayerBackwards(gradient, layers[i].layer);
            // printMatrix(gradient);
            // printf("ReLU \n");
            break;
        case SOFTMAX:
            softmaxLayerBackwards(gradient, layers[i].layer);
            // printMatrix(gradient);
            // printf("Softmax \n");
            // printMatrix(gradient);
            break;
        }
    }
}
void forwardPass(Layer *layers, struct Matrix *data, int n_layers)
{
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
            softmaxLayer(data, layers[i].layer);
            break;
        }
    }
}

void nn_eval()
{
    srand(time(NULL));

    int n_data_points = 12000;
    int epochs = 3;
    struct Matrix train_data = createMatrix(n_data_points, 784);
    struct Matrix labels = createMatrix(n_data_points, 1);
    // setup data, input data 784 length vector
    ReadMNIST(&train_data, &labels, n_data_points);

    /*     printf("Training data \n");
    printMatrix(train_data);
 */
    int n_layers = 4;
    Layer *layers = malloc(sizeof(Layer) * n_layers);

    DenseLayer dl1 = createDenseLayer(784, 512);
    Layer l1 = {.type = DENSE, .layer = (void *)&dl1};

    ReluLayer rl1 = {};
    Layer l2 = {.type = RELU, .layer = (void *)&rl1};

    DenseLayer dl2 = createDenseLayer(512, 10);
    Layer l3 = {.type = DENSE, .layer = (void *)&dl2};

    SoftmaxLayer sm1 = {};
    Layer l4 = {.type = SOFTMAX, .layer = (void *)&sm1};

    layers[0] = l1;
    layers[1] = l2;
    layers[2] = l3;
    layers[3] = l4;

    for (int e = 0; e < epochs; e++)
    {
        double error = 0;
        for (int i = 0; i < 8000; i++)
        {
            // Define the range
            int min = 0;
            int max = 8000;

            // Generate random number in [min, max]
            int randomIndex = min + rand() % (max - min + 1);
            // One hot encode label
            struct Matrix one_hot = createMatrix(1, LABELS);
            setMatrix(&one_hot, 0, labels.elements[randomIndex], 1);

            struct Matrix X = extractVector(&train_data, randomIndex);

            forwardPass(layers, &X, n_layers);

            struct Matrix gradient = crossEntropyDerivative(LABELS, &one_hot, &X);

            backwardPass(layers, &gradient, n_layers);
            double loss = crossEntropy(LABELS, X, one_hot);
            error += loss;
            free(X.elements);
        }
        printf("Epoch: %d, Loss: %f \n", e, error / 8000);
        // printMatrix(dl1.output);
        // printMatrix(dl1.input);
    }

    printf("\nTraining done\n");
    // validation
    int corrects = 0;
    for (int i = 0; i < 3000; i++)
    {
        struct Matrix X = extractVector(&train_data, i + 8000);

        forwardPass(layers, &X, n_layers);

        int argMaxIndex = 0;

        for (int j = 0; j < (X.cols * X.rows); j++)
        {
            if (X.elements[j] > X.elements[argMaxIndex])
            {
                argMaxIndex = j;
            }
        }

        if (argMaxIndex == labels.elements[i])
        {
            corrects++;
        }
    }
    printf("Validation done, correct amount: %d correct: %f \n", corrects, ((float)corrects / 3000) * 100);
}
