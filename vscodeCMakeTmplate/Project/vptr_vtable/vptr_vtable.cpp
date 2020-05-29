/*
 * @Author: your name
 * @Date: 2020-05-27 22:27:28
 * @LastEditTime: 2020-05-28 17:50:49
 * @LastEditors: Please set LastEditors
 * @Description: 虚函数表  虚函数  多态调用
 * @FilePath: \vscodeCMakeTmplate\Project\vptr_vtable\vptr_vtable.cpp
 */ 
#include <iostream>

class Base
{
public:
    Base() {}  //构造
    virtual void func1()
    {
        std::cout << "Base::func1()" << std::endl;
    }

    virtual void func2()
    {
        std::cout << "Base::func2()" << std::endl;
    }
    virtual void func3()
    {

    }
    ~Base(){};
private:
};


class Derived:public Base
{
public:
    Derived() {};
    ~Derived() {};

    void func1()
    {
        std::cout << "Derived:func1()`" <<std::endl;
    }

    void func2()
    {
        std::cout <<  "Derived::func2()" << std::endl;
    }
};
int main()
{
    Base ptr;
    Derived d;

    Base* pt = new Derived();
    
    std::cout << "基类对象直接调用虚函数" << std::endl;
    ptr.func1();   // 调用的是基类的函数

    std::cout << "基类引用指向基类实例，调用虚函数" << std::endl;
    Base& pp = ptr;  
    pp.func1();   // 调用的是基类的函数

    std::cout<<"基类指针指向派生类实例并调用虚函数"<<std::endl;
    pt->func1();  // 调用的是子类的函数

    std::cout<<"基类引用指向子类实例并调用虚函数"<<std::endl;
    Base& p = d;
    p.func1();   // 调用的是子类的函数

    return 0;    
}