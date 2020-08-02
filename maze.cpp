
#include"MazeStack.h"
using namespace std;
 
 
 
void MazeMat::initMaze()//初始化迷宫矩阵
{
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
        {
            matrix[i][j].i=i;
            matrix[i][j].j=j;
            matrix[i][j].state=0;//初始化迷宫矩阵元素为0，即全为墙
        }
 
        mazeStack=new MazeStack();
 
        int a=3;
        EntryPath.clear();//初始化各个路径
        ExitPath.clear();
        FinalPath.clear();
}
 
void MazeMat::createMaze()//产生迷宫矩阵，中间也记录了从初始点到入口、出口的路径
{
    
    int i=4;//初始点设定，注意i,j必须为偶数
    int j=4;
    bool Left=false;//初始化四个方向，false代表可以朝这个方向搜索
    bool Right=false;
    bool Up=false;
    bool Down=false;
 
    matrix[i][j].state=1;//设置初始点是空的，即不是墙
    srand((int)time(0));//产生随机数种子，使得每次运行情况不同
    Maze temp;
 
    temp.i=i;
    temp.j=j;
    temp.state=0;
    int count1=0;
    int num1=0;
   
    
    mazeStack->Push(temp);//将初始点进栈
 
    while(1)//不断循环搜索可行方向，形成迷宫
    {
        
        temp.i=i;
        temp.j=j;
        int randNum=0;
        
        randNum=rand()%4;//0,1,2,3
        
        //我们假设迷宫矩阵的第一个元素(0,0)为入口，最后一个元素（M-1,N-2）为出口
        if(temp.i==0&&temp.j==0)
        {
            EntryPath.clear();
          while(mazeStack->isEmpty() == false)
          {
              
             EntryPath.push_back(mazeStack->GetTop());//获得从初始点到入口的路径
             mazeStack->Pop();
            
          }
          for(int ii=EntryPath.size()-1;ii>=0;ii--)
          {
              mazeStack->Push(EntryPath[ii]);//还原栈
          }
        }
 
        if(temp.i==M-1&&temp.j==N-1)
        {
            ExitPath.clear();
          while(mazeStack->isEmpty() == false)
          {
              
             ExitPath.push_back(mazeStack->GetTop());//获得从初始点到出口的路径
             mazeStack->Pop();
            
          }
          for(int i=ExitPath.size()-1;i>=0;i--)
          {
              mazeStack->Push(ExitPath[i]);//还原栈
          }
        }
 
        switch(randNum)
        {
            
        case 0://向上搜索
            if(Up==false&&i>1&&matrix[i-2][j].state!=1)
            {
                mazeStack->Push(temp);
                matrix[i-1][j].state=1;
                matrix[i-2][j].state=1;
 
                i=i-2;
                Left=false;
                Right=false;
                Up=false;
                Down=false;
            }
            else
                Up=true;
            break;
        case 1://向下搜索
            if(Down==false&&i<M-2&&matrix[i+2][j].state!=1)
            {
                mazeStack->Push(temp);
                matrix[i+1][j].state=1;
                matrix[i+2][j].state=1;
 
                i=i+2;
                Left=false;
                Right=false;
                Up=false;
                Down=false;
            }
            else
                Down=true;
            break;
         case 2://向左搜索
             if(Left==false&&j>1&&matrix[i][j-2].state!=1)
            {
                mazeStack->Push(temp);
                matrix[i][j-1].state=1;
                matrix[i][j-2].state=1;
 
                j=j-2;
                Left=false;
                Right=false;
                Up=false;
                Down=false;
            }
            else
                Left=true;
            break;
         case 3://向右搜索
             if(Right==false&&j<N-2&&matrix[i][j+2].state!=1)
            {
                mazeStack->Push(temp);
                matrix[i][j+1].state=1;
                matrix[i][j+2].state=1;
 
                j=j+2;
                Left=false;
                Right=false;
                Up=false;
                Down=false;
            }
            else
                Right=true;
            break;
        }//end switch
 
        if(Left&&Right&&Up&&Down)   //当上下左右都不可行时，进行回溯
          {
              if(mazeStack->isEmpty()) //回溯完毕，生成迷宫
               {
                    return ;
               }
               else    //进行出栈操作
               {
                    i = mazeStack->GetTop().i;
                    j = mazeStack->GetTop().j;
                    mazeStack->Pop();
                  
                    Left=false;
                    Right=false;
                    Up=false;
                    Down=false;
               }
              
          }
 
    }//end while
 
 
}
 
void MazeMat::displayMaze()//显示迷宫
{
    
     matrix[0][0].state = matrix[M-1][N-1].state = 2;//2表示入口和出口
     for(int i=0;i<FinalPath.size();i++)
     {
         matrix[FinalPath.at(i).i][FinalPath.at(i).j].state=3;//3表示可达路径点
     }
     cout<<"左上角为入口，右下角为出口，oo代表可达路径."<<endl;
     for(int k=0;k<N+2;k++)//在迷宫矩阵的外围墙
         cout<<"■";
     cout<<endl;
     for (int i = 0; i < M; i++)
     {
          cout<<"■";
          for (int j = 0; j <N; j++)
          {
              switch ( matrix[i][j].state )
                {
                   case 0:cout<<"■";break;// 显示墙
                   case 1:cout<<"  ";break;//显示空
                   case 2:cout<<"↘";break;//显示入口和出口
                   case 3:cout<<"oo";break;//显示可达路径
                }
          }
          cout<<"■";
          cout<<endl;
     }
      for(int k=0;k<N+2;k++)
         cout<<"■";
     cout<<endl;
}
 
void MazeMat::FindWay()//寻找可达路径
{
    FinalPath.clear();//清零
    int i=0,j=0;
    
    for(i=EntryPath.size()-1,j=ExitPath.size()-1;i>=0&&j>=0;i--,j--)
    {
        if(EntryPath.at(i).i!=ExitPath.at(j).i||EntryPath.at(i).j!=ExitPath.at(j).j)
        {
            break;
        }
    }
 
    if(i<0)//初始点到出口的路径中经过入口
    {
        for(int k=ExitPath.size()-EntryPath.size()-1;k>=0;k--)
        {
            FinalPath.push_back(ExitPath.at(k));
        }
            
    }
 
    else if(j<0)//初始点到入口的路径中经过出口
    {
        for(int k=EntryPath.size()-ExitPath.size()-1;k>=0;k--)
        {
            FinalPath.push_back(EntryPath.at(k));
        }
    }
 
    else//初始点到入口、出口的路径有部分重叠或则没有重叠
    {
        for(int k=0;k<=i+1;k++)
        {
            FinalPath.push_back(EntryPath.at(k));
        }
 
        for(int k=j;k>=0;k--)
        {
            FinalPath.push_back(ExitPath.at(k));
        }
    }
    
 
