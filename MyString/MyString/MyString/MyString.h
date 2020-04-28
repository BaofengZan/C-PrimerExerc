// MyString.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。
#pragma once
#include <ostream>
#pragma warning(disable:4996)

class CMyString
{
	// 友元函数 用于输出
	friend std::ostream& operator<<(std::ostream& os, const CMyString& str)
	{
		os << str.m_pData;
		return os;
	}
public:
	CMyString(const char* str=nullptr);
	~CMyString();
	
	CMyString(const CMyString& str);
	CMyString& operator=(const CMyString& str);
	
	CMyString operator+(const CMyString& str);  // 字符串连接
	bool operator==(const CMyString& str); // 两个字符串是否相等
	char operator[](int index); // 数组索引 返回字符
	
	CMyString& operator+=(const CMyString& str); // 实现两个字符串的连接
	const int size() const; // 函数后面const，说明this指向的对象不能改变

	const char* c_str() const; // 返回const char*

protected:
	char* m_pData;
private:
};