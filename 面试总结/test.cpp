/*************************************************************************
	> File Name: emptyclass.cpp
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: 2017年04月04日 星期二 00时05分06秒
 ************************************************************************/

#include<iostream>
using namespace std;


class Empty
{
};

class HoldsAnInt
{
	int x;
	Empty e;
};

int main()
{
	cout << sizeof(Empty)<< endl;
	cout << "sizeof(HoldsAnInt)= " << sizeof(HoldsAnInt) <<endl;
	return 0;
}
