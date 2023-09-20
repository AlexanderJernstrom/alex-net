#include <stdlib.h>
#include <math.h>
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

int *kNearesNeighbors(int k, struct knnPoint classifiedPoints[], struct Point unclassified[], int nUnclassified, int nClassified)
{
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
    }
}

int comparePoints(const void *a, const void *b)
{
    int sumA = ((struct knnPointDist *)a)->distance;
    int sumB = ((struct knnPointDist *)b)->distance;

    return sumA - sumB;
}

int pickPointClass(struct knnPointDist pointDistance[], int k, int n)
{
    if (k > n)
    {
        return NULL;
    }
    qsort(pointDistance, n, sizeof(struct knnPointDist), comparePoints);

    int classes[k];

    struct classOccurence
    {
        int class;
        int occurences;
    };

    struct classOccurence occurences[k];

    for (int i = 0; i < k; i++)
    {

        for (int i = 0; i < k; i++)
        {
            classes[i] = pointDistance[i].class;

            // Check if class already exists in occurences array
            int classExists = 0;
            for (int j = 0; j < k; j++)
            {
                if (occurences[j].class == pointDistance[i].class)
                {
                    classExists = 1;
                    break;
                }
            }

            // If class doesn't exist in occurences array, insert it
            if (classExists == 0)
            {
                struct classOccurence newOccurence;
                newOccurence.class = pointDistance[i].class;
                newOccurence.occurences = 0;
                occurences[i] = newOccurence;
            }
        }
    }

    for (int i = 0; i < k; i++)
    {
        }
}
