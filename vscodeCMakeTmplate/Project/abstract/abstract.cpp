/*
 * @Author: Zanbf
 * @Date: 2020-05-26 21:39:14
 * @LastEditTime: 2020-05-26 22:02:53
 * @LastEditors: Please set LastEditors
 * @Description: 纯虚函数 抽象类
 * @FilePath: \vscodeCMakeTmplate\Project\abstract\abstract.cpp
 */ 
#include <iostream>

class A
{
    public:
        virtual void f()=0;  // 纯虚函数
        void g() 
        {
            this->f(); //  成员函数内部可以调用纯虚函数
        }
        A(int i)
        {
            //构造函数和析构函数中则不能调用纯虚函数
            //this->f();  // 警告:pure virtual 'virtual void A::f()' called from constructor
            x = i;
        }
    protected:
        int x;
};

class B : public A
{
    public:
        B(int i, int j):A(i)   // 调用基类构造函数
        {
            y = j;
        }
        void f()
        {
            std::cout << "B: f()" << "x = " << x << " y = " << y << std::endl;
        }
    private:
        int y;
};

class A1 : public A
{
    
};
int main()
{
    // 1 纯虚函数使一个类变成抽象类
    //A a; //  error: 不允许使用抽象类类型 "A" 的对象: -- 函数 "A::f" 是纯虚拟函数
    
    // 2 抽象类的指针和引用 可以指向 由抽象类派生出来的类的对象
    A* pa = new B(1, 2);
    pa->f();   // 可以正常输出

    // 3 如果不在派生类中覆盖纯虚函数,那么派生类还是抽象类
    //A1 a1;  // error 不允许使用抽象类类型 "A" 的对象: -- 函数 "A::f" 是纯虚拟函数
    
    // 4 抽象类可以有构造函数
    B bb(12, 34);
    bb.f();


    // B b;
    // b.f();

    return 0;
}