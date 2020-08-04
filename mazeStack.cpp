#include"MazeStack.h"
#include"assert.h"
bool MazeStack::isEmpty(){
   return front==bottom;
}


void MazeStack::Push(Maze m){
    if(size==0){
        Node*temp=new Node(m);
        size=1;
        front=temp;
        bottom=temp;
    }
    Node*temp=new Node(m);
    temp->next=front;
    front=temp;
    size++;
}

Maze MazeStack::gettop(){
     assert(size);
     return front->data;
}

void MazeStack::pop(){
    assert(size);
    Node*temp=front();
    front=front->next;
    delete temp;
    size--;
    if(!size)bottom=nullptr;
}
