/*
 * @Author: your name
 * @Date: 2020-06-09 23:01:50
 * @LastEditTime: 2020-06-10 16:19:46
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
    return 0;
}
