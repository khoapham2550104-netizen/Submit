#include"Algo.h"
using namespace std;

int main(){
    int warehouse[100][100] = {
        {0,1,0,0,0,1,0},
        {0,1,0,1,0,1,0},
        {0,1,0,1,0,0,0},
        {0,0,0,1,1,1,0},
        {1,1,0,0,0,1,0},
        {0,0,0,1,0,1,0},
        {0,1,1,1,0,0,0}
    };


    int m = 7;
    int n = 7;

    int startX = 0;
    int startY = 0;

    int goalX = 6;
    int goalY = 6;

    int mode = 1;
    printPath(findWarehousePath(warehouse, m, n, startX, startY, goalX,goalY, mode));

}