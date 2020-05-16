/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑       永不宕机     永无BUG
 */

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

template<typename T>
void f(T&& param)
{
    if (std::is_same<string, T>::value)
    {
        std::cout << "string" << std::endl;
    }
    else if(std::is_same<string&, T>::value)
    {
        /* code */
        std::cout << "string&" << std::endl;
    }
    else if (std::is_same<string&&, T>::value)
    {
        std::cout << "string&&" << std::endl;
    }  
    else if (std::is_same<int, T>::value)
    {
        std::cout << "int" << std::endl;
    }
    else if (std::is_same<int&, T>::value)
    {
        std::cout << "int&" << std::endl;
    }
    else if (std::is_same<int&&, T>::value) 
    {
        std::cout << "int&&" << std::endl;
    }   
    else
    {
        std::cout << "unkown" << std::endl;
    }
}

int main()
{
    int x = 10; // x为左值
    f(1);  // 参数是右值，T推导成 int， int&& 为右值引用
    f(x); //x是左值， T推到成 int&，  int& && 折叠成int& 左值引用
    int && a = 2;
    // a为右值引用 //实质上就是将不具名(匿名)变量取了个别名
    // 但是如果从左值和右值的角度区分它，它实际上是个左值。
    // 因为可以对它取地址，而且它还有名字，是一个已经命名的右值
    f(a); // a实际上是左值，T被推导为 int&

    string str = "hello"; // str是左值
    f(str); // //参数是左值 T推导成了string&
    f(string(str)); //构建了临时变量，参数为右值，T推到成string
    f(std::move(str)); // move将左值变为右值，T推导成string

    return 0;
}