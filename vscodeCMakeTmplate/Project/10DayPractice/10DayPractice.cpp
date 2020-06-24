/*
 * @Author: your name
 * @Date: 2020-06-05 18:03:05
 * @LastEditTime: 2020-06-20 17:59:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vscodeCMakeTmplate\Project\10DayPractice\10DayPractice.cpp
 */

/////////////////////宏开关/////////////////////

//#define D1_1   //union
//#define D2_1
// #define D2_2 // 汉诺塔  递归
//#define D3 // 静态数据成员
//#define D4 //时钟类，能够记录时、分、秒，重载它的++运算符，每执行一次++运算，加时1秒，但要使计时过程能够自动进位
//#define D5_1 // 虚拟继承：派生类初始化 ：虚基类由最终派生类初始化
//#define D6_1 // 操作符重载: 类对象和内置类型的操作（比如A+2）
#define D7 // string的操作符重载
/////////////////////////////////////////

#ifdef D1_1
#include <iostream>

union myunion {
    int k;
    struct
    {
        int x;
        int y;
        int z;
    } u;
};

int main()
{
    myunion a;
    a.u.x = 1;
    a.u.y = 2;
    a.u.z = 3;
    a.k = 4;                                                                                             // 把 a.u.x 覆盖掉了  (union以最大的结构：struct分配一块内存，k的内存也用这一块的一部分)
    std::cout << "x = " << a.u.x << " y = " << a.u.y << " z = " << a.u.z << " k = " << a.k << std::endl; // x = 4 y = 2 z = 3 k = 4
    return 0;
}

#endif

#ifdef D2_1
#include <iostream>
using namespace std;
double power(double x, int n); // x^n = x*x*x...

int main(int argc, char const *argv[])
{
    int x;
    cin >> x;
    int wei = 0;
    int sum = 0;
    int each, chu;
    for (int i = 0; i < 8; i++)
    {
        each = x % 10;
        chu = x / 10;
        sum += each * power(2, wei);
        x = chu;
        wei++;
    }
    cout << sum << endl;
    system("pause");
    return 0;
}
double power(double x, int n)
{
    double val = 1.0;
    while (n--)
    {
        val *= x;
    }
    return val;
}

#endif

#ifdef D2_2
#include <iostream>

void move(char A, char B)
{
    std::cout << A << "-->" << B << std::endl;
}
void hanoi(int n, char A, char B, char C)
{
    // 共有几个盘子。 A B C三个柱子  由A移动到C B为辅助
    if (n == 1)
    {
        move(A, C);
    }
    else
    {
        hanoi(n - 1, A, C, B); // 先把上面的n-1个 由A移到B C作为辅助
        move(A, C);
        hanoi(n - 1, B, A, C); //把B上的n-1个移动C
    }
}

int main()
{
    hanoi(3, 'A', 'B', 'C');
    return 0;
}

#endif

#ifdef D3

#include <iostream>
class Base1
{
public:
    Base1(int aa) : a(aa)
    {
        b += 10;
    }
    void g();
    static void f();

private:
    int a;
    static int b;
};

//  静态变量初始化 在类外
int Base1::b = 100;

void Base1::f()
{
    //std::cout << a << std::endl;  // 静态函数只能调用静态变量
    std::cout << b << std::endl;
}
void Base1::g()
{
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

int main()
{
    Base1::f(); // 静态函数 由类名和作用域符号离开调用    100

    Base1 b(123); // 每调用一次 静态变量b+10
    Base1::f();   // 静态函数 由类名和作用域符号离开调用 110
    //Base1::g();  // 非静态成员 只能由对象来调用

    Base1 b1(123); // 每调用一次 静态变量b+10
    Base1::f();    // 静态函数 由类名和作用域符号离开调用 120

    return 0;
}

#endif

#ifdef D4

#include <iostream>

class Time
{
private:
    /* data */
    int hour, minute, second;

public:
    Time(int h = 0, int m = 0, int s = 0)
    {
        hour = h;
        minute = m;
        second = s;
    }

    ~Time()
    {
    }

    /*
    首先要确定它的返回值是左值，还是右值，如果是左值最返回引用，如果是右值那就直接返回值；
    // 前增量 返回引用()
    // 后增量 返回值
    */
    Time &operator++();   // 前缀++
    Time operator++(int); // 后缀++

    //全局函数
    friend Time &operator--(Time &t); //前缀--   友元函数参数说明： 要访问非static成员时，需要对象做参数
    friend Time operator--(Time &t, int);
    void showTime()
    {
        std::cout << "Current time is: " << hour << " : " << minute << " : " << second << std::endl;
    }
};

Time &Time::operator++()
{
    second++;
    if (second == 60)
    {
        second = 0;
        minute++;
        if (minute == 60)
        {
            minute = 0;
            hour++;
            if (hour == 24)
            {
                hour = 0;
            }
        }
    }
    return *this;
}

Time Time::operator++(int)
{
    second++;
    if (second == 60)
    {
        second = 0;
        minute++;
        if (minute == 60)
        {
            minute = 0;
            hour++;
            if (hour == 24)
            {
                hour = 0;
            }
        }
    }
    return *this;
}

// 友元函数的实现 不用再写friend
Time &operator--(Time &t)
{
    --t.second;
    if (t.second < 0)
    {
        t.second = 59;
        --t.minute;
        if (t.minute < 0)
        {
            t.minute = 59;
            --t.hour;
            if (t.hour < 0)
                t.hour = 23;
        }
    }
    return t;
}

Time operator--(Time &t, int)
{
    --t.second;
    if (t.second < 0)
    {
        t.second = 59;
        --t.minute;
        if (t.minute < 0)
        {
            t.minute = 59;
            --t.hour;
            if (t.hour < 0)
                t.hour = 23;
        }
    }

    return t;
}

int main()
{
    Time t(23, 59, 58);
    t.showTime();
    ++t;
    t.showTime();
    ++t;
    t.showTime();
    t++;
    t.showTime();

    std::cout << "-------------" << std::endl;
    // 自减
    t--;
    t.showTime();
    --t;
    t.showTime();

    Time t2(12, 56, 23);
    t2--;
    t2.showTime();
    return 0;
}

/*
Current time is: 23 : 59 : 58
Current time is: 23 : 59 : 59
Current time is: 0 : 0 : 0
Current time is: 0 : 0 : 1
*/
#endif

#ifdef D5_1
// 说明： 基础知识.md -> 虚继承的一些说明
#include <iostream>
using namespace std;

class A
{
    int a;

public:
    A(int x)
    {
        a = x;
        cout << "Virtual Bass A..." << endl;
    }
};

class B : virtual public A
{
public:
    B(int i) : A(i) { cout << "Virtual Bass B..." << endl; }
};

class C : virtual public A
{
    int x;

public:
    C(int i) : A(i)
    {
        cout << "Constructing C..." << endl;
        x = i;
    }
};

class ABC : public C, public B
{
public:
    //虚基类由最终派生类初始化
    ABC(int i, int j, int k) : A(k), C(i), B(j) // 无论虚基类A(K)放在哪里 都是先初始化 接着才是按顺序
    {
        cout << "Constructing ABC..." << endl;
    }

    //     ABC(int i, int j, int k) : C(i), B(j) // error : no matching function for call to 'A::A()'
    //     {
    //         cout << "Constructing ABC..." << endl;
    //     }
};
int main()
{
    ABC obj(1, 2, 3);
    system("pause");
    return 0;
}

#endif

#ifdef D6_1

#include <iostream>

// 复数类
class Complex
{

public:
    Complex(double R = 0, double I = 0) : r(R), i(I){};
    ~Complex(){};

    // 操作符重载 + - * / 使用者为两边  定义为全局函数
    friend Complex operator+(Complex &a, Complex &b);
    friend Complex operator-(Complex &a, Complex &b);
    friend Complex operator*(Complex &a, Complex &b);
    friend Complex operator/(Complex &a, Complex &b);

    void disPlay()
    {
        std::cout << r;
        if (i > 0)
            std::cout << "+";
        if (i != 0)
            std::cout << i << "i" << std::endl;
    }

private:
    double i;
    double r;
};

Complex operator+(Complex &a, Complex &b)
{
    return Complex(a.r + b.r, a.i + b.i);
}

Complex operator-(Complex &a, Complex &b)
{
    return Complex(a.r - b.r, a.i - b.i);
}

// (a+bi)(c+di)=(ac-bd)+(bc+ad)i。
Complex operator*(Complex &a, Complex &b)
{
    Complex t;
    t.r = a.r * b.r - a.i * b.i;
    t.i = a.r * b.i + a.i * b.i;
    return t;
}

//(a+bi)/(c+di)=(ac+bd)/(c2+d2) +((bc-ad)/(c2+d2))i
Complex operator/(Complex &a, Complex &b)
{
    Complex t;
    double x = 1 / (b.i * b.i + b.r * b.r);
    t.r = x * (a.r * b.r + a.i + b.i);
    t.i = x * (a.i * b.r - a.r * b.i);
    return t;
}

int main()
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    c1.disPlay();
    c2.disPlay();

    Complex c = c1 + c2;
    c.disPlay();

    return 0;
}

#endif

#ifdef D7
#include <iostream>
#include <cstring>

class MyString
{
public:
    MyString(const char *str)
    {
        if (this->sptr == nullptr) // 对m_data加NULL 判断
        {
            this->sptr = nullptr;
        }
        else
        {
            this->sptr = new char[strlen(str) + 1]; // 最后有个结束符
            strcpy(this->sptr, str);
            length = strlen(str);
        }
    }
    ~MyString()
    {
        if (this->sptr)
        {
            delete[] this->sptr; // char *指向的
            this->sptr = nullptr;
        }
    }
    const MyString &operator=(const MyString &s);  // 重载= 返回当前对象的引用
    const MyString &operator+=(const MyString &s); // 字符串串联
    MyString operator+(const MyString& s);
    bool operator==(const MyString &s);
    bool operator!=(const MyString &s);
    bool operator!();
    bool operator<(const MyString &s) const;
    bool operator>(const MyString &s);
    bool operator>=(const MyString &s);
    //下标
    char &operator[](int);

private:
    int length; //字符串长度
    char *sptr; // 字符串内容
    friend std::ostream &operator<<(std::ostream &os, const MyString &str)
    {
        os << str.sptr;
        return os;
    }
    //friend ostream& operator<<(ostream &os, const MyString &s);
    //friend istream& operator<<(istream &is, MyString &s);
};

const MyString &MyString::operator+=(const MyString &s)
{
    char *tmp = this->sptr;
    this->length += s.length;
    this->sptr = new char[this->length + 1];
    strcpy(sptr, tmp);
    strcat(sptr, s.sptr);
    delete[] tmp;
    return *this;
}

MyString MyString::operator+(const MyString& s)
{
    MyString tmp(*this);
    tmp+=s;
    return tmp;
}

bool MyString::operator==(const MyString &s)
{
    return strcmp(this->sptr, s.sptr) == 0;
}
bool MyString::operator!=(const MyString &s)
{
    return !(*this == s);
}

bool MyString::operator!()
{
    return this->length == 0;
}
bool MyString::operator<(const MyString &s) const
{
    return strcmp(this->sptr, s.sptr) < 0;
}

bool MyString::operator>(const MyString &s)
{
    return s < (*this);
}
bool MyString::operator>=(const MyString &s) { return !(*this < s); }
char &MyString::operator[](int subscript) { return (this->sptr)[subscript]; }

int main()
{
    MyString s1("abd");
    std::cout << s1 << std::endl;
    MyString s2("   ----------------");
    MyString s3 = s1 + s2;
    std::cout << s3 << std::endl;
    
    return 0;
}
#endif