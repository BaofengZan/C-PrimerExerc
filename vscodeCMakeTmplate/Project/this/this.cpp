/*
 * @Author: your name
 * @Date: 2020-05-21 12:37:21
 * @LastEditTime: 2020-05-21 12:51:04
 * @L
 * \astEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\this\this.cpp
 */ 
#include<iostream>
#include<cstring>
#include<stdlib.h>

class Person
{
private:
    /* data */
    int age;
    char* name;
public:
    Person(char* n, int a)
    {
        name = new char[strlen(n)+1];
        strcpy(name, n);
        age = a;
    }
    ~Person()
    {
     delete[] name;   
    }
    int get_age() const{
        return this->age;
    }
    Person& fuc()
    {
        return *this;
    }
};


int main()
{

    Person p("xxx", 10);
    std::cout << p.get_age() << std::endl;
    Person pp = p.fuc();
    return 0;
}