#include"Algo.h"
using namespace std;

int main(){
    int coords[100][2] = {
        {0,0},   // node 0
        {1,2},   // node 1
        {3,1},   // node 2
        {4,4},   // node 3
        {6,5}    // node 4
    };

    double adjMatrix[100][100] = {
        {0, 2.5, 0, 0, 0},
        {2.5, 0, 1.8, 0, 0},
        {0, 1.8, 0, 3.1, 0},
        {0, 0, 3.1, 0, 2.2},
        {0, 0, 0, 2.2, 0}
    };
    int startPoint = 0;
    int goalPoint = 4;
    printPath(findDronePath(adjMatrix,coords, startPoint, goalPoint, 1));

}