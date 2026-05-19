#include "main.h"
#include "Algo.h"

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

// Task 1 — Degrees of Separation in a Social Network:
PathNode* findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson){

    // BFS to find heuristic cost

    vector<int> queue;
    vector<int> h(100, INT_MAX);
    
    h.at(goalPerson) = 0;
    int node = goalPerson;
    queue.push_back(goalPerson);

    while(!queue.empty()){
        int node = queue.front();
        queue.erase(queue.begin());
    
        for(int next = 0; next < 100; next++){
            if (adjMatrix[node][next] == 1){
                int tempCost = h[node] + 1;
                if (tempCost < h[next]){
                    h[next] = tempCost;
                    queue.push_back(next);
                }
            }   
        }
    }

    
    //A* algo
    vector<int> g(100,INT_MAX);
    vector<int> f(100,INT_MAX);
    vector<int> previous(100,-1);

    node = startPerson;
    queue.push_back(startPerson);
    g.at(startPerson) = 0;
    f.at(startPerson) = h.at(startPerson);
    while (!queue.empty()){


        int min = INT_MAX;
        int minIndex = 0;
        for (int i =0; i < queue.size(); i++){
            if(f[queue.at(i)] < min){
                min = f[queue.at(i)];
                node = queue.at(i);
                minIndex = i;
            }
        }
        if(min == INT_MAX) return nullptr;
        if(node == goalPerson){
            break;
        }
        queue.erase(queue.begin() + minIndex);


        //Cost mới = cost đường đi + cost heu

        for (int next = 0; next < 100; next++){
            if(adjMatrix[node][next] == 1){
                int tempCost = g[node] + 1;
                if(tempCost < g[next]){
                    g[next] = tempCost;
                    f[next] = g[next] + h[next];
                    queue.push_back(next);
                    previous[next] = node;
                }
            }
        }
    }

    //Create the Path
    PathNode* NodeList = new PathNode(to_string(goalPerson), f[goalPerson], g[goalPerson], h[goalPerson], nullptr);

    int pre = previous[goalPerson];
    while (pre != startPerson && pre != -1){
        NodeList = insertHead(NodeList, to_string(pre), f[pre], g[pre], h[pre]);
        pre = previous[pre];
    }
    
    // Thêm node bắt đầu (startPerson) vào đầu danh sách
    if (startPerson != goalPerson) {
        NodeList = insertHead(NodeList, to_string(pre), f[pre], g[pre], h[pre]);
    }
    
    return NodeList;
}










double ManhattanDistance(int coords[100][2], int node1, int node2){
    return abs(coords[node1][0] - coords[node2][0]) + abs(coords[node1][1] - coords[node2][1]);
}

double EuclideanDistance(int coords[100][2], int node1, int node2){
    return pow(pow((coords[node1][0] - coords[node2][0]),2) + pow((coords[node1][1] - coords[node2][1]),2), 0.5);
}

double ChebyshevDistance(int coords[100][2], int node1, int node2){
    return max((coords[node1][0] - coords[node2][0]),(coords[node1][1] - coords[node2][1]));
}



void MODE1(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    vector<int> queue;
    h.at(goalPoint) = 0;
    queue.push_back(goalPoint);
    while(!queue.empty()){

        int node = queue.back();
        queue.pop_back();
        for(int next = 0; next < 100; next ++){
            if (adjMatrix[node][next] <= 0) continue;
            double temp = h[node] + ManhattanDistance(coords,node,next);
            if (temp < h[next]){
                h[next] = temp;
                queue.push_back(next);
            }
        }
    }
}

void MODE2(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    vector<int> queue;
    h.at(goalPoint) = 0;
    queue.push_back(goalPoint);
    while(!queue.empty()){

        int node = queue.back();
        queue.pop_back();
        for(int next = 0; next < 100; next ++){
            if (adjMatrix[node][next] <= 0) continue;
            double temp = h[node] + EuclideanDistance(coords,node,next);
            if (temp < h[next]){
                h[next] = temp;
                queue.push_back(next);
            }
        }
    }
}

void MODE3(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    vector<int> queue;
    h.at(goalPoint) = 0;
    queue.push_back(goalPoint);
    while(!queue.empty()){

        int node = queue.back();
        queue.pop_back();
        for(int next = 0; next < 100; next ++){
            if (adjMatrix[node][next] <= 0) continue;
            double temp = h[node] + ChebyshevDistance(coords,node,next);
            if (temp < h[next]){
                h[next] = temp;
                queue.push_back(next);
            }
        }
    }
}




//Task 2
PathNode* findDronePath(double adjMatrix[100][100], int coords[100][2],
int startPoint, int goalPoint, int mode){

    // Location of node => (coords[node][0]; coords[node][1]);
    vector<double> h(100,DBL_MAX);
    vector<double> g(100,DBL_MAX);
    vector<double> f(100,DBL_MAX);
    vector<int> previous(100,-1);
    
    // =======================PHASE 1================================
    // EVALUATE THE HEURISTIC COST:
    if (mode == 1){MODE1(adjMatrix,coords,startPoint,goalPoint,h);}
    else if (mode == 2){ MODE2(adjMatrix,coords,startPoint,goalPoint,h);}
    else if (mode == 3){MODE3(adjMatrix,coords,startPoint,goalPoint,h);}
    
    // =======================PHASE 2================================
    // EVLUATE THE ACTUAL COST
    
    vector<int> queue;
    queue.push_back(startPoint);
    g.at(startPoint) = 0;
    f.at(startPoint) = h.at(startPoint);

    while(!queue.empty()){


        double min = f[queue.at(0)];
        int minIndex = 0;
        for(int i = 0; i < queue.size(); i++){
            if (f[queue.at(i)] < min){
                min = f[queue.at(i)];
                minIndex = i;
            }
        }

        int node = queue.at(minIndex);
        if (node == goalPoint) break;
        if (min >= DBL_MAX) return nullptr;
        queue.erase(queue.begin() + minIndex);


        for(int next = 0; next < 100; next++){
            if(adjMatrix[node][next] <= 0) continue;

            double cost = g[node] + adjMatrix[node][next];
            if (cost < g[next]){
                g[next] = cost;
                f[next] = g[next] + h[next];
                previous[next] = node;
                queue.push_back(next);
            }
        }
    }

    // =======================PHASE 3================================
    // CREATE NODE PATH
    
    PathNode* NodeList = new PathNode(to_string(goalPoint),f[goalPoint],g[goalPoint],h[goalPoint],nullptr);
    int pre = goalPoint;

    while (pre != startPoint){
        pre = previous[pre];
        if (pre == -1) return nullptr;
        insertHead(NodeList,to_string(pre),f[pre],g[pre],h[pre]);
    }

    return NodeList;
}


double ManhattanDistance(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

double ChebyshevDistance(int x1, int y1, int x2, int y2){
    return max((x1 - x2), abs(y1 - y2));
}




int TrackBack(int nodeX, int nodeY, int nextX, int nextY){
    bool left = false;
    bool right = false;
    bool down = false;
    bool up = false;

    left = nextX - nodeX < 0 ? true : false;
    right = nextX - nodeX > 0 ? true : false;
    down = nextY- nodeY < 0 ? true : false;
    up = nextY - nodeY > 0 ? true : false;

    // sẽ lưu kiểu 1->8 ô xung quanh; 
    
    // 1   2   3
    // 8       4
    // 7   6   5
    
    if ( left && down) return 7;
    else if (left && up) return 1;
    else if (left && !down && !up) return 8;
    else if (right && down) return 5;
    else if (right && up) return 3;
    else if (right && !up && !down) return 4;
    else if (!left && !right && up) return 2;
    else if (!left && !right && down) return 6;
    return 0;
}

vector<vector<int>> Neighbor(int X, int Y){
    vector<vector<int>> neighbor;

    for (int x = -1 ; x < 2;x++){
        for(int y =-1 ; y < 2;y++){
            if (x == 0 && y == 0) continue;
            if (X + x < 0 || Y + y < 0) continue;
            neighbor.push_back([X + x, Y + y]);
        }
    }
    return neighbor;
}


string toString(int direction){
    switch (direction){
        case 1 : return "Up-Left";
        case 2 : return "Up";
        case 3 : return "Up-Right";
        case 4 : return "Right";
        case 5 : return "Down-Right";
        case 6 : return "Down";
        case 7 : return "Down-Left";
        case 8 : return "Left";
    }
    return "";
}




//Task 3 — Warehouse Robot Navigation with Obstacles:
PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
int startY, int goalX, int goalY, int mode){


    vector<vector<double>> f(100,vector<double>(100,DBL_MAX));
    vector<vector<double>> g(100,vector<double>(100,DBL_MAX));
    vector<vector<double>> h(100,vector<double>(100,DBL_MAX));

    vector<vector<int>> previous(100,vector<int>(100,-1)); 
    vector<vector<int>> queue;
    
    
    
    queue.push_back([startX,startY]);  // Sẽ có minIndex = 0 và min coords;
    f[startX][startY] = h[startX][startY];
    g[startX][startY] = 0;
    
    
    h[startX][startY] = (mode == 1? ManhattanDistance(startX,startY,goalX,goalY) : ChebyshevDistance(startX,startY,goalX,goalY)); 

    // ================MERGE HEURISTIC AND COST INTO 1 PHASE============
    while(!queue.empty()){
        
        int minIndex = 0;
        int min = f[queue[0][0]][queue[0][1]];
        
        for(int i = 0; i < queue.size(); i++){
            if( f[queue[i][0]][queue[i][1]] < min ){
                min = f[queue[i][0]][queue[i][1]];
                minIndex = i;
                
            }
        }

        int nodeX = queue[minIndex][0];
        int nodeY = queue[minIndex][1];
        queue.erase(queue.begin() + minIndex); // Soon exit
        
        
        
        if (min == DBL_MAX) return nullptr;
        if (nodeX == goalX && nodeY == goalY) break;
        
        vector<vector<int>> neighbor = Neighbor(nodeX,nodeY);
        for (int i = 0; i < neighbor.size() ; i ++ ){
            int nextX = neighbor[i][0];
            int nextY = neighbor[i][1];
            
            
            if (warehouse[nextX][nextY] == 1) continue;
            double temp = g[nodeX][nodeY] + (ManhattanDistance(nodeX,nodeY,nextX,nextY) == 1 ? 1 : 1.5 );
            
            
            if(temp < g[nextX][nextY]){
                g[nextX][nextY] = temp;
                f[nextX][nextY] = g[nextX][nextY] + (mode == 1 ? ManhattanDistance(nodeX,nodeY,nextX,nextY) : ChebyshevDistance(nodeX,nodeY,nextX,nextY));
                
                previous[nextX][nextY] = TrackBack(nodeX,nodeY,nextX,nextY);
                // sẽ lưu kiểu 1->8 ô xung quanh; 
                
                // 1   2   3
                // 8       4
                // 7   6   5
                
                queue.push_back([nextX,nextY]);
            }
        }
    }


    // =====================ADD TO PATH=======================
    PathNode* NodeList = createPathNode("GOAL",f[goalX][goalY],g[goalX][goalY],h[goalX][goalY]);

    while(previous != -1 || previous == start ....){

        insertHead(toString(previous[preX][preY]),f,g,h);
        
        int preX...
        int preY...
    }

    return NodeList;


}