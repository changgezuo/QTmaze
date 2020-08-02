#include"MazeStack.h"

bool MazeStack::isEmpty(){
    if(front==bottom)
        return true;
    return false;
}

bool MazeStack::Push(Maze m){

    Node*temp;
    temp=front;
    front=new Node();
    if(!front)return false;
    top->data=m;
    top->next=temp;
