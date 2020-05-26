/*
 * @Author: your name
 * @Date: 2020-05-26 13:59:42
 * @LastEditTime: 2020-05-26 16:14:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueue\MyQueue.cpp
 */ 
#include "MyQueue.h"

MyQueue::MyQueue(int capacity)
{   
    m_iQueueCapacity = capacity;
    m_pQueue = new int[m_iQueueCapacity];  // 创建数组
    ClearQueue();
}
MyQueue::~MyQueue()
{
    // 清空
    delete[] m_pQueue;
    m_pQueue = nullptr;
}
void MyQueue::ClearQueue()
{
    m_iHead = 0;
    m_iTail = 0;
    m_iQueueLen = 0;
}

bool MyQueue::IsEmpty() const
{
    return m_iQueueLen == 0 ? true : false;
}

bool MyQueue::IsFull() const
{
    return m_iQueueLen == m_iQueueCapacity ? true : false;
}

int MyQueue::QueueLength() const
{
    return m_iQueueLen;
}

bool MyQueue::EnQueue(int element)
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

int MyQueue::DeQueue()
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

void MyQueue::QueueTraverse()
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