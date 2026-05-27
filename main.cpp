#include"Algo.h"
#include<iostream>
using namespace std;

// To print the Path
void printPath(PathNode* head){
    cout << "Solution Path:\n";
    while (head != nullptr) {
        cout << "Node: " << head->name
             << " | f: " << head->f
             << " | g: " << head->g
             << " | h: " << head->h << "\n";
        head = head->next;
    }
}

int main() {
    cout << "=== RUNNING TEST CASE 1: findSocialPath (10x10) ===" << endl;
    
    double socialMatrix[100][100] = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    printPath(findSocialPath(socialMatrix, 0, 9));

    cout << "=== RUNNING TEST CASE 2: findDronePath (10x10) ===" << endl;
    
    double rawDrone[10][10] = {
        {-1, 2.5, 4.0, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 3.0, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, 3.5, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, 2.0, -1, 4.5, -1, -1, -1},
        {-1, -1, -1, -1, -1, 3.0, -1, 4.0, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, 3.2, -1},
        {-1, -1, -1, -1, -1, -1, -1, 3.0, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, 3.8},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, 2.9},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    
    double droneMatrix[100][100];
    for(int i=0; i<100; i++) {
        for(int j=0; j<100; j++) droneMatrix[i][j] = (i < 10 && j < 10) ? rawDrone[i][j] : -1;
    }

    int droneCoords[100][2] = {{0,0}, {2,1}, {1,4}, {4,2}, {5,5}, {3,8}, {7,3}, {8,6}, {6,9}, {10,10}};

    printPath(findDronePath(droneMatrix, droneCoords, 0, 9, 1));

    cout << "=== RUNNING TEST CASE 3: findWarehousePath (9x9) ===" << endl;
    
    int warehouseGrid[100][100] = {
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    printPath(findWarehousePath(warehouseGrid, 9, 9, 0, 0, 8, 8, 1));


    cout << "=== RUNNING TEST CASE 4: findPathInMaze2 (10x10) ===" << endl;

    int floorPlan[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 1, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
    };

    double weightMatrix[100][100] = {0};


    printPath(findPathInMaze2(floorPlan, 10, 10, 0, 0, 9, 9, weightMatrix, 1));

    return 0;
}