#pragma once
#include<Maze.h>

class Node {
    Maze data;
    Node* next=nullptr ;
};
class MazeStack
{
public:
   MazeStack() :bottom(nullptr), front(nullptr), Size(0) {}
   ~MazeStack() {}

    bool isEmpty();
    void Push(Maze e);
    Maze GetTop();
    void Pop();

private:
    Node* bottom;
    Node* front;
    int size;
};

