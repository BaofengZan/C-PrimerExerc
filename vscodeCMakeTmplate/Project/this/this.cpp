/*
 * @Author: your name
 * @Date: 2020-05-21 12:37:21
 * @LastEditTime: 2020-05-25 21:13:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\this\this.cpp
 */ 
#include<iostream>                     

class Base
{
public:
    inline virtual void who()
    {
        std::cout << "基类。。。" << std::endl;
    }
};

class Derived : public Base
{
    public:
    inline void who()
    {
        std::cout << "派生类，，，" << std::endl;
    }

};

int main()
{
    Base b;
    b.who(); 

    Base* ptr = new Derived();
    ptr->who();

    //delete ptr;
    //ptr = nullptr;
    return 0;
}