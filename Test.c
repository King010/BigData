#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"BigData.h"
using namespace std;

void Fun1()
{
	BigData b1("123124814");
	cout << b1<<endl;
	BigData b2("0000024814");
	cout << b2 << endl;
	BigData b3("        24814");
	cout << b3 << endl;
	BigData b4("-00123124814");
	cout << "b4"<<b4 << endl;

	BigData b5("12312dsadas4814");
	cout << b5 << endl;

	BigData b6("12312  4814");
	cout << b6 << endl;

}

void Fun2()
{
	BigData b1("9999999999999999999");
	BigData b2("-9999999999999999999");
	BigData b3("33333333");
	BigData b4("-33333333");
	//BigData b3(b1 + b2);
	cout << b1 + b3 << endl;//正 正  正
	cout << b1 + b4 << endl;//正 负  正
	cout << b2 + b4 << endl;//负 负  负
	cout << b4 + b1 << endl;//负 正	 正

	cout << endl;

	cout << b3 - b1 << endl;//正 正	 负
	cout << b1 - b4 << endl;//正 负	 正
	cout << b2 - b4 << endl;//负 负	 负
	cout << b4 - b1 << endl;//负 正	 负
}

void Fun3()
{
	BigData b1("99999999999");
	BigData b2("-9999999999");

	BigData b3("33333333333333333333333");
	BigData b4("-33333333333333333333333");

	BigData b5("44444444444444444444444444444");
	BigData b6("-44444444444444444444444444444");

	//BigData b3(b1 + b2);

	cout << b1 + b3 << endl;//正 正  正

	cout << b1 + b4 << endl;//正 负  负
	cout << b5 + b2 << endl;//正 负  正

	cout << b4 + b5 << endl;//负 正	 正
	cout << b6 + b1 << endl;//负 正  负

	cout << b2 + b4 << endl;//负 负  负

	cout << endl;

	cout << b3 - b1 << endl;//正 正	 正
	cout << b3 - b5 << endl;//正 正	 负

	cout << b1 - b4 << endl;//正 负	 正

	cout << b2 - b4 << endl;//负 负	 正
	cout << b4 - b1 << endl;//负 正	 负

}

void Fun4()
{
	BigData b1("9999999999");
	BigData b2("100000000000000");
	cout << b1*b2 << endl;

}

void Fun5()
{
	BigData b1("22222222222222222222");
	BigData b2("-22222222222222222222");
	cout << b1/b2 << endl;
}

int main()
{
	//Fun1();
	//Fun2();
	//Fun3();
	//Fun4();
	Fun5();

	system("pause");
	return 0;
}
