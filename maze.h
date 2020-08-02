#pragma once
#include<iostream>
#include<vector>
#include<ctime>

using namespace std;
class Maze {
public:
    int i;
    int j;
    bool state;
};
class MazeStack;

class MazeMat {
public:
    vector<vector<Maze>>matrix;
    vector<Maze>initPath;
    vector<Maze>finPath;
    vector<Maze>lasPath;
    MazeStack* mazeStack;
protected:
    void init(int M=9,int N=9);
    void create();
    void display();
};
