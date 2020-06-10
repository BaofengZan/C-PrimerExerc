/*
 * @Author: your name
 * @Date: 2020-06-05 14:58:45
 * @LastEditTime: 2020-06-10 17:28:04
 * @LastEditors: Please set LastEditors
 * @Description: 测试智能指针的相关
 * @FilePath: \vscodeCMakeTmplate\Project\SharedPtr\SharedPtr.cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
class CBase
{
private:
    /* data */
    int m_ia;
    int m_ib;
    std::string m_sc;

public:
    CBase(int a, int b, std::string c);
    void show()
    {
        std::cout << "a = " << m_ia << " b = " << m_ib << " c = " << m_sc << std::endl;
    }
    ~CBase();
};

CBase::CBase(int a, int b, std::string c)
    : m_ia(a), m_ib(b), m_sc(c)
{
}

CBase::~CBase()
{
}

// 如果构造函数时protected的话，智能指针就无法make_shared 会报错 
// 解决办法：就是使用继承 如下面的代码
class CBase1
{
private:
    int m_ia;
    std::string m_sc;

protected:
    CBase1(int a, std::string s) : m_ia(a), m_sc(s)
    {
    }
    ~CBase1() {}

public:
    void show()
    {
        std::cout << "a = " << m_ia << " c = " << m_sc << std::endl;
    }
};

class CDerived : public CBase1
{
private:
    /* data */
public:
    CDerived(int a, std::string s): CBase1(a, s)
    {
       
    }

    ~CDerived()
    {
    }
};

int main()
{
    std::shared_ptr<CBase> ptr = std::make_shared<CBase>(10, 100, "asd"); // 后面参数就是 构造函数需要的参数
    ptr->show();

    
    // error: 'CBase1::CBase1(int, std::__cxx11::string)' is protected within this context
    //std::shared_ptr<CBase1> ptr2 = std::make_shared<CBase1>(10, "asd"); // 后面参数就是 构造函数需要的参数

    // 解决办法：
    // 使用继承类：子类来实现调用基类的函数
    std::shared_ptr<CDerived> ptr2 = std::make_shared<CDerived>(3230, "ghdd");
    ptr2->show();
    return 0;
}