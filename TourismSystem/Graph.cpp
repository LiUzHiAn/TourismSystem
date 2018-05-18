#include "Graph.h"
#include<iostream>
#include<vector>
using namespace std;

void Graph::initGraph()
{
	for (int i = 0;i < MAX_SPOT_NUM;i++)
	{
		for (int j = 0;j < MAX_SPOT_NUM;j++)
		{
			// ��ʼ���ڽӾ���Ϊ-1����ʾ���ж���֮�䲻���ڱ�
			adjMatrix[i][j] = -1;
		}
	}
	// ��ʼ�������Ϊ0
	vexNum = 0;
	// ��ʼ���߸���Ϊ0
	edgeNum = 0;
}

bool Graph::insertVex(Vex vex)
{
	if(vexNum==MAX_SPOT_NUM)
		return false;
	vexs[vexNum++] = vex;
	return true;
}

bool Graph::insertEdge(Edge edge)
{
	if (edge.vex1 < 0 || edge.vex2 < 0 || edge.vex1 >= MAX_SPOT_NUM || edge.vex2 >= MAX_SPOT_NUM)
	{
		cout << "����Ϣ�±�Խ�磡" << endl;
		return false;
	}
	// �������Ϣ
	adjMatrix[edge.vex1][edge.vex2] = edge.distance;
	adjMatrix[edge.vex2][edge.vex1] = edge.distance;
	edgeNum++;
	return true;
}

Vex Graph::getVex(int vexIndex)
{
	return vexs[vexIndex];
}

int Graph::findEdge(int vexIndex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0;i < vexNum;i++)
	{
		// ���ڽӾ�����������vexIndex���ڵı�
		if (adjMatrix[vexIndex][i] != -1)  // �б�
		{
			aEdge[k].vex1 = vexIndex;
			aEdge[k].vex2 = i;
			aEdge[k].distance = adjMatrix[vexIndex][i];
			k++;
		}
	}
	return k;
}

int Graph::getVexNum()
{
	return vexNum;
}
 
int Graph::getEdgeNum()
{
	return edgeNum;
}

void Graph::prinGraphInfo()
{ 
	printNodeInfo();  // ��ӡ������Ϣ
	printEdgeInfo();  // ��ӡ�ߵ���Ϣ
}

void Graph::printNodeInfo()
{
	cout << "\n========����========" << endl;
	cout << "������Ŀ:" << vexNum << endl;
	for (int i = 0;i < vexNum;i++)
	{
		cout << getVex(i).num << "--" << getVex(i).spotName << "--" << getVex(i).spotInfo << endl;
	}
	cout << endl;
}

void Graph::printEdgeInfo()
{
	cout << "========��=========" << endl;
	for (int i = 0;i < vexNum;i++)
	{
		for (int j = i;j < vexNum;j++)
		{
			if (adjMatrix[i][j] != -1)
			{
				cout << "<V" << i << ",V" << j << "> -->" << adjMatrix[i][j] << "��" << endl;
			}
		}
	}
	cout << endl;
}

void Graph::DFS(int beginVexIndex, bool visited[], int & depth, PathList &pathList)
{
	
	visited[beginVexIndex] = true;
	pathList->vexIndex[depth] = beginVexIndex;  // ��ǰ����¶�Ӧ���ʵ�ǰ���
	// �Ƿ����е㶼���߹�
	if (true == allVisited(visited, vexNum))
	{
		// �½�һ��·�����
		PathNode *newNode = new PathNode;
		newNode->next = NULL;
		// ������λ��ǰ��ֵȫ������
		for (int i = 0;i < vexNum;i++)
		{
			newNode->vexIndex[i] = pathList->vexIndex[i];
		}
		// ����ͷΪ�½�������һ��
		pathList->next = newNode;
		pathList = newNode;
	}
	for(int i=0;i<vexNum;i++)
	{
		// �뵱ǰ����б���û�����ʹ�
		if (adjMatrix[beginVexIndex][i] != -1&&visited[i]==false)
		{
			depth++; // ��һ��
			DFS(i, visited, depth, pathList);
			visited[i] = false;
			depth--;
		}
	}

}

bool Graph::allVisited(bool visited[],int num)
{
	for (int i = 0;i < num;i++)
	{
		//  ֻҪ��һ����û�����ʣ��ͷ���false
		if (false == visited[i])
			return false;
	}
	return true;
}

void Graph::DFSTravel(int beginVexIndex, PathList &pathList)
{
	int depth = 0;
	bool visited[MAX_SPOT_NUM] = { false };
	DFS(beginVexIndex, visited, depth,pathList);
}

void Graph::findShortPath(int vexStart, int vexEnd, Edge pathEdges[])
{
	bool visited[MAX_SPOT_NUM] = { false };
	int weight[MAX_SPOT_NUM];
	// ��ʼ����������Ϊ����
	for (int i = 0;i < vexNum;i++)
	{
		weight[i] = INT_MAX;
	}

	// ��㵽����·��Ϊ0
	weight[vexStart] = 0;
	visited[vexStart] = true;
	pathEdges[vexStart].vex1 = vexStart;
	pathEdges[vexStart].vex2 = vexStart;
	pathEdges[vexStart].distance = 0;

	// ��ʼ����������ΪstartΪ�������
	for (int i = 0;i < vexNum;i++)
	{
		if (adjMatrix[vexStart][i]!=-1)
		{
			weight[i] = adjMatrix[vexStart][i];
			// ���i��ǰ��ΪԴ��
			pathEdges[i].vex1 = vexStart;
			// vex2ûʲô����
			pathEdges[i].vex2 = i;
			pathEdges[i].distance = adjMatrix[vexStart][i];
		}
	}
	// ���·����Ӧ�ĵ��±�
	int minIndex = -1;
	// �Ѿ��߹��ĵ���
	int vexVisitedNum = 1;

	while(vexVisitedNum != vexNum)
	{ 
		// �ҵ���ǰ������������С���Ǹ�
		int min = INT_MAX;
		
		for(int i=0;i<vexNum;i++)
		{
			 // ÿ���ʹ���������С��
			if (visited[i]==false && weight[i] < min)
			{
				min = weight[i];
				minIndex = i;
			}
		}
		// �����뵱ǰ�㳤����С�ĵ�
		visited[minIndex] = true;
		vexVisitedNum++;

		// ������С����ת�㣬��Ӧ�޸ĳ�������
		for(int j=0;j<vexNum;j++)
		{
			// �����һ����û���������뵱ǰ��ת���бߣ����Ҿ�����ת��ĳ��Ⱥͱ�ԭ����С
			if ((adjMatrix[minIndex][j] + weight[minIndex] < weight[j])&&(visited[j] == false) && (adjMatrix[minIndex][j] != -1))
			{
				weight[j] = adjMatrix[minIndex][j] + weight[minIndex];
				// ���½���ǰ��
				pathEdges[j].vex1 = minIndex;
				pathEdges[j].vex2 = j;
				pathEdges[j].distance = weight[j];
			}
		}
	}
}

vector<Edge> Graph::findMinTree()
{
	vector<Edge> edgesVec;
	Edge newEdge;
	int adjvex[MAX_SPOT_NUM];	// ��ض����±�
	int lowcost[MAX_SPOT_NUM];  // ��̬������̱�����
	// ��������v0��㿪ʼ��
	lowcost[0] = 0;			// lowcost=0��ʾ�Ѿ�����������
	adjvex[0] = 0;
	for (int i = 1;i < vexNum;i++)
	{
		// ������������еĵ��б�
		if (adjMatrix[0][i] != -1)
		{
			lowcost[i] = adjMatrix[0][i];
			adjvex[i] = 0;
		}
		else
		{
			lowcost[i] = INT_MAX;
			adjvex[i] = 0;
		}
			
	}
	// ѭ�����е�
	for (int i = 1;i < vexNum;i++)
	{

		int min = INT_MAX;
		int minIndex = -1;
		// ����С��
		for (int j = 1;j < vexNum;j++)
		{
			// ������û�����������ұ���С·������
			if ((lowcost[j] != 0) && lowcost[j] < min)
			{
				min = lowcost[j];
				minIndex = j;
			}
		}
		// ��С�߶�Ӧ�ĵ����������
		lowcost[minIndex] = 0;
		// ����µıߵ��߼�������
		newEdge.vex1 = adjvex[minIndex];
		newEdge.vex2 = minIndex;
		newEdge.distance=min;
		edgesVec.push_back(newEdge);
		// ������С��
		for (int i = 1;i < vexNum;i++)
		{
			// ��û���ʹ����ұ߳��ȵ�ǰֵ��С
			if (lowcost[i] != 0 && (adjMatrix[minIndex][i]!=-1)&&adjMatrix[minIndex][i] < lowcost[i])
			{
				lowcost[i] = adjMatrix[minIndex][i];
				adjvex[i] = minIndex;
			}
		}
		
	}
	return edgesVec;
}
