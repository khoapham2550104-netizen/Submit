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

double moveCost(int X1, int Y1, int X2, int Y2){
    double absX = abs(X1 - X2);
    double absY = abs(Y1 - Y2);
    double min = absX > absY ? absY : absX; 
    double max = absX < absY ? absY : absX;

    if (min == 0) return 1*max;
    else{
        return min * 1.5 + (max - min) * 1;
    }
    return 0;
}

string toCoord(int value, int m, int n){
    
    int x = value / n;
    int y = value % n;
    string res = "(" + to_string(x) + "," + to_string(y) + ")" ;
    return res;
}

PathNode* findPathInMaze2(int floorPlan[100][100], int m, int n, int startX,
int startY, int exitX, int exitY, double weightMatrix[100][100], int mode = 1){

    vector<double> h(100, DBL_MAX);
    // Tạo weight matrixx
    int range = m*n;
    int start, end;
    // Bước khởi tạo một ma trận trọng số
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            
            int currX = i;
            int currY = j;
            int coordCurrent = currX * n + currY;
            // Công thức chuyển hệ toạ độ thành các node;
            // Sẽ assign thứ tự từ trái sang phải
            // Với ma trận m x n = 3 x 5
                // 0  1  2  3  4 
            // 5  6  7  8  9
            // 10 11 12 13 14

            // Cthuc tổng quát: hàng i cột j
            // i * 5 + j

            // Công thức chuyển đổi lại:
            // Tìm phần dư của Nodes cho 5 (tổng quát là cho n)
            // => X = Nodes / n;
            // => Y = Nodes % n; 

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
                int coordNext = nextX * n + nextY;
          
                double cost = moveCost(currX,currY,nextX,nextY);
                weightMatrix[coordCurrent][coordNext] = cost;
            }

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
    vector<bool> visited(100, false);


    f[start] = h[start];
    g[start] = 0;
    queue.clear();
    queue.push_back(start);
    while(!queue.empty()){
        // Lấy phần tử đầu tiên của queue.
        double min = f[queue[0]], minIndex = 0;
        for (int index  = 1; index < queue.size() ; index++){
            if( min >   f[queue[index]]){
                min = f[queue[index]];
                minIndex = index;
            }
        }
        
        int current = queue[minIndex];
        if (visited[current] == true) continue;
        visited[current] = true;
        if (f[current] == DBL_MAX) return nullptr;
        queue.erase(queue.begin() + minIndex);
        if (current == end) break;

        
        for(int next = 0; next < range; next ++){
            if (weightMatrix[current][next] == 0) continue;
            if (visited[next] == true) continue;
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
    PathNode* NodeList = new PathNode(toCoord(end,m,n),f[end],g[end],h[end],nullptr);
    int pre = previous[end];

    while(pre != -1){
        insertHead(NodeList,toCoord(pre,m,n), f[pre], g[pre], h[pre]);
        pre = previous[pre];
    }

    return NodeList;

}


