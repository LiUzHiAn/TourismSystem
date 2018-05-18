#include"Graph.h"
#include"Tourism.h"
#include<iostream>
using namespace std;

/********************************
*		time:2018.05.18			*
*		author:Andy				*
*		WHUT					*
*********************************/

int main() 
{
	int choice;
	Tourism t;
	while (true)
	{
		cout << "=================景区管理系统=========================" << endl;
		cout << "1.创建景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出系统"<< endl;
		cout << "请输入操作编号（0~5）:";
		cin >> choice;
		switch (choice)
		{
		/*case 0:
			exit(0);
			break;*/
			if (0 == choice)
			{
				break;
			}
			case 1:
				t.createGraph();
				break;
			case 2:
				t.querySpotInfo();
				break;
			case 3:
				t.travelPath();
				break;
			case 4:
				t.findShortPath();
				break;
			case 5:
				t.designPath();
				break;
			default:
				cout << "请输入正确的功能序号！" << endl;
				break;
		}
	}
	return 0;
}