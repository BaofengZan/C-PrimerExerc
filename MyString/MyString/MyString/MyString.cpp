// MyString.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include <cstring>
#include <assert.h>
#include "MyString.h"

CMyString::CMyString(const char* str)
{
	if (str==nullptr) // 对m_data加NULL 判断
	{
		this->m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(str) + 1]; // 最后有个结束符
		strcpy(this->m_pData, str);
	}
}

CMyString::CMyString(const CMyString& str)
{
	// 拷贝构造
	if (str.m_pData == nullptr)
	{
		this->m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(str.m_pData) + 1];
		strcpy(this->m_pData, str.m_pData);
	}
}

CMyString::~CMyString()
{
	if (this->m_pData)
	{
		delete[] this->m_pData;  // char *指向的
		this->m_pData = nullptr;
	}
}

CMyString& CMyString:: operator= (const CMyString& str)
{
	/*
	我们先用delete释放了实例m_pdata的内存，
	如果此时内存不足导致new char抛出异常，则m_data将是一个空指针，
	这样非常容易导致程序崩溃。违背了异常安全性原则。
	*/
	// 赋值运算符
	if (this != &str)
	{
		delete[] this->m_pData; // 释放原有资源
		if (str.m_pData == nullptr)
		{
			this->m_pData = nullptr;
		}
		else
		{
			this->m_pData = new char[strlen(str.m_pData) + 1];
			if (!this->m_pData)
			{
				assert((this->m_pData != nullptr));
			}
			strcpy(this->m_pData, str.m_pData);
		}
	}

	return *this;
}

CMyString CMyString::operator+(const CMyString& str)  // 字符串连接
{
	//创建一个string
	CMyString newstring;
	if (!str.m_pData) // str.m_pData==nullptr
	{
		newstring = *this;
	}
	else if (!this->m_pData)
	{
		newstring = str;  // 需要实现赋值运算赋值符
	}
	else // 两个都不为空，concat
	{
		newstring.m_pData = new char[strlen(str.m_pData) + strlen(this->m_pData)+ 1];
		strcpy(newstring.m_pData, this->m_pData);
		strcat(newstring.m_pData, str.m_pData);
	}
	return newstring;
}

bool CMyString::operator==(const CMyString& str) // 两个字符串是否相等
{
	if (strlen(str.m_pData) != strlen(this->m_pData)) // 长度不等
	{
		return false;
	}
	else
	{
		// 当str1的字典序大于str2时返回一个一个正数
		// str1 < str2 返回负数
		// == 时返回0
		if (0 == strcmp(str.m_pData, this->m_pData))
		{
			return true;
		}
		else
		{
			return false;
		}
		//return (strcmp(str.m_pData, this->m_pData)) ? false : true;
	}
}
char CMyString::operator[](int index) // 数组索引 返回字符
{
	//边界检查
	if (index < 0 || index >= strlen(this->m_pData))
	{
		return NULL;
	}
	return this->m_pData[index];
}

CMyString& CMyString::operator+=(const CMyString& str)
{
	// 重新分类成员
	char* newdata = new char[strlen(this->m_pData) + strlen(str.m_pData) + 1];
	strcpy(newdata, this->m_pData);
	strcat(newdata, str.m_pData);
	delete[] this->m_pData; //清空当前对象内存
	this->m_pData = newdata;
	return *this;


}

const int CMyString::size() const
{
	return strlen(this->m_pData);  // 不包含最后的\0
}

const char* CMyString::c_str() const
{
	return this->m_pData;
}
