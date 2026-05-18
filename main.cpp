#include"Algo.h"
using namespace std;

int main(){
    double adjMatrix[100][100] = {

    //0 1 2 3 4 5
    {0,1,1,0,0,0}, // 0
    {1,0,0,1,1,0}, // 1
    {1,0,0,0,1,0}, // 2
    {0,1,0,0,0,1}, // 3
    {0,1,1,0,0,1}, // 4
    {0,0,0,1,1,0}  // 5
    };

    int start = 0;
    int goal = 5;

    printPath(findSocialPath(adjMatrix, start, goal));

}