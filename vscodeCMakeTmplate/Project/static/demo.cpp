/*
 * @Author: your name
 * @Date: 2020-05-11 17:35:43
 * @LastEditTime: 2020-05-20 22:30:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\static\demo.cpp
 */ 
#include <iostream>

void demo()
{
    static int count = 0;
    std::cout << count << std::endl;
    count++;
}


class Apple
{
public:
    static int i;
    Apple()
    {

    };
};

class Apple2
{
public:
    int i;
    Apple2()
    {
        i = 0;
        std::cout << "Constructor" << std::endl;
    }
    ~Apple2()
    {
        std::cout << "Destructor" << std::endl;
    }
};

class Apple3
{
public:
    static void printMsg()
    {
        std::cout << "¾²Ì¬³ÉÔ±º¯Êý" << std::endl;
    }
};

int Apple::i =10;
int main()
{

    //// 1
    // for (int i = 0; i < 5; i++)
    // {
    //     /* code */
    //     demo();
    // }
    
    //// 2
    // Apple obj1, obj2;
    // obj1.i = 1;
    // obj2.i = 3;
    // std::cout << obj1.i << " " << obj2.i << std::endl;

    //// 3 
    // { 
    //     Apple2 obj; 
    // } 
    // std::cout << "End of main\n"; 
    // std::cout << "-------------------\n"; 
    // {
    //     static Apple2 obj1;  
    // }
    // std::cout << "End of main2\n";

    //// 4
    Apple3::printMsg();
    return 0;
}