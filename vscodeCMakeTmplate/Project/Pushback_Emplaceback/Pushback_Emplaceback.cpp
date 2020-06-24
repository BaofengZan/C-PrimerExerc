/*
 * @Author: zanbf
 * @Date: 2020-05-28 17:53:16
 * @LastEditTime: 2020-06-23 23:02:02
 * @LastEditors: Please set LastEditors
 * @Description: vector的push_back和emplace_back的速度比较  std::chrono
 * @FilePath: \vscodeCMakeTmplate\Project\Pushback_Emplaceback\Pushback_Emplaceback.cpp
 */ 

#include <iostream>
#include <vector>
#include <chrono>
#include <string>

class President
{
private:
    std::string name;
    std::string country;
    int year;
public:
    President(std::string p_name, std::string p_country, int p_year)
    : name(p_name)
    , country(p_country)
    , year(p_year)
    {
        std::cout << "I am being constructed" << std::endl;
    }
    President(const President& other)
    :name(other.name)
    , country(other.country)
    , year(other.year)
    {
        // 拷贝构造
        std::cout << "I am being copy constructed." << std::endl;
    }

    // President(President&& other)
    // : name(std::move(other.name))
    // , country(std::move(other.country))
    // , year(std::move(other.year))
    // {
    //     //移动构造
    //     std::cout << "I am being moveing constructed." << std::endl;
    // }

    //赋值运算符
    President& operator=(const President& other)=default; 
};

int main()
{
    //1 使用内置类型 int
    //输出如下：
    /*
    <int> push_back takes time of: 0.0193696s
    <int> emplace_back takes time of: 0.015787s
    */
    std::vector<int> vInt;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();
    // 执行
    for (int i = 0; i < 1000000; i++)
    {
        vInt.push_back(i);
    }
    
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    double t = elapsed_seconds.count(); // 转化为double
    std::cout << "<int> push_back takes time of: " << t << "s" << std::endl;

    vInt.clear();
    start = std::chrono::steady_clock::now();
    // 执行
    for (int i = 0; i < 1000000; i++)
    {
        vInt.emplace_back(i);
    }
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    t = elapsed_seconds.count(); // 转化为double
    std::cout << "<int> emplace_back takes time of: " << t << "s" << std::endl;

    // 2非内置类型， 类，
    // 如果没有定义移动构造，只实现了拷贝构造那么输出如下：
    /*
    I am being constructed
    I am being copy constructed.
    <President> push_back takes time of: 0.001356s
    I am being constructed
    <President> emplace_back takes time of: 0.0002171s
    */
    // push_back 要比 emplace_back耗时的多。push_back先构造在拷贝构造。

    // 如果定义了移动构造函数，那么输出如下:
    /*
    I am being constructed
    I am being moveing constructed.
    <President> push_back takes time of: 0.00043s
    I am being constructed
    <President> emplace_back takes time of: 0.0001776s
    */
   // 两者仍然push_back要耗时，但是耗时不是太多。push_back先构造在移动构造。

    std::vector<President> vPresident;
    start = std::chrono::steady_clock::now();
    // 执行
    for (int i = 0; i < 1; i++)
    {
        vPresident.push_back(President("a", "b", 1));
    }
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    t = elapsed_seconds.count(); // 转化为double
    std::cout << "<President> push_back takes time of: " << t << "s" << std::endl;

    vPresident.clear();
    start = std::chrono::steady_clock::now();
    // 执行
    for (int i = 0; i < 1; i++)
    {
        vPresident.emplace_back("a", "b", 1);
    }
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    t = elapsed_seconds.count(); // 转化为double
    std::cout << "<President> emplace_back takes time of: " << t << "s" << std::endl;

    //3
    vPresident.clear();
    start = std::chrono::steady_clock::now();
    // 执行
    for (int i = 0; i < 1; i++)
    {
        // 有移动构造函数的情况下
        // I am being constructed
        // I am being moveing constructed.
        // <President> emplace_back takes time of: 0.0010794s

        //如果没有移动构造函数
        //I am being constructed
        //I am being copy constructed.
        //<President> emplace_back takes time of: 0.0019493s
        vPresident.emplace_back(President("a", "b", 1));
    }
    
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    t = elapsed_seconds.count(); // 转化为double
    std::cout << "<President> emplace_back takes time of: " << t << "s" << std::endl;
    
    return 0;
}