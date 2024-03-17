#ifndef KNN_EVAL
#define KNN_EVAL

void knn_eval();

typedef struct
{
    double area;
    double solidity;
    double convex_area;
    double roundness;
    double compactness;
} DryBeanTrain;

typedef struct
{
    double area;
    double solidity;
    double convex_area;
    double roundness;
    double compactness;
    int label;
} DryBeanTest;

#endif