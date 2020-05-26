/*
 * @Author: your name
 * @Date: 2020-05-26 13:59:30
 * @LastEditTime: 2020-05-26 15:40:54
 * @LastEditors: Please set LastEditors
 * @Description: 环形队列，用数组实现
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueue\MyQueue.h
 */ 

#pragma once
#include <iostream>

class MyQueue
{
public:
    MyQueue(int capacity); // 创建队列
    virtual ~MyQueue(); //  销毁队列
    void ClearQueue(); // 清空
    bool IsEmpty() const;
    bool IsFull() const;
    int QueueLength() const; 
    bool EnQueue(int element); //入队
    int DeQueue(); //出队
    void QueueTraverse(); //遍历输出

private:
    int m_iQueueLen; // 元素个数 
    int m_iQueueCapacity; // 元素容量（最大个数）
    int m_iHead;  
    int m_iTail;  
    int *m_pQueue; // 队列数组指针
};