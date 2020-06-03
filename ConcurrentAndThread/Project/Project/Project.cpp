// Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <windows.h>

int a = 10;

class T
{
public:
	int m_i;
	T(int i) : m_i(i)
	{
		std::cout << "T的构造" << std::endl;
	}
	T(const T& a)
	{
		m_i = a.m_i;
		std::cout << "T的拷贝构造" << std::endl;
	}
	~T()
	{
		std::cout << "T的析构" << std::endl;
	}
	void operator()()
	{
		std::cout << "子线程入口operator() start" << std::endl;
		// ...
		std::cout << "子线程 1 " << m_i << std::endl;
		std::cout << "子线程 2 " << m_i << std::endl;
		std::cout << "子线程 3 " << m_i << std::endl;
		std::cout << "子线程 4 " << m_i << std::endl;
		std::cout << "子线程 5 " << m_i << std::endl;
		std::cout << "子线程 6 " << m_i << std::endl;
		std::cout << "子线程入口operator() end" << std::endl;
	}
};


//void printint()
//{
//	std::cout << "zixianchen1:  " << a << std::endl;
//	std::cout << "zixianchen2:  " << a << std::endl;
//	std::cout << "zixianchen3:  " << a << std::endl;
//	std::cout << "zixianchen4:  " << a << std::endl;
//	std::cout << "zixianchen5:  " << a << std::endl;
//	std::cout << "zixianchen6:  " << a << std::endl;
//}


//void myprint(const int& i, char* mybuf)
//void myprint(const int& i, const std::string& mybuf)
//{
//	std::cout << i << std::endl;
//	std::cout << mybuf.c_str() << std::endl;
//	//std::cout << mybuf << std::endl;
//
//}

class A
{
private:
		int m_a;
public:
	A(int a) : m_a(a) // 别名: 类型转换构造函数，一个参数，可以把一个int转为类类型
	{
		std::cout << "A(int a) 构造函数执行 "  << this << " 线程id = " << std::this_thread::get_id() << std::endl;
	}
	A(const A& aa) :m_a(aa.m_a)
	{
		std::cout << "A 拷贝构造函数执行 " << this << " 线程id = " << std::this_thread::get_id() << std::endl;
	}
	~A()
	{
		std::cout << "A 析构函数执行 " << this << " 线程id = " << std::this_thread::get_id() << std::endl;
	}

private:

};

void myprint(const int i, const A& mybuf)
{
  	//std::cout << i << std::endl;
	std::cout << &mybuf << " 线程id = " << std::this_thread::get_id()  << std::endl;  // 打印A对象的地址

}


int main()
{
 //   std::cout << "Hello World!\n";

	//std::cout << "11: " << a << std::endl;
	//std::thread obj(printint);

	////obj.join();
	//obj.detach();
	//std::cout << "22: " << a << std::endl;

	/*int i = 10;
	T t(i);
	std::thread obj(t);
	obj.detach();*/

	// 传递参数
	int var = 1;
	char mystr[] = "hello thread";

	//std::thread myobj(myprint, var, mystr);
	//myobj.detach();
	int AVar = 12;

	std::cout << "main函数的线程id = " << std::this_thread::get_id() << std::endl;
	//std::thread myobj(myprint, var, A(AVar)); // 将AVar转为A对象，传递个myprint第二个参数【隐士转换】
	std::thread myobj(myprint, var, AVar); // 将AVar转为A对象，传递个myprint第二个参数【隐士转换】

	myobj.join();
	//std::cout << "main fuc" << std::endl;
	//system("pause");
	return 0;
}