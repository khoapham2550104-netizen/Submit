
#include"PathNode.h"
#include"main.h"
using namespace std;
PathNode::PathNode(){
    name = "";
    f = 0;
    g = 0;
    h = 0;
    next = nullptr;
}

PathNode::PathNode(string name, int f, int g, int h, PathNode* next){
    this->name = name;
    this->f = f;
    this->g = g;
    this->h = h;
    this->next = next;
}


PathNode* createPathNode(string name, int f,int g, int h){
    PathNode * newNode = new PathNode(name,f,g,h,nullptr);
    return newNode;
}

PathNode* insertTail(PathNode* &head ,string name, int f, int g, int h){
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

PathNode* insertHead(PathNode* &head,string name, int f, int g, int h){
    PathNode* newNode = new PathNode(name, f, g, h, head);
    head = newNode;
    return head;
}
