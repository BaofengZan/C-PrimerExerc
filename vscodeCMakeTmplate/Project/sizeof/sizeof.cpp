/*
 * @Author: your name
 * @Date: 2020-05-25 21:28:20
 * @LastEditTime: 2020-05-25 22:04:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\sizeof\sizeof.cpp
 */ 
#include <iostream>

class A
{};

class B
{
    /*
    静态数据成员被编译器放在程序的一个global data members（全局内存区）中，它是类的一个数据成员，但不影响类的大小。
   不管这个类产生了多少个实例，还是派生了多少新的类，
   静态数据成员只有一个实例。静态数据成员，一旦被声明，就已经存在

   对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针,vptr的大小
    */
    public:
    char b;  // 1  
    virtual void fun(){}; // 8字节 
    static int c;
    static int d;
    static int e;
    static int f;
};

class C
{
    public:
    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};

class D // 公用8
{
    public:
    char a; // 1
    int b; //4
};


/**
此时D1按照顺序：
    char a; // 1
    int b; // 4
    short a; // 2
    long b; // 8

    根据字节对齐： 8 + 8 = 16
 */
class D1 : public D
{
    public:
    short a;
    long b;
};

class E
{
    private:
    D1 a; // 16
    char e; // 1
};

class A1
{
    virtual void fun(){}
};
class C1:public A1
{
};

class A6
{
    virtual void fun() {}
};
class B6
{
    virtual void fun2() {}
};
class C6 : virtual public  A6, virtual public B6  // 虚继承
{
    public:
        virtual void fun3() {}
};

int main()
{
    std::cout << "char: " << sizeof(char) << std::endl; // 1 
    std::cout << "int: " << sizeof(int) << std::endl; // 4
    std::cout << "1: " << sizeof(A) << std::endl;  // 1
    std::cout << "2: " << sizeof(B) << std::endl;  // 16 = 8+8
    std::cout << "3: " << sizeof(C) << std::endl;  // 8
    
    std::cout << "4/5: " << sizeof(D) << std::endl;  // 8
    std::cout << "4/5: " << sizeof(D1) << std::endl;  // 16
    std::cout << "4/5: " << sizeof(E) << std::endl;  //20 = 16+4？

    std::cout << "4/5: " << sizeof(C1) << std::endl;  //8

    std::cout << "6: " << sizeof(A6) << " " << sizeof(B6) << " " << sizeof (C6)<< std::endl;  //8 8 16
    return 0;
}
