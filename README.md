# alex-net

A simple ML library written in C with some common ML algorithms such as Linear regression, Logistic regression , k-NN and many more.

(Has nothing to do with the architecture propsoed in Krizhevsky et al. 2012)

Made as a high school diploma project. 

## Neural network

The neural netowrk is completely implemented from scratch, everything from matrix operations to backprop is implemented. Currently it only support linear/dense/fully-connected layers together with some common activation functions.

### Layers

Layer in alex-net are all the different kinds of matrix operations that are done on the data, this include fully connected layers but also activation functions.

All layers store the input value and the output value, which are calculated during the forward pass. Layers may also store other kinds of data depending on the type, for example the `DenseLayer` stores also the weights and bias.

Every layer implements its own forward and backward pass and is located in `layers.c`. Therefore a backward pass can be implemented in this way:

```c
for (int i = n_layers - 1; i >= 0; i--)
{
            switch (layers[i].type)
            {
            case DENSE:
                denseLayerBackward(&gradient, layers[i].layer, &gradient, LEARNING_RATE);
                break;
            case SIGMOID:
                sigmoidLayerBackwards(&gradient, layers[i].layer);
                break;
            case RELU:
                reluLayerBackwards(&gradient, layers[i].layer);
                break;
}
```

## Running

Script to run: `gcc -g main.c functions/loss_functions.c functions/activation_functions.c regression/linear_regression.c calc/calculus.c knn/knn.c regression/logistic_regression.c linalg/matrix.c nn/model/nn.c nn/model/layers.c nn/tests/nn_test.c examples/linear_regression_eval.c functions/evalutation_functions.c examples/logistic_regression_eval.c examples/knn_eval.c examples/nn_eval.c  -lm -o  ./a.out`
Will update to a better solution
