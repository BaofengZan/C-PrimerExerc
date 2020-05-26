/*
 * @Author: your name
 * @Date: 2020-05-26 16:40:09
 * @LastEditTime: 2020-05-26 16:49:45
 * @LastEditors: Please set LastEditors
 * @Description: 类模板的声明和实现要放在一起,否则编译报错,找不到实现
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueueTemplate\CircularQueue.cpp
 */ 

#include <iostream>
#include "MyQueue.h"

int main()
{
    MyQueue<int> Q(4);
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