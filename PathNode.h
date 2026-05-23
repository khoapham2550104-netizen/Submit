#pragma once
#include<string>
using namespace std;


struct PathNode {
    string name;
    double f;
    double g;
    double h;
    PathNode* next; // Tạo 1 con trỏ struct chỉ tới Node mới

    PathNode();
    PathNode(string name, double f, double g, double h, PathNode* next);
};


// Create PathNode
PathNode* createPathNode(string name, double f,double g, double h);


// Insert Node to Tail
PathNode* insertTail(PathNode* &head ,string name, double f, double g, double h);

PathNode* deleteTail(PathNode* &head ,string name, double f, double g, double h);


// Insert Node to Head
PathNode* insertHead(PathNode* &head,string name, double f, double g, double h);

















