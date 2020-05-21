/*
 * @Author: your name
 * @Date: 2020-05-11 17:19:23
 * @LastEditTime: 2020-05-20 16:41:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\const\main.cpp
 */ 
#include <iostream>

#define N 10;

extern int noconst_a;
extern const int const_b;
extern const int const_c;

int A = 10000;

const int* f()
{
    const int* p = &A;
    return p;
}


// class Apple
// {
// private:
//     int people[100];
// public:
//     Apple(int i);
//     const int apple_num;
//     const int apple_num2;
// };

// Apple::Apple(int i):apple_num(i)
// {
//     apple_num2 = i;
// }

class Apple
{
private:
    /* data */
    int people[100];
public:
    Apple(int i);

    const int apple_num; // const成员变量
    void take(int num) const;  // 常成员函数
    int add(int num); // 正常函数
    int add(int num) const; // 常成员函数，
    int getCount() const; //常成员函数
    int minus(int num);
};

Apple::Apple(int i):apple_num(i)
{

}

void Apple::take(int num) const
{
    std::cout <<"take const func "<< num << std::endl; 
}
int Apple::add(int num)
{
    std::cout <<"add func " << num << std::endl; 
    take(num);
    return 0;
}
int Apple::add(int num) const
{
    std::cout <<"add const func " << num << std::endl; 
    take(num);
    return 0;
}
int Apple::getCount() const
{
    take(1);
    add(12); 
    return apple_num;
}

int Apple::minus(int num)
{
    std::cout <<"minus func " << num << std::endl; 
    take(num);
    return 0;
}

int main()
{
//     std::cout << noconst_a << std::endl;
//     //std::cout << const_b << std::endl;
//     std::cout << const_c << std::endl;

//     // 指向常量的指针 指向 非const对象
//     const int* ptr;
//     int val = 3;
//     ptr = &val;
//     // *ptr = 100; //error
//     int* ptr1 = &val;
//     *ptr1  = 100;

//     // 常指针
//     // int* const p;
    
//    // int* const p;
//     int* const pp = &val;
//     *pp = 100;  // *p可改变
//     int a = 100;
//    // pp = &a;


    Apple a(22);
    std::cout << "----------------------" << std::endl;
    std::cout << a.getCount() << std::endl;
    std::cout << "----------------------" << std::endl;
    a.add(110);  //调用正常的add
    a.take(100444);  // 非const对象可以调用const成员函数
    std::cout << "----------------------" << std::endl;
    const Apple b(233333);
    std::cout << "----------------------" << std::endl;
    b.add(110);  // 调用const add
    //b.minus(123123); //error const对象不可调用非const的成员函数
    std::cout << "----------------------" << std::endl;
    return 0;
}