
/*
 * @Author: your name
 * @Date: 2020-05-15 22:42:56
 * @LastEditTime: 2020-05-16 20:32:00
 * @LastEditors: Please set LastEditors
 * @Description: 完美转发
 * @FilePath: \vscodeCMakeTmplate\Project\PerfectForwarding\PerfectForwarding.cpp
 */ 

#include <iostream>
#include <cstring>
#include <vector>
//#define  FirstDemo
#define  SecondDemo



#ifndef  FirstDemo
void process(int& i)  // 形参为左值引用
{
    std::cout << "process(int& i): " << i << std::endl;    
}

void process(int&& i)  // 形参为右值引用
{
    std::cout << "process(int&& i): " << i << std::endl;    
}

void myforward(int&& i)  // 右值引用
{
    std::cout << "myforward(int&& i): " << i << std::endl;   
    process(i);  
}

void myforward2(int&& i){ // 形参为右值引用
    std::cout << "myforward2(int&&):" << i << std::endl;
    process(std::forward<int>(i));  // 
}

int main0()
{
    int a = 10;
    process(a); // a为左值， 调用 process(int& i) 
    process(1); // 1为右值。调用  process(int&& i)
    process(std::move(a)); // 将左值a转为右值，调用  process(int&& i)
    myforward(11); // 1为右值，经过myforward函数后，变为左值传递到process函数中， 调用 process(int& i)

    myforward(std::move(a));   // 同上。

    return 0;
}

#endif

#ifdef SecondDemo

using namespace std;

void RunCode(int &&m) {
    cout << "rvalue ref" << endl;
}
void RunCode(int &m) {
    cout << "lvalue ref" << endl;
}
void RunCode(const int &&m) {
    cout << "const rvalue ref" << endl;
}
void RunCode(const int &m) {
    cout << "const lvalue ref" << endl;
}

// 这里利用了universal references，如果写T&,就不支持传入右值，
// 而写T&&，既能支持左值，又能支持右值
// 同时，T是推断出来的，因此是通用引用
template<typename T>
void perfectForward(T && t) {
    RunCode(forward<T> (t)); 
}

template<typename T>
void notPerfectForward(T && t) {
    RunCode(t);
}

int main()
{
    int a = 0; // a为左值
    int b = 0; // b为左值
    const int c = 0;  // c为 const 左值
    const int d = 0;

    
    //知识点：
    //当右值引用和模板结合的时候，就复杂了。
    //T&& 并不一定表示右值引用，它可能是个左值引用又可能是个右值引用
    //T&& 即可以接受左值，又可以接受右值，此时T&&为未定义的引用类型。称为universal references(通用引用)，
    //它必须被初始化，它是左值引用还是右值引用却决于它的初始化
    
    notPerfectForward(a); // a为左值，T被推断为int 因此形参为int&& 接受左值。因此t为左值，调用 RunCode(int &m)函数
    notPerfectForward(move(b)); // b为左值，move将其转为右值，形参为int&& 作为右值引用，int&& t = 0; //t实质上为左值，调用调用 RunCode(int &m)函数
    
    // universal references仅仅发生在 T&& 下面，任何一点附加条件都会使之失效
    notPerfectForward(c); // c为const 左值， T&& t 接受的是左值，调用void RunCode(const int &m)
    notPerfectForward(move(d)); //左值转为右值，T&& t = d;  调用void RunCode(const int &m) 

    cout << endl;
    perfectForward(a); 
    // a为左值，T&& 接受左值，T被推断为int& 
    //T&&-> int&&& -->int&
    //forward<T> --> forward<int&>  --> forward<int&>最后返回 int& 左值，因此调用RunCode(int &m)

    perfectForward(move(b)); // rvalue ref
    // b为左值，move转为右值，T&&接受右值，T被推断为int
    // T&&-->int&&
    //forward<T> --> forward<int>  --> forward<int>最后返回 int&& 接受右值，因此调用RunCode(int&& m)


    // 下面的两个分析同上，只是加上const
    perfectForward(c); // const lvalue ref
    perfectForward(move(d)); // const rvalue ref
}


#endif