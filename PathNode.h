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
    PathNode(string name, int f, int g, int h, PathNode* next);
};


// Create PathNode
PathNode* createPathNode(string name, int f,int g, int h);


// Insert Node to Tail
PathNode* insertTail(PathNode* &head ,string name, int f, int g, int h);


// Insert Node to Head
PathNode* insertHead(PathNode* &head,string name, int f, int g, int h);

















