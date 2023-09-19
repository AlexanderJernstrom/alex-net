// {class("class of the point"), dim("how many dimensions the poins are in"), coords("the coordinates of the point")}
struct knnPoint
{
    int class;
    int dim;
    double *coords;
};

struct Point
{
    int dim;
    double *coords;
};

struct knnPoint *kNearesNeighbors(int k, struct knnPoint classifiedPoints[], struct Point unclassified[], int nUnclassified, int nClassified)
{
}
