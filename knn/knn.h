#ifndef KNN_H
#define KNN_H

struct knnPoint
{
    int class;
    int dim;
    double *coords;
};

struct knnPointDist
{
    int class;
    double distance;
};

struct Point
{
    int dim;
    double *coords;
};

struct classOccurence
{
    int class;
    int occurences;
};

int pickPointClass(struct knnPointDist pointDistance[], int k, int n);
int *kNearestNeighbors(int k, struct knnPoint classifiedPoints[], struct Point unclassified[], int nUnclassified, int nClassified);
int comparePoints(const void *a, const void *b);
int comparOccurences(const void *a, const void *b);

#endif