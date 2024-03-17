#include "../knn/knn.h"
#include <stdio.h>
#include "./knn_eval.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// labels (Seker, Barbunya, Bombay, Cali, Dermosan, Horoz and Sira)
int labelToNum(char *label)
{
    if (strcmp(label, "SEKER\r\n") == 0)
    {
        return 1;
    }
    else if (strcmp(label, "BARBUNYA\r\n") == 0)
    {
        return 2;
    }
    else if (strcmp(label, "BOMBAY\r\n") == 0)
    {
        return 3;
    }
    else if (strcmp(label, "CALI\r\n") == 0)
    {
        return 4;
    }
    else if (strcmp(label, "DERMOSAN\r\n") == 0)
    {
        return 5;
    }
    else if (strcmp(label, "HOROZ\r\n") == 0)
    {
        return 6;
    }
    else if (strcmp(label, "SIRA\r\n") == 0)
    {
        return 7;
    }
    else
    {
        // Handle unknown label
        return -1;
    }
}

DryBeanTest *loadBeanDataFromCsv()
{
    int n_training = 13000;
    FILE *stream = fopen("examples/data/Dry_Beans_Dataset_Table.csv", "r");
    if (stream == NULL)
    {
        perror("Unable to open the file.");
        exit(1);
    }
    char line[1024];
    DryBeanTest *train_set = malloc(sizeof(DryBeanTest) * n_training);
    int line_number = 0;

    while (fgets(line, 1024, stream))
    {
        if (line_number > 0)
        {
            char *token = strtok(line, ";");
            int column = 1; // Start from the first column
            double area, solidity, convex_area, roundness, compactness;
            char *label;

            while (token != NULL)
            {
                if (column == 1)
                {
                    area = atof(token);
                }
                else if (column == 10)
                {
                    solidity = atof(token);
                }
                else if (column == 11)
                {
                    roundness = atof(token);
                }
                else if (column == 7)
                {
                    convex_area = atof(token);
                }
                else if (column == 12)
                {
                    compactness = atof(token);
                }
                else if (column == 17)
                {
                    label = token;
                }
                token = strtok(NULL, ";");
                column++;
            }
            DryBeanTest data = {.area = area, .compactness = compactness, .solidity = solidity, .roundness = roundness, .convex_area = convex_area};
            data.label = labelToNum(label);
            train_set[line_number - 1] = data;
        }
        line_number++;
    }
    return train_set;
}

void knn_eval()
{
    int n_classified = 10000;
    int n_unclassified = 2000;
    DryBeanTest *data = loadBeanDataFromCsv();
    struct Point *unclassified_points = malloc(sizeof(struct Point) * n_unclassified);
    struct knnPoint *classified_points = malloc(sizeof(struct knnPoint) * n_classified);

    // populate classified_points
    for (int i = 0; i < n_classified; i++)
    {
        double *coordinates = malloc(sizeof(double) * 5);
        coordinates[0] = data[i].area;
        coordinates[1] = data[i].compactness;
        coordinates[2] = data[i].convex_area;
        coordinates[3] = data[i].roundness;
        coordinates[4] = data[i].compactness;
        struct knnPoint classified_point = {
            .class = data[i].label,
            .dim = 5,
            .coords = coordinates,

        };
        classified_points[i] = classified_point;
    }

    // populate unclassified points
    for (int i = n_classified; i < 12000; i++)
    {
        double *coordinates = malloc(sizeof(double) * 5);
        coordinates[0] = data[i].area;
        coordinates[1] = data[i].compactness;
        coordinates[2] = data[i].convex_area;
        coordinates[3] = data[i].roundness;
        coordinates[4] = data[i].compactness;
        struct Point unclassified_point = {
            .coords = coordinates,
            .dim = 5};
        unclassified_points[i - n_classified] = unclassified_point;
    }
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int *classes = kNearestNeighbors(3, classified_points, unclassified_points, n_unclassified, n_classified);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("The function took %f seconds to execute.\n", cpu_time_used);
}