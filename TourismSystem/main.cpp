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
		cout << "=================��������ϵͳ=========================" << endl;
		cout << "1.��������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�ϵͳ"<< endl;
		cout << "�����������ţ�0~5��:";
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
				cout << "��������ȷ�Ĺ�����ţ�" << endl;
				break;
		}
	}
	return 0;
}