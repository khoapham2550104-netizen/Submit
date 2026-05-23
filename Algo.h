#pragma once
#include"PathNode.h"
#include<vector>
// Print
using namespace std;

#define DBL_MAX 1.7976931348623157e+308
// INT_MAX đã được define rồi


void printPath(PathNode* head);
vector<vector<int>> Neighbor(int X, int Y, int m, int n);

//Task 1 — Degrees of Separation in a Social Network:
PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson);

double ManhattanDistance(int coords[100][2], int node1, int node2);
double EuclideanDistance(int coords[100][2], int node1, int node2);
double ChebyshevDistance(int coords[100][2], int node1, int node2);
void MODE1(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h);
void MODE2(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h);
void MODE3(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h);

string toCoord(int coords[100][2], int point);


//Task 2 — Drone Delivery in 2D Space with Three Heuristics:
PathNode* findDronePath(double adjMatrix[100][100], int coords[100][2],
int startPoint, int goalPoint, int mode);
double ManhattanDistance(int x1, int y1, int x2, int y2);
double ChebyshevDistance(int x1, int y1, int x2, int y2);
int TrackBack(int nodeX, int nodeY, int nextX, int nextY);
string toString(int direction);
int PreX(int X, int pos);
int PreY(int Y, int pos);

//Task 3 — Warehouse Robot Navigation with Obstacles:
PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
int startY, int goalX, int goalY, int mode);

double moveCost(int X1, int Y1, int X2, int Y2);
vector<vector<int>> Neighbor(int X, int Y, int m, int n);



//Task 4 — Evacuation Route Planning:
PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, int startX,
int startY, int exitX, int exitY, double weightMatrix[100][100], int mode);


