#pragma once
#include <string>
#include<vector>
using namespace std;
#define MAX_SPOT_NUM  20 // ����������

// ͼ�еĵ㣬������
struct Vex
{
	int num;		  // ������
	string spotName;  // ��������
	string spotInfo;  // ��������
};

// ͼ�еıߣ�������֮���·��
struct Edge
{
	int vex1;		// �ߵĵ�һ������
	int vex2;		// �ߵĵڶ�������
	int distance;   // �ߵĳ���
};

typedef struct PathNode
{
	int vexIndex[MAX_SPOT_NUM];   // һ��·�����±�ֵ
	PathNode *next;  // ��һ��·��

	// ���캯��
	PathNode()
	{
		for(int i=0;i<MAX_SPOT_NUM;i++)
			vexIndex[i] = -1;	
		next = NULL;
	}
}*PathList;
class Graph
{
private:
	int adjMatrix[MAX_SPOT_NUM][MAX_SPOT_NUM];   // �ڽӾ���
	Vex vexs[MAX_SPOT_NUM];						 // ������Ϣ����
	int vexNum;								     // ͼ�ж�����
	int edgeNum;								 // ͼ���������
	// ������ȱ���(�ݹ�ʵ��)
	void DFS(int beginVexIndex, bool visited[], int &depth, PathList &pathList);
	bool allVisited(bool visited[], int num);	// �ж�ǰn�������Ƿ񶼱����ʹ�

public:
	void initGraph();										// ��ʼ��ͼ�Ľṹ
	bool insertVex(Vex vex);								// ��������ӵ���������
	bool insertEdge(Edge edge);								// ���߱��浽�ڽӾ�����
	Vex getVex(int vexIndex);								// ���ݱ�Ų�ѯ������Ϣ
	int findEdge(int vexIndex, Edge aEdge[]);				// ��ѯ��ָ�����������ı�
	int getVexNum();										// ��ȡ��ǰ�������
	int getEdgeNum();										// ��ȡ��ǰ������
	void prinGraphInfo();									// ���ͼ����Ϣ
	void printNodeInfo();									// ���ͼ�е����Ϣ
	void printEdgeInfo();									// ���ͼ�бߵ���Ϣ
	void DFSTravel(int beginVexIndex, PathList &pathList);  // ������ȱ����õ�һ��·��
	void findShortPath(int vexStart, int vexEnd, Edge pathEdges[]);  //�ҵ���㵽�յ�����·��
	vector<Edge>  findMinTree();										// Ѱ����С��������prim�㷨ʵ�֣�
};
