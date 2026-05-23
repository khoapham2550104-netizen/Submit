#define DBL_MAX 1.7976931348623157e+308

struct PathNode {
    string name;
    double f;
    double g;
    double h;
    PathNode* next; // Tạo 1 con trỏ struct chỉ tới Node mới

    PathNode();
    PathNode(string name, double f, double g, double h, PathNode* next);
};

PathNode::PathNode(){
    name = "";
    f = 0;
    g = 0;
    h = 0;
    next = nullptr;
}
PathNode::PathNode(string name, double f, double g, double h, PathNode* next){
    this->name = name;
    this->f = f;
    this->g = g;
    this->h = h;
    this->next = next;
}
PathNode* createPathNode(string name, double f,double g, double h){
    PathNode * newNode = new PathNode(name,f,g,h,nullptr);
    return newNode;
}
PathNode* insertTail(PathNode* &head ,string name, double f, double g, double h){
    PathNode* newNode = new PathNode(name,f,g,h, nullptr);
    PathNode* temp = head; // Init another pointer to keep the head at its position while scanning all the Node
    if (head == nullptr){
        head = newNode;
        return head;
    }

    //Iterate temp to point to the last element
    while (temp->next != nullptr){
        temp = temp->next;
    }
    //Add node to the last element
    temp->next = newNode;
    return head; // Vì pass địa chỉ của ptr head vào nên cũng không cần return, nhưng vẫn cứ ghi
}
PathNode* insertHead(PathNode* &head,string name, double f, double g, double h){
    PathNode* newNode = new PathNode(name, f, g, h, head);
    head = newNode;
    return head;
}

PathNode* deleteTail(PathNode* &head){
    PathNode* temp = head;
    while(temp->next->next){
        temp = temp->next;
    }
    //delete to avoid mem leak
    delete temp->next;
    temp->next = nullptr;
    return head;
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
