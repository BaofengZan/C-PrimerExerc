/*
 * @Author: BaofengZan
 * @Date: 2020-05-16 21:45:41
 * @LastEditTime: 2020-05-16 22:01:46
 * @LastEditors: Please set LastEditors
 * @Description: emplace_back 和 push_back
 * @FilePath: \vscodeCMakeTmplate\Project\emplaceback\emplaceback.cpp
 */ 

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class A {
public:
    A(int i){
        cout << "构造函数： A()" << endl;
        str = to_string(i);
    }
    ~A(){}
    A(const A& other): str(other.str){
        cout << "拷贝构造：A&" << endl;
    }

public:
    string str;
};

int main()
{
    vector<A> vec;
    vec.reserve(10);
    for(int i=0;i<10;i++){
        vec.push_back(A(i)); //调用了10次拷贝构造函数
    }  

    cout << "empalce_back()...." << endl;
    vector<A> vec2;
    vec2.reserve(10);
   for(int i=0;i<10;i++)
    {
       vec2.emplace_back(i);  //一次拷贝构造函数都没有调用过
    }
}

