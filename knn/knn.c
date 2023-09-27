#include <stdlib.h>
#include <math.h>
#include <stdio.h>
// {class("class of the point"), dim("how many dimensions the poins are in"), coords("the coordinates of the point")}
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
int *kNearestNeighbors(int k, struct knnPoint classifiedPoints[], struct Point unclassified[], int nUnclassified, int nClassified)
{
    if (k > nClassified)
    {
        return NULL;
    }
    int *classes = malloc(sizeof(int) * nUnclassified);
    for (int i = 0; i < nUnclassified; i++)
    {
        struct knnPointDist pointDistance[nClassified];
        for (int j = 0; j < nClassified; j++)
        {
            double distance = 0;
            if (unclassified[i].dim != classifiedPoints[i].dim)
            {
                return NULL;
            }
            for (int d = 0; d < classifiedPoints[j].dim; d++)
            {
                distance += (classifiedPoints[j].coords[d] - unclassified[i].coords[d]) * (classifiedPoints[j].coords[d] - unclassified[i].coords[d]);
            }

            distance = sqrt(distance);
            struct knnPointDist point;
            point.class = classifiedPoints[j].class;
            point.distance = distance;

            pointDistance[j] = point;
        }

        classes[i] = pickPointClass(pointDistance, k, nClassified);
    }

    return classes;
}

int comparePoints(const void *a, const void *b)
{
    int sumA = ((struct knnPointDist *)a)->distance;
    int sumB = ((struct knnPointDist *)b)->distance;

    return sumA - sumB;
}

int comparOccurences(const void *a, const void *b)
{
    int sumA = ((struct classOccurence *)a)->occurences;
    int sumB = ((struct classOccurence *)b)->occurences;

    return sumB - sumA;
}

int pickPointClass(struct knnPointDist pointDistance[], int k, int n)
{
    if (k > n)
    {
        return NULL;
    }
    qsort(pointDistance, n, sizeof(struct knnPointDist), comparePoints);

    int classes[k];

    struct classOccurence occurences[k];

    for (int i = 0; i < k; i++)
    {
        classes[i] = pointDistance[i].class;
    }

    for (int i = 0; i < k; i++)
    {
        int occurence = 0;
        for (int j = 0; j < k; j++)
        {
            if (classes[i] == classes[j])
            {
                occurence++;
            }
        }
        struct classOccurence occurenceStruct;
        occurenceStruct.class = classes[i];
        occurenceStruct.occurences = occurence;
        occurences[i] = occurenceStruct;
    }
    printf("occurences: %d, class: %d\n", occurences[0].occurences, occurences[0].class);
    printf("occurences: %d, class:%d \n", occurences[1].occurences, occurences[1].class);
    qsort(occurences, k, sizeof(struct classOccurence), comparOccurences);

    return occurences[0].class;
}
