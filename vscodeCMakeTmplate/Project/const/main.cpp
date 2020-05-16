/*
 * @Author: your name
 * @Date: 2020-05-11 17:19:23
 * @LastEditTime: 2020-05-15 22:49:32
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\const\main.cpp
 */ 
#include <iostream>

#define N 10;

extern int noconst_a;
extern const int const_b;
extern const int const_c;
int main()
{
    std::cout << noconst_a << std::endl;
    //std::cout << const_b << std::endl;
    std::cout << const_c << std::endl;
    return 0;
}