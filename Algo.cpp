#include "main.h"
#include "Algo.h"

using namespace std;

vector<vector<int>> Neighbor(int X, int Y, int m, int n);
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
            if (adjMatrix[next][node] == 1){
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
    return max(abs(coords[node1][0] - coords[node2][0]),abs(coords[node1][1] - coords[node2][1]));
}




void MODE1(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    for(int i =0; i < 100 ;i ++){
        h[i] = ManhattanDistance(coords,i,goalPoint);
    }
}

void MODE2(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    for(int i =0; i < 100 ;i ++){
        h[i] = EuclideanDistance(coords,i,goalPoint);
    }
}

void MODE3(double adjMatrix[100][100] ,int coords[100][2], int startPoint, int goalPoint, vector<double>& h){
    for(int i =0; i < 100 ;i ++){
        h[i] = ChebyshevDistance(coords,i,goalPoint);
    }
}


string toCoord(int coords[100][2], int point){
    string name = "(" + to_string(coords[point][0]) + "," + to_string(coords[point][1]) + ")";
    return name;
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
    vector<bool> visited(100, false);
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
            else if (f[queue.at(i)] == min){
                if (h[queue.at(i)] < h[queue.at(minIndex)]) {
                    minIndex = i;
                }
            }
        }
        
        int node = queue.at(minIndex);
        visited[node] = true;

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
                if (visited[next] == false){
                    queue.push_back(next);
                }
            }
        }
    }

    // =======================PHASE 3================================
    // CREATE NODE PATH
    
    PathNode* NodeList = new PathNode(toCoord(coords,goalPoint),f[goalPoint],g[goalPoint],h[goalPoint],nullptr);
    int pre = goalPoint;

    while (pre != startPoint){
        pre = previous[pre];
        if (pre == -1) return nullptr;
        insertHead(NodeList,toCoord(coords,pre),f[pre],g[pre],h[pre]);
    }

    return NodeList;
}



double ManhattanDistance(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

double ChebyshevDistance(int x1, int y1, int x2, int y2){
    return max(abs(x1 - x2), abs(y1 - y2));
}

int TrackBack(int nodeX, int nodeY, int nextX, int nextY){

    bool up    = nextX < nodeX;
    bool down  = nextX > nodeX;
    bool left  = nextY < nodeY;
    bool right = nextY > nodeY;

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


int PreX(int X, int pos){
    switch(pos){
        case 1: return X + 1;
        case 2: return X + 1;
        case 3: return X + 1;
        case 4: return X;
        case 5: return X - 1;
        case 6: return X - 1;
        case 7: return X - 1;
        case 8: return X;
    }
    return X;
}

int PreY(int Y, int pos){
    switch(pos){
        case 1: return Y + 1;
        case 2: return Y;
        case 3: return Y - 1;
        case 4: return Y - 1;
        case 5: return Y - 1;
        case 6: return Y;
        case 7: return Y + 1;
        case 8: return Y + 1;
    }
    return Y;
}



//Task 3 — Warehouse Robot Navigation with Obstacles:
PathNode* findWarehousePath(int warehouse[100][100], int m, int n, int startX,
int startY, int goalX, int goalY, int mode){


    vector<vector<double>> f(100,vector<double>(100,DBL_MAX));
    vector<vector<double>> g(100,vector<double>(100,DBL_MAX));
    vector<vector<double>> h(100,vector<double>(100,DBL_MAX));

    vector<vector<int>> previous(100,vector<int>(100,-1)); 
    vector<vector<int>> queue;
    vector<vector<bool>> visited(100, vector<bool>(100, false));
    
    
    
    g[startX][startY] = 0;
    
    h[startX][startY] =
    (mode == 1 ? ManhattanDistance(startX,startY,goalX,goalY): ChebyshevDistance(startX,startY,goalX,goalY));
    h[goalX][goalY] = 0;
    f[startX][startY] = g[startX][startY] + h[startX][startY];
    
    queue.push_back({startX,startY});  // Sẽ có minIndex = 0 và min coords;
    // ================MERGE HEURISTIC AND COST INTO 1 PHASE============
    while(!queue.empty()){
        
        int minIndex = 0;
        double min = f[queue[0][0]][queue[0][1]];
        
        for(int i = 0; i < queue.size(); i++){
            if( f[queue[i][0]][queue[i][1]] < min ){
                min = f[queue[i][0]][queue[i][1]];
                minIndex = i; 
            }
            else if (f[queue[i][0]][queue[i][1]] == min ){
                if( g[queue[i][0]][queue[i][1]] < g[queue[minIndex][0]][queue[minIndex][1]]){
                    minIndex = i;
                }
                else if(g[queue[i][0]][queue[i][1]] == g[queue[minIndex][0]][queue[minIndex][1]]){
                    if (h[queue[i][0]][queue[i][1]] < h[queue[minIndex][0]][queue[minIndex][1]]){
                        minIndex = i;
                    }
                }
            }
        }

        int nodeX = queue[minIndex][0];
        int nodeY = queue[minIndex][1];
        queue.erase(queue.begin() + minIndex); // Soon exit
        if (nodeX == goalX && nodeY == goalY) break;
        if (visited[nodeX][nodeY] == true) continue; // Bỏ qua node này khi đã discover rồi

        // Không tồn tại đường đi tới đó nữa
        if (min == DBL_MAX) return nullptr;
        visited[nodeX][nodeY] = true;

        vector<vector<int>> neighbor = Neighbor(nodeX,nodeY,m,n);
        
        for (int i = 0; i < neighbor.size() ; i ++ ){
            int nextX = neighbor[i][0];
            int nextY = neighbor[i][1];
            
            
            if (warehouse[nextX][nextY] == 1) continue;
            if (visited[nextX][nextY]) continue;

            double movecost = (ManhattanDistance(nodeX,nodeY,nextX,nextY) == 1 ? 1 : 1.5 );
            double temp = g[nodeX][nodeY] + movecost;
            
            
            if(temp < g[nextX][nextY]){
                g[nextX][nextY] = temp;
                h[nextX][nextY] = mode == 1 ? ManhattanDistance(goalX,goalY, nextX,nextY) : ChebyshevDistance(goalX,goalY,nextX,nextY);
            
                f[nextX][nextY] = g[nextX][nextY] + h[nextX][nextY];
                
                previous[nextX][nextY] = TrackBack(nodeX,nodeY,nextX,nextY);
                // sẽ lưu kiểu 1->8 ô xung quanh; 
                
                // 1   2   3
                // 8       4
                // 7   6   5
                queue.push_back({nextX,nextY});
            }
        }
    }


    // =====================ADD TO PATH=======================
    if(f[goalX][goalY] == DBL_MAX) return nullptr;
    PathNode* NodeList = createPathNode("GOAL",f[goalX][goalY],g[goalX][goalY],h[goalX][goalY]);

    int preX = goalX;
    int preY = goalY;

    while(previous[preX][preY] != -1){
        insertHead(NodeList, toString(previous[preX][preY]),f[preX][preY],g[preX][preY],h[preX][preY]);
        int tempDirection = previous[preX][preY]; 
        preX = PreX(preX, tempDirection);
        preY = PreY(preY, tempDirection);
    }
    
    deleteTail(NodeList);
    
    return NodeList;
}




// ==================================TASK 4 =================================


double moveCost(int X1, int Y1, int X2, int Y2){
    double absX = abs(X1 - X2);
    double absY = abs(Y1 - Y2);
    double min = absX > absY ? absY : absX; 
    double max = absX > absY ? absY : absX;

    if (min == 0) return 1*max;
    else{
        return min * 1.5 + (max - min) * 1;
    }
    return 0;
}


vector<vector<int>> Neighbor(int X, int Y, int m, int n){
    vector<vector<int>> neighbor;

    for (int x = -1 ; x < 2;x++){
        for(int y =-1 ; y < 2;y++){
            if (x == 0 && y == 0) continue;
            if (X + x < 0 || Y + y < 0 || X + x >= m || Y + y >= n) continue;
            neighbor.push_back({(X + x),(Y + y)});
        }
    }
    return neighbor;
}




PathNode* findEvacuationPath(int floorPlan[100][100], int m, int n, int startX,
int startY, int exitX, int exitY, double weightMatrix[100][100], int mode){

    vector<double> h(100, DBL_MAX);
    // Tạo weight matrixx
    int range = m*n;
    int start, end;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            
            int currX = i;
            int currY = j;
            int coordCurrent = currX * m + currY;
            h[coordCurrent] = mode == 1 ? ManhattanDistance(currX,currY,exitX,exitY) : ChebyshevDistance(currX,currY,exitX,exitY);
            if (currX == startX && currY == startY){
                start = coordCurrent;
            }
            else if (currX == exitX && currY == exitY){
                end = coordCurrent;
                h[end] = 0;
            }
            
            
            vector<vector<int>> neighbor = Neighbor(currX,currY,m,n);
            for (vector<int> next : neighbor){
                int nextX = next[0];
                int nextY = next[1];
                int coordNext = nextX * m + nextY;
                double cost = moveCost(currX,currY,nextX,nextY);
                weightMatrix[coordCurrent][coordNext] = cost;
                
                // Để cộng theo mảng chiều ngang

            }
            // Cộng phần tử mảng chiều dọc
            // Bổ sung phần heuristic cost vào ở đây luôn

        }
    }

    if (start == end) return nullptr;

    // Sử dụng dijkstra như bình thường


    // Init data
    vector<double> g(100, DBL_MAX);
    vector<double> f(100, DBL_MAX);
    vector<int>    previous(100,-1);
    vector<int> queue;
    vector<bool> visited;


    f[start] = h[start];
    g[start] = 0;
    queue.push_back(start);

    while(!queue.empty()){
        // Lấy phần tử đầu tiên của queue.
        
        double min = f[queue[0]], minIndex = 0;
        for (int index  =0; index < queue.size() ; index++){
            if( min >   f[queue[index]]){
                min = f[queue[index]];
                minIndex = index;
            }
        }
        
        int current = queue[minIndex];
        if (current == end) break; 
        if (f[current] == DBL_MAX) return nullptr;
        queue.erase(queue.begin() + minIndex);



        for(int next = 0; next < range; next ++){
            if (weightMatrix[current][next] == 0) continue;
            double temp = g[current] + weightMatrix[current][next];
            if (temp  < g[next]){
                g[next] = temp;
                f[next] = temp + h[next];
                previous[next] = current;
                queue.push_back(next);
            }
        }
    }

        
    


    // Create node path
    PathNode* NodeList = new PathNode(to_string(end),f[end],g[end],h[end],nullptr);
    int pre = end;
    while(pre != start){
        pre = previous[pre];
        insertHead(NodeList,to_string(pre), f[pre], g[pre], h[pre]);
    }

    return NodeList;

}






























