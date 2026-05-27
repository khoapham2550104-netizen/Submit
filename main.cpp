#include"Algo.h"
using namespace std;

int main(){
    int floorPlan[100][100] = {0};

    int m = 10;
    int n = 10;

    int startX = 2;
    int startY = 3;

    int exitX = 9;
    int exitY = 6;
    double weightMatrix[100][100];
    int mode = 1;

    printPath(findEvacuationPath(floorPlan, m, n, startX, startY, exitX, exitY, weightMatrix, mode));

}