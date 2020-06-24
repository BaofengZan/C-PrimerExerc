/*
 * @Author: your name
 * @Date: 2020-06-09 23:01:50
 * @LastEditTime: 2020-06-10 22:34:47
 * @LastEditors: Please set LastEditors
 * @Description: 模板-函数模板和类模板
 * @FilePath: \vscodeCMakeTmplate\Project\Template\Template.cpp
 */
#include <iostream>
#include <cstring>
//实现冒泡
template <typename T>
void display(T &a, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << a[i] << "\t" << std::endl;
}

// 模板特例化
template <typename T>
T Max(T a, T b)
{
    return (a > b) ? a : b;
}

// 但是对于char*的就不能使用 因此需要特化
//template <>
//返回类型 函数名<特化的数据类型>(参数表) {}
template <>
char *Max<char *>(char *a, char *b)
{
    return (strcmp(a, b) >= 0) ? a : b;
}

void bubbleSort(int A[], int n)
{
    bool sorted = false; // 标志 可提前结束
    while (!sorted)      // 如果没有交换(也就是全部有序了)， 就不会进入循环
    {
        /* code */
        sorted = true;              // 首先设置true，就可以保证
        for (int i = 1; i < n; i++) // 从左向右遍历
        {
            /* code */
            if (A[i - 1] > A[i]) // 前面大于后面 需要交换
            {
                /* code */
                //swap(A[i-1], A[i]); // 交换
                int tmp = A[i - 1];
                A[i - 1] = A[i];
                A[i] = tmp;
                sorted = false; //
            }
        }
        n--; // 最后一位元素必然就位
    }
}

// 通用数组类，可以实现 下标索引和排序
const int Size = 5;
template <typename T>
class Array
{
private:
    T a[Size];

public:
    Array()
    {
        for (int i = 0; i < Size; i++)
        {
            a[i] = 0;
        }
    }
    T &operator[](int i);
    void sort();
};

template <typename T>
T &Array<T>::operator[](int i)
{
    if (i < 0 || i > Size - 1)
    {
        std::cout << "out of index" << std::endl;
        exit(-1);
    }
    return a[i];
}

template <typename T>
void Array<T>::sort()
{
    int p = 0;
    for (int i = 0; i < Size - 1; i++)
    {
        /* code */
        p = i;
        for (int j = i; j < Size; j++)
        {
            if (a[p] < a[j]) // 这里的判断对char* 数据不行 因此要特化一个
            {
                p = j;
            }
        }
        // swap
        T t = a[p];
        a[p] = a[i];
        a[i] = t;
    }
}

template <>
void Array<char *>::sort()
{
    int p = 0;
    for (int i = 0; i < Size - 1; i++)
    {
        /* code */
        p = i;
        for (int j = i; j < Size; j++)
        {
            if (strcmp(a[p], a[j]) < 0) // 这里的判断对char* 数据不行 因此要特化一个
            {
                p = j;
            }
        }
        // swap
        char *t = a[p];
        a[p] = a[i];
        a[i] = t;
    }
}

// 模拟栈：
//设计一个堆栈的类模板Stack，在模板中用类型参数T表示栈中存放的数据，用非类型参数MAXSIZE代表栈的大小。
//知识点： 模板可以提供 特定类型 的参数
template <typename T, int MAXSIZE>
class Stack
{
private:
    T elem[MAXSIZE];
    int top; // 栈顶下标

public:
    Stack()
    {
        top = 0;
    }

    void push(T e);
    T pop();
    bool empty()
    {
        if (top < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void clean()
    {
        top = -1;
    }
    bool full()
    {
        if (top > MAXSIZE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T e)
{
    if (full())
    {
        std::cout << "stack is full" << std::endl;
    }
    top++;
    elem[top] = e;
}
template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::pop()
{
    if (empty())
    {
        std::cout << "stack is empty" << std::endl;
    }
    // 注意这里 不能写 top-- return elem[top];
    // 顺序应该是 先得到要return 的值，然后top在减1
    //top--;
    return elem[top--];
}

int main()
{
    int a[] = {1, 5, 3, 2, 7};
    display(a, 5);
    char b[] = {'a', 'c', 's', 'd', 'w', 'e', 'r'};
    display(b, 7);

    float c = 5.1, d = 3.2;
    std::cout << "2,3的最大值是：" << Max<int>(3, 2) << std::endl;
    std::cout << "c,d的最大值是：" << Max<float>(c, d) << std::endl;
    std::cout << Max("xbv", "xyce") << std::endl;

    bubbleSort(a, 5);

    Array<int> a1;
    Array<char *> b1;
    a1[0] = 1;
    a1[1] = 23;
    a1[2] = 6;
    a1[3] = 3;
    a1[4] = 9;
    a1.sort();
    for (int i = 0; i < 5; i++)
        std::cout << a1[i] << "\t";
    std::cout << std::endl;
    b1[0] = "x1";
    b1[1] = "ya";
    b1[2] = "ad";
    b1[3] = "be";
    b1[4] = "bc";
    b1.sort();
    for (int i = 0; i < 5; i++)
        std::cout << b1[i] << "\t";
    std::cout << std::endl;

    //类模板实例化
    Stack<int, 10> iStack;
    Stack<char, 10> cStack;
    iStack.clean();
    cStack.clean();
    std::cout << "-------intStack----\n";
    int i;
    for (i = 1; i < 11; i++)
        iStack.push(i);
    for (i = 1; i < 11; i++)
        std::cout << iStack.pop() << "\t";
    std::cout << "\n\n-------charStack----\n";
    cStack.push('A');
    cStack.push('B');
    cStack.push('C');
    cStack.push('D');
    cStack.push('E');
    for (i = 1; i < 6; i++)
        std::cout << cStack.pop() << "\t";
    std::cout << std::endl;
    return 0;
}
