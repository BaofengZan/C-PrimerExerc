/*
 * @Author: your name
 * @Date: 2020-05-26 13:59:30
 * @LastEditTime: 2020-05-26 16:48:53
 * @LastEditors: Please set LastEditors
 * @Description: 环形队列，用数组实现
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueue\MyQueue.h
 */ 

#pragma once
#include <iostream>

template<typename T>
class MyQueue
{
public:
    MyQueue(int capacity); // 创建队列
    virtual ~MyQueue(); //  销毁队列
    void ClearQueue(); // 清空
    bool IsEmpty() const;
    bool IsFull() const;
    int QueueLength() const; 
    bool EnQueue(T element); //入队
    T DeQueue(); //出队
    void QueueTraverse(); //遍历输出

private:
    int m_iQueueLen; // 元素个数 
    int m_iQueueCapacity; // 元素容量（最大个数）
    int m_iHead;  
    int m_iTail;  
    T *m_pQueue; // 队列数组指针
};

template<typename T>
MyQueue<T>::MyQueue(int capacity)
{   
    m_iQueueCapacity = capacity;
    m_pQueue = new int[m_iQueueCapacity];  // 创建数组
    ClearQueue();
}

template<typename T>
MyQueue<T>::~MyQueue()
{
    // 清空
    delete[] m_pQueue;
    m_pQueue = nullptr;
}
template<typename T>
void MyQueue<T>::ClearQueue()
{
    m_iHead = 0;
    m_iTail = 0;
    m_iQueueLen = 0;
}

template<typename T>
bool MyQueue<T>::IsEmpty() const
{
    return m_iQueueLen == 0 ? true : false;
}

template<typename T>
bool MyQueue<T>::IsFull() const
{
    return m_iQueueLen == m_iQueueCapacity ? true : false;
}

template<typename T>
int MyQueue<T>::QueueLength() const
{
    return m_iQueueLen;
}

template<typename T>
bool MyQueue<T>::EnQueue(T element)
{
    // 队列已经满,不允许入队
    if (IsFull())
    {
        /* code */
        return false;
    }
    else
    {
        // 从队尾入队,
        m_pQueue[m_iTail] = element;
        m_iTail++;  // 队尾++
        m_iQueueLen++; // 元素个数++
        m_iTail = m_iTail % m_iQueueCapacity;  //循环队列
        return true;
    }
}

template<typename T>
T MyQueue<T>::DeQueue()
{
    //为空 不允许出队
    if (IsEmpty())
    {
        /* code */
        return false;
    }
    else
    {
        // 从头出队
        int popele = m_pQueue[m_iHead];
        m_iHead++; //队首++，出队的元素下一个成为新的队首元素
        m_iQueueLen--;
        m_iHead = m_iHead % m_iQueueCapacity;
        return popele;
    }  
}
template<typename T>
void MyQueue<T>::QueueTraverse()
{
    // 要循环所有的元素,
    for (int i = m_iHead; i < m_iQueueLen + m_iHead; i++)
    {
        /* code */
        std::cout << m_pQueue[i%m_iQueueCapacity] << std::endl;
    }
    
    // if (m_iQueueLen==0) 
    // {
    //     return;
    // }
    // else
    // {
    //     for (int i = m_iHead; i <= m_iTail; i++)
    //     {
    //         std::cout << m_pQueue[i] << std::endl;
    //     }
        
    // } 
}