#include"Tourism.h"
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

Tourism::Tourism()
{
	// ��ʼ��ͼ
	mGraph.initGraph();
}

Tourism::~Tourism()
{
}

bool Tourism::createGraph()
{
	// ��ʼ��ͼ
	mGraph.initGraph();

	// ���ļ���ȡ������Ϣ
	fstream inFile;
	int vexNum;
	bool insertVexResult;
	Vex vex;
	inFile.open("vexs.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "���ļ�vexs.txtʧ�ܣ�" << endl;
		return false;
	}
	inFile >> vexNum;
	for (int i = 0;i < vexNum;i++)
	{
		// ���ļ���ȡһ�������Ϣ
		inFile >> vex.num  >> vex.spotName >> vex.spotInfo;
		insertVexResult = mGraph.insertVex(vex);
		if (false == insertVexResult)
			break;
	}
	inFile.close();
	if (!insertVexResult)
	{
		cout << "���뾰��ʧ��!������Ϣ�����ƣ�" << endl;
		return false;
	}

	// ���ļ���ȡ����ߵ���Ϣ
	bool insertEdgeResult;
	Edge edge;
	inFile.open("edges.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "���ļ�edges.txtʧ�ܣ�" << endl;
		return false;
	}
	while (!inFile.eof())
	{
		inFile >> edge.vex1 >> edge.vex2 >> edge.distance;
		insertEdgeResult = mGraph.insertEdge(edge);
		if (false == insertEdgeResult)
			break;
	}
	if (!insertEdgeResult)
	{
		cout << "���뾰���ı�ʧ�ܣ�" << endl;
		return false;
	}

	// ��ʾͼ����Ϣ
	cout << "\n����ͼ�����ɹ�������������Ϣ����" << endl;
	mGraph.prinGraphInfo();
	return true;
}

void Tourism::querySpotInfo()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "��ǰͼ��û�ж��㣬�����Ƿ��Ѿ�����ͼ" << endl;
		return;
	}
	// ��ʾ������Ϣ
	mGraph.printNodeInfo();
	int queryIndex,k;
	Edge find[MAX_SPOT_NUM];
	cout << "��������Ҫ��ѯ�ľ������:";
	cin >> queryIndex;
	if (queryIndex >= mGraph.getVexNum())
	{
		cout << "����ľ����������" << endl;
		return;
	}
	cout << "\n"<<mGraph.getVex(queryIndex).spotName << "--" << mGraph.getVex(queryIndex).spotInfo << endl;
	k = mGraph.findEdge(queryIndex, find);
	cout << "\n=======�ܱ߾���==========" << endl;
	for (int j = 0;j < k;j++)
	{
		cout << mGraph.getVex(queryIndex).spotName << "-->" << mGraph.getVex(find[j].vex2).spotName << "    " << find[j].distance << "��" << endl;
	}
	cout << endl;
}

void Tourism::travelPath()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "��ǰͼ��û�ж��㣬�����Ƿ��Ѿ�����ͼ" << endl;
		return ;
	}
	// ��ӡ��������Ϣ���ο�ѡ�����
	mGraph.printNodeInfo();
	int beginVexIndex = -1;
	cout << "��������ʼ�����ı��:";
	cin >> beginVexIndex;
	if (beginVexIndex >= mGraph.getVexNum())
	{
		cout << "����ľ����������" << endl;
		return;
	}
	PathList pathList = new PathNode;
	PathList pathListTail =pathList;
	mGraph.DFSTravel(beginVexIndex, pathListTail);

	// ��ӡ��·��
	cout << "����·��Ϊ:\n";
	int  routeNum= 0;
	
	while(pathList->next!= NULL)
	{
		cout << "·��" << ++routeNum<<"��";
		for (int i = 0;i < mGraph.getVexNum()-1;i++)
		{
			cout << mGraph.getVex(pathList->vexIndex[i]).spotName << " -> ";
		}
		cout << mGraph.getVex(pathList->vexIndex[mGraph.getVexNum()-1]).spotName << endl;

		pathList = pathList->next;
	}
}

void Tourism::findShortPath()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "��ǰͼ��û�ж��㣬�����Ƿ��Ѿ�����ͼ" << endl;
		return;
	}
	mGraph.printNodeInfo();
	int vexStart, vexEnd;
	cout << "���������뿪ʼ��������ֹ����ı�ţ�";
	cin >> vexStart >> vexEnd;
	if (vexStart >= mGraph.getVexNum()||vexEnd>=mGraph.getVexNum())
	{
		cout << "����ľ����������" << endl;
		return;
	}
	// path[i]��Ӧ�ŵϽ�˹�����㷨�����У���i����㵽Դ�����·���У�
	// ��һ����ת�����±꣨��ǰ����ǰ�����Լ���Դ�����̾���
	Edge path[MAX_SPOT_NUM];
	mGraph.findShortPath(vexStart, vexEnd, path);

	// �Ӻ���ǰ���� �˴�����һ��ջ�������
	stack<int> s;
	int index = vexEnd;
	while (1)
	{
		s.push(index);
		index = path[index].vex1;
		if (index == vexStart)
			break;
	}
	cout << "\n��̵�����·�����£�" << endl;
	cout << mGraph.getVex(vexStart).spotName ;
	
	while (!s.empty())
	{
		cout << " ->" << mGraph.getVex(s.top()).spotName;
		s.pop();
	}
	cout << "    �ܳ� " <<path[vexEnd].distance<< " ��" << endl<<endl;
}

void Tourism::designPath()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "��ǰͼ��û�ж��㣬�����Ƿ��Ѿ�����ͼ" << endl;
		return;
	}
	vector<Edge> edges=mGraph.findMinTree();
	int totalCost = 0;
	cout << "\n======���������������======\n";
	for (vector<Edge>::iterator iter = edges.begin();iter != edges.end();iter++)
	{
		cout << mGraph.getVex(iter->vex1).spotName << " -- " << 
		mGraph.getVex(iter->vex2).spotName << iter->distance << "��"<<endl;

		totalCost += iter->distance;
	}
	cout << "��������ܳ���Ϊ��" << totalCost <<"��"<< endl<<endl;
}
