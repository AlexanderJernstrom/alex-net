#ifndef LAYERS_H
#define LAYERS_H

// Base layer function:
//

void seed_bias(struct Matrix *biases);
void seed_weights(struct Matrix *weights);

typedef enum
{
    DENSE,
    RELU,
    SIGMOID,
    RESHAPE
} LayerType;

typedef struct
{
    struct Matrix weights;
    struct Matrix biases;
    struct Matrix input;
    struct Matrix output;
} DenseLayer;

typedef struct
{
    int new_cols;
    int new_rows;
} ReshapeLayer;

typedef struct
{
    struct Matrix input;
    struct Matrix output;
} ReluLayer;

typedef struct
{
    struct Matrix input;
    struct Matrix output;
} SigmoidLayer;

typedef union
{
    DenseLayer dense;
} LayerData;

typedef struct
{
    LayerType type;
    void *layer;
} Layer;

void reluLayer(struct Matrix *inputMatrix, ReluLayer *layerData);
void sigmoidLayer(struct Matrix *inputMatrix, SigmoidLayer *layerData);
void denseLayer(struct Matrix *inputMatrix, DenseLayer *layerData);
void denseLayerBackward(struct Matrix *gradient, DenseLayer *layer, struct Matrix *outputDerivative, double learning_rate);
void sigmoidLayerBackwards(struct Matrix *gradient, SigmoidLayer *layer);
void reluLayerBackwards(struct Matrix *gradient, ReluLayer *layer);
#endif
