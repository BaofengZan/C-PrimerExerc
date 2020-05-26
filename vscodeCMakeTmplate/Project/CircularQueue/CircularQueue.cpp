/*
 * @Author: Zanbf
 * @Date: 2020-05-26 13:37:32
 * @LastEditTime: 2020-05-26 16:14:49
 * @LastEditors: Please set LastEditors
 * @Description: 环形队列
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueue\CircularQueue.cpp
 */ 
#include <iostream>
#include "MyQueue.h"

int main()
{
    MyQueue Q(4);
    Q.EnQueue(1);
    Q.EnQueue(2);
    Q.EnQueue(3);
    Q.EnQueue(4);
    Q.QueueTraverse();
    std::cout << "=============" << std::endl;
    Q.EnQueue(5);
    Q.QueueTraverse();
    std::cout << "=============" << std::endl;
    //////
    int p = Q.DeQueue();
    std::cout << p << std::endl;

    std::cout << "=============" << std::endl;
    Q.EnQueue(5);
    Q.QueueTraverse();
    
    return 0;
}