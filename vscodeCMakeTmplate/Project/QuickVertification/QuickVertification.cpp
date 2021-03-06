/*
 * @Author: your name
 * @Date: 2020-05-30 09:46:06
 * @LastEditTime: 2020-06-05 10:35:42
 * @LastEditors: Please set LastEditors
 * @Description: 快速验证一些简单代码，而不需要再建立新的工程 利用宏定义来实现各个模块的开启和关闭
 * @FilePath: \vscodeCMakeTmplate\Project\QuickVertification\QuickVertification.cpp
 */

//////////////////////////////宏定义/////////////////////////////////////////////

//#define VIRTUAL_DEFAULTARG   // 验证虚函数中的默认参数
//#define VIRTUAL_PRIVATE  // 验证虚函数可以是private的么？
//#define EXPLICT  // 验证禁止隐士转换
//#define FRIEND  // 验证友元相关
//#define USING // 验证using 的一些用法
//#define ENUM // 测试enum
#define DECLTYPE
//#define MACRO // 测试宏的几个特殊符号

///////////////////////////////////////////////////////////////////

#ifdef VIRTUAL_DEFAULTARG
class Base
{
public:
    virtual void func(int x = 10)
    {
        std::cout << "Base:func(), x = " << x << std::endl;
    }

private:
};

class Derived : public Base
{
public:
    virtual void func(int x = 20)
    {
        std::cout << "Derived:func(), x = " << x << std::endl;
    }
};

int main()
{
    Derived d;
    Base *pd = &d; // 父类指针指向子类对象
    pd->func();    // 应该调用的是子类的函数=，打印出20，而实际上打印的10：原因是 默认参数的使用需要看指针或者应用本身的类型，而不是对象的类型！
    return 0;
}
#endif

#ifdef VIRTUAL_PRIVATE
class Base
{
public:
    //virtual static void fun();

private:
    virtual void func()
    {
        std::cout << "Base: private virtual func()" << std::endl;
    }
    friend int main();
};

class Derived : public Base
{
public:
    void func()
    {
        std::cout << "Derived func " << std::endl;
    }
};

int main()
{
    Base *ptr = new Derived();
    ptr->func(); // 如果将int main()声明为base的friend就可以正常访问. 否则func无法访问
}
#endif

#ifdef EXPLICT
struct A
{
    A(int a) {}
    operator bool() const { return true; }
};

struct B
{
    /* data */
    explicit B(int) {}
    explicit operator bool() const { return true; }
};

int main()
{
    A a1(1);     // 构造函数直接初始化
    A a2 = 1;    // 复制初始化
    A a3{1};     // 列表初始化
    A a4 = {1};  // 复制列表初始化
    A a5 = (A)1; // 允许static_cast的显示转换
    if (a1)
        ;                            // 使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a6(a1);                     //使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a7 = a1;                    //使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
    bool a8 = static_cast<bool>(a1); // static_cast直接初始化

    B b1(1); // 构造函数直接初始化
    //B b2 = 1; //  被explict修饰的构造函数的对象不可以复制初始化
    B b3{1}; // 列表初始化
    //B b4 = {1};  // 被 explicit 修饰构造函数的对象不可以复制列表初始化
    B b5 = (B)1; // 允许static_cast的显示转换
    if (b1)
        ;        // 使用转换函数 A::operator bool() 的从 A 到 bool 的按语境转换
    bool b6(b1); //使用转换函数 A::operator bool() 的从 A 到 bool 的按语境转换

    //bool b7 = b1; //被 explicit 修饰转换函数 B::operator bool() 的对象不可以隐式转换
    bool b8 = static_cast<bool>(b1); // static_cast直接初始化
    return 0;
}
#endif

#ifdef FRIEND
class A
{
public:
    A(int _a) : a(_a) {}
    friend int geta(A &ca); // 友元函数
    friend int getb();

    friend class B; // 友元类
private:
    static int b;
    int a;
};

int A::b = 10;

int geta(A &ca)
{
    return ca.a;
}
int getb()
{
    return A::b;
}

class B
{
public:
    int getb(A ca)
    {
        return ca.a;
    };
};

int main()
{
    A a(3);
    //B b;
    std::cout << geta(a) << std::endl; //3
    std::cout << getb() << std::endl;  // 10

    B b;
    std::cout << b.getb(a) << std::endl; // 3
    return 0;
}

#endif

#ifdef USING

#include <iostream>
#define isNs1 1
//#define isGlobal 2

using namespace std;

void func()
{
    cout << "gloabel-->  ::func()" << endl;
}

namespace s1
{
    void func()
    {
        cout << "s1::func()" << endl;
    }
} // namespace s1

namespace s2
{
#ifdef isNs1
    using s1::func; /// ns1中的函数
#elif isGlobal
    using ::func; /// 全局中的函数
#else
    void func()
    {
        cout << "other::func" << endl;
    }
#endif
} // namespace s2

//2 改变访问性
// 在类的继承中，即使为private，若使用using，就可以将其访问属性改变为子类的
/**
 * 子类对父类成员的访问权限跟如何继承没有任何关系，
 * “子类可以访问父类的public和protected成员，不可以访问父类的private成员”——这句话对任何一种继承都是成立的。
 *
 */

class Base
{
public:
    Base() : n(10), val(100) {}
    void test1()
    {
        cout << "Base test1() " << endl;
    }
    void test1(int a) // 函数重载
    {
        cout << "Base test1(int a) " << endl;
    }

protected:
    std::size_t n;

private:
    int val;
};
class Derived : private Base
{ // 私有继承
public:
    void test2()
    {
        cout << "Derived n = " << n << endl; // n为基类的protected 可以访问，即使是private继承
                                             //cout << "Derived val = " << val << endl; //  val为私有 不可访问
    }
};

class Derived1 : private Base
{ // 私有继承
public:
    using Base::n; // n此时的访问属性为 public
    void test2()
    {
        cout << "Derived n = " << n << endl; // n为基类的protected 可以访问，即使是private继承
    }
};

// 3 函数重载
class Derived2 : public Base
{ // public继承
public:
    void test1()
    {
        cout << "Derived2 test1()" << endl; // n为基类的protected 可以访问，即使是private继承
    }
};

class Derived3 : private Base
{
public:
    using Base::test1; // 注意不要括号
    void test1()
    {
        cout << "Derived2 test1()" << endl; // n为基类的protected 可以访问，即使是private继承
    }
};

int main()
{
    s2::func(); // 主要是看 s2中的哪个func函数有效，就使用哪个

    // 2
    Derived d;
    d.test2();
    //d.n;  //成员 "Base::n"  不可访问
    Derived1 d1;
    d1.n = 1000; // 可以访问

    //3
    Derived2 d2;
    d2.test1();
    // d2.test1(11); // 不能调用基类中的带参函数，被子类给隐藏掉了

    Derived3 d3;
    d3.test1();
    d3.test1(11); // 可以调用
    return 0;
}
#endif

#ifdef ENUM
namespace Color
{
    enum Type
    {
        RED = 1,
        BLUE,
        BLACK
    }; //注意分号
};

int a = Color::Type::RED;

enum class Color2
{
    RED = 2,
    YELLOW,
    BLUE
};

//int a = Color2::RED; //"Color2" 类型的值不能用于初始化 "int" 类型的实体
#endif

#ifdef DECLTYPE

#include <iostream>
#include<string>
#include<vector>
struct
{
    int d;
    double a;
} anos_s;

// template <typename T>
// auto multiply(T x, T y)  //error : auto”函数需要尾随的返回类型
// {
//     return x*y;
// }

template <typename T>
auto multiply(T x, T y) -> decltype(x * y)
{
    return x * y;
}

int main()
{
    decltype(anos_s) as;
    as.a = 10;
    as.d = 100;
    std::cout << sizeof(as) << std::endl;

    std::vector<std::string> vstr = {"da", "adsa", "adsad", "awe", "eqweq"};

    // 显示1
    for (auto& vref : vstr)
    {
        std::cout << vref << std::endl;
    }
    
    //显示2
    for (auto&& vref : vstr)
    {
        std::cout << vref << std::endl;
    }

    // 泛型 输出  自动推断类型 c++11
    for (decltype(vstr.begin()) i = vstr.begin(); i != vstr.end(); i++)
    {
        /* code */
        std::cout << *i << std::endl;
    }
    
    return 0;
}

#endif

#ifdef MACRO

#include <iostream>
#include <string>

#define exp(s) printf(s)
#define exp1(s) printf("test s is: \n" #s)
#define exp2(s) s
#define exp3(s) #s

#define expA(s) printf("pre gc + s   :%s\n",gc_##s)  //gc_s必须存在 实际打印的 是 gc_##s这个变量，因此这个变量要事先定义好
// 注意事项2
#define expB(s) printf("pre gc + s :%s\n",gc_  ##  s)  //gc_s必须存在
// 注意事项1
#define gc_hello1 "I am gc_hello1"

int main()
{
    exp("hello"); // 输出 hello
    printf("\n");
    exp1("hello"); // 输出 "hello"  ==> char[]
    printf("\n");
    //exp(hello); // error ： printf(hello),未定义标识符 hello
    printf("\n");
    exp1(hello); // hello
    printf("\n");
    std::cout << exp2("hello") << std::endl; // hello  s = "hello"
    printf("\n");
    std::string str3 = exp3("hello");
    std::cout << str3 << " " << str3.size() << std::endl; // "hello" 7


    std::string str4 = exp3(" hello  world   ");
    std::cout << str4 << " " << str4.size() << std::endl; // " hello  world   " 18
    
    std::string str5 = exp3( hello );
    std::cout << str5 << " " << str5.size() << std::endl; // hello 5
    
    std::string str6 = exp3(   hello world  );
    std::cout << str6 << " " << str6.size() << std::endl; // hello world 11
    
    //2 
    // 注意事项1
    const char * gc_hello = "I am gc_hello";
    expA(hello);
    expB(hello1);
    
     return 0;
}

#endif
