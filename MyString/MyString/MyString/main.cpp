#include <iostream>
#include "MyString.h"

int main()
{


	char a[] = "Hello", b[] = "World!";
	CMyString s1(a), s2(b);
	std::cout << s1.c_str() << std::endl;
	std::cout << s2.c_str() << std::endl;
	s1 += s2;
	std::cout << s1.c_str() << std::endl;
	s1 = s2;
	//cout << s1.c_str() << endl;
	std::cout << (s1 + s2) << std::endl;
	std::cout << s1.size() << std::endl;
	std::cout << s1[1] << std::endl;

	if (s1 == s2)
	{
		std::cout << "ПаµИ" << std::endl;
	}
	return 0;
}