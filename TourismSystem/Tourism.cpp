#include"Tourism.h"
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

Tourism::Tourism()
{
	// 初始化图
	mGraph.initGraph();
}

Tourism::~Tourism()
{
}

bool Tourism::createGraph()
{
	// 初始化图
	mGraph.initGraph();

	// 从文件读取景点信息
	fstream inFile;
	int vexNum;
	bool insertVexResult;
	Vex vex;
	inFile.open("vexs.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "打开文件vexs.txt失败！" << endl;
		return false;
	}
	inFile >> vexNum;
	for (int i = 0;i < vexNum;i++)
	{
		// 从文件读取一个点的信息
		inFile >> vex.num  >> vex.spotName >> vex.spotInfo;
		insertVexResult = mGraph.insertVex(vex);
		if (false == insertVexResult)
			break;
	}
	inFile.close();
	if (!insertVexResult)
	{
		cout << "插入景点失败!景点信息超限制！" << endl;
		return false;
	}

	// 从文件读取景点边的信息
	bool insertEdgeResult;
	Edge edge;
	inFile.open("edges.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "打开文件edges.txt失败！" << endl;
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
		cout << "插入景点间的边失败！" << endl;
		return false;
	}

	// 显示图的信息
	cout << "\n景点图创建成功，景点详情信息如下" << endl;
	mGraph.prinGraphInfo();
	return true;
}

void Tourism::querySpotInfo()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "当前图中没有顶点，请检查是否已经创建图" << endl;
		return;
	}
	// 显示景点信息
	mGraph.printNodeInfo();
	int queryIndex,k;
	Edge find[MAX_SPOT_NUM];
	cout << "请输入你要查询的景区编号:";
	cin >> queryIndex;
	if (queryIndex >= mGraph.getVexNum())
	{
		cout << "输入的景区编号有误！" << endl;
		return;
	}
	cout << "\n"<<mGraph.getVex(queryIndex).spotName << "--" << mGraph.getVex(queryIndex).spotInfo << endl;
	k = mGraph.findEdge(queryIndex, find);
	cout << "\n=======周边景区==========" << endl;
	for (int j = 0;j < k;j++)
	{
		cout << mGraph.getVex(queryIndex).spotName << "-->" << mGraph.getVex(find[j].vex2).spotName << "    " << find[j].distance << "米" << endl;
	}
	cout << endl;
}

void Tourism::travelPath()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "当前图中没有顶点，请检查是否已经创建图" << endl;
		return ;
	}
	// 打印出景点信息供游客选择起点
	mGraph.printNodeInfo();
	int beginVexIndex = -1;
	cout << "请输入起始景区的编号:";
	cin >> beginVexIndex;
	if (beginVexIndex >= mGraph.getVexNum())
	{
		cout << "输入的景区编号有误！" << endl;
		return;
	}
	PathList pathList = new PathNode;
	PathList pathListTail =pathList;
	mGraph.DFSTravel(beginVexIndex, pathListTail);

	// 打印出路径
	cout << "导游路线为:\n";
	int  routeNum= 0;
	
	while(pathList->next!= NULL)
	{
		cout << "路线" << ++routeNum<<"：";
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
		cout << "当前图中没有顶点，请检查是否已经创建图" << endl;
		return;
	}
	mGraph.printNodeInfo();
	int vexStart, vexEnd;
	cout << "请依次输入开始景点与终止景点的编号：";
	cin >> vexStart >> vexEnd;
	if (vexStart >= mGraph.getVexNum()||vexEnd>=mGraph.getVexNum())
	{
		cout << "输入的景区编号有误！" << endl;
		return;
	}
	// path[i]对应着迪杰斯特拉算法过程中，第i个结点到源点最短路径中，
	// 上一个中转结点的下标（当前结点的前驱）以及到源点的最短距离
	Edge path[MAX_SPOT_NUM];
	mGraph.findShortPath(vexStart, vexEnd, path);

	// 从后往前回溯 此处设置一个栈方便输出
	stack<int> s;
	int index = vexEnd;
	while (1)
	{
		s.push(index);
		index = path[index].vex1;
		if (index == vexStart)
			break;
	}
	cout << "\n最短的游览路径如下：" << endl;
	cout << mGraph.getVex(vexStart).spotName ;
	
	while (!s.empty())
	{
		cout << " ->" << mGraph.getVex(s.top()).spotName;
		s.pop();
	}
	cout << "    总长 " <<path[vexEnd].distance<< " 米" << endl<<endl;
}

void Tourism::designPath()
{
	if (mGraph.getVexNum() == 0)
	{
		cout << "当前图中没有顶点，请检查是否已经创建图" << endl;
		return;
	}
	vector<Edge> edges=mGraph.findMinTree();
	int totalCost = 0;
	cout << "\n======电线铺设情况如下======\n";
	for (vector<Edge>::iterator iter = edges.begin();iter != edges.end();iter++)
	{
		cout << mGraph.getVex(iter->vex1).spotName << " -- " << 
		mGraph.getVex(iter->vex2).spotName << iter->distance << "米"<<endl;

		totalCost += iter->distance;
	}
	cout << "铺设电线总长度为：" << totalCost <<"米"<< endl<<endl;
}
