#ifndef KNN_EVAL 
#define KNN_EVAL

void knn_eval();

typedef struct {
    int area;
    float solidity;
    int convex_area;
    float roundness;
    float compactness;
} DryBeanTrain;

typedef struct {
    int area;
    float solidity;
    int convex_area;
    float roundness;
    float compactness;
    int label;
} DryBeanTest;

#endif