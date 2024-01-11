#include "../knn/knn.h"
#include <stdio.h>
#include "./knn_eval.h"
#include <stdlib.h>

void extractHousePriceFromLine(char *line)
{
    const char delimiter[2] = ";";
    char *tokens = strtok(line, delimiter);
}

// labels (Seker, Barbunya, Bombay, Cali, Dermosan, Horoz and Sira)
int labelToNum(char *label)
{
    if (strcmp(label, "Seker") == 0)
    {
        return 1;
    }
    else if (strcmp(label, "Barbunya") == 0)
    {
        return 2;
    }
    else if (strcmp(label, "Bombay") == 0)
    {
        return 3;
    }
    else if (strcmp(label, "Cali") == 0)
    {
        return 4;
    }
    else if (strcmp(label, "Dermosan") == 0)
    {
        return 5;
    }
    else if (strcmp(label, "Horoz") == 0)
    {
        return 6;
    }
    else if (strcmp(label, "Sira") == 0)
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
    int n_training = 13e4;
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
            char *token = strtok(line, ",");
            int column = 1; // Start from the first column
            float area, solidity, convex_area, roundness, compactness;
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
                    break; // No need to tokenize further
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
                token = strtok(NULL, ",");
                column++;
            }
            DryBeanTest data = {.area = area, .compactness = compactness, .solidity = solidity, .roundness = roundness, .convex_area = convex_area};
            data.label = labelToNum(label);
            train_set[line_number] = data;
        }
        line_number++;
    }
    return train_set;
}

void knn_eval()
{
    int n_classified = 10e4;
    int n_unclassified = 2000;
    DryBeanTest *data = loadBeanDataFromCsv();
    struct Point *unclassified_points = malloc(sizeof(struct Point) * n_unclassified);
    struct knnPoint *classified_points = malloc(sizeof(struct knnPoint) * n_classified);

    // populate classified_points
    for (int i = 0; i < n_classified; i++)
    {
        struct knnPoint classified_point = {
            .class = data[i].label,
            .dim = 5,
        };
    }
}