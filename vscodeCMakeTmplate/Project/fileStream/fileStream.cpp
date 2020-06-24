/*
 * @Author: your name
 * @Date: 2020-06-10 22:35:58
 * @LastEditTime: 2020-06-10 23:17:52
 * @LastEditors: Please set LastEditors
 * @Description: 测试输入输出流
 * @FilePath: \vscodeCMakeTmplate\Project\fileStream\fileStream.cpp
 */

#include <iostream>
using namespace std;
int main()
{
    // char A[50]; // 字符数组
    // std::cout << "请输入string：";
    // std::cin >> A; // cin输入字符串数据时，如果字符串中含有空白就不能完整输入。因为遇到空白字符时，cin就认为字符串结束了。
    // std::cout << A << std::endl;
    /*
    请输入string：hello world
    hello
    */

    // char a, b, c, d;
    // a = std::cin.get(); // get 是获取一个字符
    // b = std::cin.get(); // 并且 空格 回车 也算作字符，
    // std::cout << int(a) << " " << int(b) << std::endl;
    //输入： a [空格]  ->> 97 32

    // cin.get(arrayname,size)  把字符输入到arrayname中，长度不超过size

    //1.输入串长<size，输入串长>arraylength，会自动扩张arrayname大小，使能保存所有数据
    //2.输入串长<size，输入串长<arraylength，把串全部输入，后面补‘\0’
    //3.输入串长>size，先截取size个字符，若还是大于arraylength，则输入前arraylength个字符
    //4.输入串长>size，先截取size个字符，若小于arraylength，则把截取串放入数组中，最后补充‘\0’
    
    char a3[5];
    char bb;
    cin.get(a3, 10);
    bb = cin.get(); //接受回车 (换行符的ascii 为10)
    cout << a3 << endl;
    cout << sizeof(a3) << endl; // 一直是 定义时的大小
     cout << int(bb)<< endl;

    // int i;
    // char e[10];
    // cin.get(e, 8, ',');
    // cout << e;

    // cin.get(arrayname,size,s) ?把数据输入到arrayname字符数组中，当到达长度size时结束或者遇到字符s时结束

    return 0;
}