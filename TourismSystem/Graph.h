#pragma once
#include <string>
#include<vector>
using namespace std;
#define MAX_SPOT_NUM  20 // 景区最大个数

// 图中的点，即景区
struct Vex
{
	int num;		  // 景点编号
	string spotName;  // 景点名称
	string spotInfo;  // 景点描述
};

// 图中的边，即景点之间的路径
struct Edge
{
	int vex1;		// 边的第一个顶点
	int vex2;		// 边的第二个顶点
	int distance;   // 边的长度
};

typedef struct PathNode
{
	int vexIndex[MAX_SPOT_NUM];   // 一条路径的下标值
	PathNode *next;  // 下一条路径

	// 构造函数
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
	int adjMatrix[MAX_SPOT_NUM][MAX_SPOT_NUM];   // 邻接矩阵
	Vex vexs[MAX_SPOT_NUM];						 // 顶点信息数组
	int vexNum;								     // 图中顶点数
	int edgeNum;								 // 图中无向边数
	// 深度优先遍历(递归实现)
	void DFS(int beginVexIndex, bool visited[], int &depth, PathList &pathList);
	bool allVisited(bool visited[], int num);	// 判断前n个景点是否都被访问过

public:
	void initGraph();										// 初始化图的结构
	bool insertVex(Vex vex);								// 将顶点添加到顶点数组
	bool insertEdge(Edge edge);								// 将边保存到邻接矩阵中
	Vex getVex(int vexIndex);								// 根据编号查询顶点信息
	int findEdge(int vexIndex, Edge aEdge[]);				// 查询与指定顶点相连的边
	int getVexNum();										// 获取当前顶点个数
	int getEdgeNum();										// 获取当前边条数
	void prinGraphInfo();									// 输出图的信息
	void printNodeInfo();									// 输出图中点的信息
	void printEdgeInfo();									// 输出图中边的信息
	void DFSTravel(int beginVexIndex, PathList &pathList);  // 深度优先遍历得到一条路径
	void findShortPath(int vexStart, int vexEnd, Edge pathEdges[]);  //找到起点到终点的最短路径
	vector<Edge>  findMinTree();										// 寻找最小生成树（prim算法实现）
};
