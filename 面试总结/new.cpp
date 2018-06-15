/*************************************************************************
  > File Name: new.cpp
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: Tue 22 Aug 2017 03:02:48 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

class A
{
	public:
		A(int a = 10):_a(a)
	{
		cout << "A的构造函数被执行了" <<endl;
	}
	int test()
	{
		cout << "_a = "<< _a <<endl;
	}
	private:
		int _a;
};

int main()
{

	 A*p1 = new A[10]();
	 cout << "无括号情况"<<endl
	 A*p2 = new A[10];

/*	for(int i = 0; i < 10; ++i)
	{
		 p1[i].test();	
	}

	cout <<endl;
	for(int i = 0; i < 10; ++i)
	{
		p2[i].test();
	}
	cout <<endl;
*/

	cout << "hello..."<<endl;
	return 0;
}
